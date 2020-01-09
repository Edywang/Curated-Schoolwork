// $Id: cix.cpp,v 1.9 2019-04-05 15:04:28-07 - - $
//client
// Edwin Wang and Andrew Lyle (ekwang and alyle respectively)
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <regex>
#include <fstream>

using namespace std;

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>


#include "protocol.h"
#include "logstream.h"
#include "sockets.h"

logstream outlog (cout);
struct cix_exit: public exception {};

unordered_map<string,cix_command> command_map {
   {"exit", cix_command::EXIT},
   {"help", cix_command::HELP},
   {"ls"  , cix_command::LS  },
   {"get"  , cix_command::GET  },
   {"put"  , cix_command::PUT  },
   {"rm"  , cix_command::RM  },
};

static const char help[] = R"||(
exit         - Exit the program.  Equivalent to EOF.
get filename - Copy remote file to local host.
help         - Print help summary.
ls           - List names of files on remote server.
put filename - Copy local file to remote host.
rm filename  - Remove file from remote server.
)||";

void cix_help() {
   cout << help;
}

bool fileExists (string filename){
   ifstream f(filename);
   return f.good();
}

void cix_ls (client_socket& server) {
   cix_header header;
   header.command = cix_command::LS;
   outlog << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   outlog << "received header " << header << endl;
   if (header.command != cix_command::LSOUT) {
      outlog << "sent LS, server did not return LSOUT" << endl;
      outlog << "server returned " << header << endl;
   }else {
      auto buffer = make_unique<char[]> (header.nbytes + 1);
      recv_packet (server, buffer.get(), header.nbytes);
      outlog << "received " << header.nbytes << " bytes" << endl;
      buffer[header.nbytes] = '\0';
      cout << buffer.get();
   }
}

void cix_get (client_socket& server, string filename) {
   if(fileExists(filename)){
      outlog << "get: file already exists" << endl;
      return;
   }
   cix_header header;
   header.command = cix_command::GET;
   char char_file[59];
   strcpy(char_file, filename.c_str());
   strcpy(header.filename,filename.c_str());
   outlog << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   outlog << "sending header " << header << endl;
   cout <<"Sent "<<endl;
   recv_packet (server, &header, sizeof header);
   outlog << "received header " << header << endl;
   if (header.command != cix_command::FILEOUT) {
      outlog << "sent GET, server did not return FILEOUT" << endl;
      outlog << "server returned " << header << endl;
   }else {
      auto buffer = make_unique<char[]> (header.nbytes + 1);
      recv_packet (server, buffer.get(), header.nbytes);
      outlog << "received " << header.nbytes << " bytes" << endl;
      buffer[header.nbytes] = '\0';
      ofstream out(filename);
      out << buffer.get();
      out.close();
   }
}

void cix_rm (client_socket& server, string filename) {
    cix_header header;
    header.command = cix_command::RM;
    strcpy(header.filename, filename.c_str());
    outlog << "sending header " << header << endl;
    send_packet (server, &header, sizeof header);
    recv_packet (server, &header, sizeof header);
    outlog << "received header " << header << endl;
    if (header.command != cix_command::ACK) {
      outlog << "sent RM, server did not return ACK" << endl;
      outlog << "server returned " << header << endl;
   }
}

void cix_put(client_socket& server, string filename){
   if(!fileExists(filename)){
      outlog << "put: file doesn't exist" << endl;
      return;
   }
   ifstream t(filename);
   string filecontents((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
   cix_header header;
   strcpy(header.filename, filename.c_str());
   header.command = cix_command::PUT;
   header.nbytes = filecontents.size();
   send_packet (server, &header, sizeof header);
   outlog << "sending header " << header << endl;
   send_packet (server, filecontents.c_str(), filecontents.size());
   outlog << "sending file contents" << endl;
   recv_packet (server, &header, sizeof header);
   outlog << "received header " << header << endl;
}


void usage() {
   cerr << "Usage: " << outlog.execname() << " [host] [port]" << endl;
   throw cix_exit();
}

int main (int argc, char** argv) {
   outlog.execname (basename (argv[0]));
   outlog << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   if (args.size() > 2) usage();
   string host = get_cix_server_host (args, 0);
   in_port_t port = get_cix_server_port (args, 1);
   outlog << to_string (hostinfo()) << endl;
   try {
      outlog << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      outlog << "connected to " << to_string (server) << endl;
      for (;;) {
         string line;
         getline (cin, line);
         if (cin.eof()) throw cix_exit();
         outlog << "command " << line << endl;
         regex first_word("^\\s*\\w*");
         string not_first_word = regex_replace(line, first_word, "");
         regex not_first (not_first_word);
         string first = regex_replace(line, not_first, "");
         regex leading_spaces("^\\s*");
         first= regex_replace(first, leading_spaces, "");
         string second = regex_replace(line, first_word, "");
         second = regex_replace(second, leading_spaces, "");
         regex whitespace("\\s");
         if(regex_search(second, whitespace)){
              first = "failed";
         }
         const auto& itor = command_map.find (first);
         cix_command cmd = itor == command_map.end()
                         ? cix_command::ERROR : itor->second;
         switch (cmd) {
            case cix_command::EXIT:
               throw cix_exit();
               break;
            case cix_command::HELP:
               cix_help();
               break;
            case cix_command::LS:
               if ( second.size()==0)
                  cix_ls (server);
               else
                  outlog << line << ": invalid command" << endl;
               break;
            case cix_command::GET:
               if ( second.size()==0)
                  outlog << line << ": invalid command" << endl;
               else
                  cix_get(server, second);
               break;
            case cix_command::PUT:
               if ( second.size()==0)
                  outlog << line << ": invalid command" << endl;
               else
                  cix_put(server, second);
               break;
            case cix_command::RM:
               if ( second.size()==0)
                  outlog << line << ": invalid command" << endl;
               else
                  cix_rm (server, second);
               break;
            default:
               outlog << line << ": invalid command" << endl;
               break;
         }
      }
   }catch (socket_error& error) {
      outlog << error.what() << endl;
   }catch (cix_exit& error) {
      outlog << "caught cix_exit" << endl;
   }
   outlog << "finishing" << endl;
   return 0;
}
