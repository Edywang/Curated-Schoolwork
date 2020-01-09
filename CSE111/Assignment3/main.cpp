// $Id: main.cpp,v 1.11 2018-01-25 14:19:29-08 - - $
// Edwin Wang and Andrew Lyle (ekwang and alyle respectively)

#include <cstdlib>

#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <regex>
using namespace std;
#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap < string, string > ;
using str_str_pair = str_str_map::value_type;
string one = "\\s{0,100}[^=\\s]{1}[^=]{0,100}\\s{0,100}[=]";
string two = "\\s{0,100}[^\\s]{1,100}.{0,100}\\s{0,100}";
static regex aequalsb(one + two);
static regex aequals("\\s{0,100}[^=]{1,100}\\s{0,100}[=]\\s{0,100}");
static regex equalsb
("\\s{0,100}[=]\\s{0,100}[^\\s]{1}.{0,100}\\s{0,100}");
static regex comment("\\s{0,100}#.{1,100}");
static regex keyonly("\\s{0,100}[^=]{1,100}\\s{0,100}");
static regex equals("\\s{0,100}[=]\\s{0,100}");
static regex trailingspaces("([\\s]{1,100}$)");
static regex leadingspaces("(^[\\s]{1,100})");
static regex a("([\\s]{0,100}=[\\s]{0,100}.{0,100}$)");
static regex b("(^[^=]{0,100}=[\\s]{0,100})");

void scan_options(int argc, char ** argv) {
  opterr = 0;
  for (;;) {
    int option = getopt(argc, argv, "@:");
    if (option == EOF) break;
    switch (option) {
      case '@':
      debugflags::setflags(optarg);
      break;
      default:
      complain() << "-" << char(optopt) << ": invalid option" <<
      endl;
      break;
    }
  }
}

void executeLine(string line, listmap<const string,
 const string, xless<const string>> *map) {

  if (regex_match(line, aequalsb)) {
    string value = regex_replace(line, b, "");
    value = regex_replace(value, trailingspaces, "");

    string key = regex_replace(line, a, "");
    key = regex_replace(key, leadingspaces, "");

    xpair<const string, const string> pair(key,value);
    cout << pair<< endl;
    if(map->find(key)==map->end()){
      map->insert(pair);
    }else{
      map->erase(map->find(key));
      map->insert(pair);
    }
  } else if (regex_match(line, aequals)) {
    string key = regex_replace(line, a, "");
    key = regex_replace(key, leadingspaces, "");
    if(map->find(key)!=map->end()){
      map->erase(map->find(key));
    }


  } else if (regex_match(line, equalsb)) {

    string value = regex_replace(line, b, "");
    value = regex_replace(value, trailingspaces, "");
    auto it = map->begin();
    while(it != map->end()){
      if(it->second == value){
        cout << *it << endl;
      }
      ++it;
    }
  } else if (regex_match(line, comment)){
    // Do nothing
  }else if (regex_match(line, keyonly)) {
    string key = regex_replace(line, trailingspaces, "");
    key = regex_replace(key, leadingspaces, "");
    if(map->find(key)!=map->end()){
      cout << *map->find(key)<<endl;
    }else{
      cout << key << ": key not found"<<endl;
    }
  } else if (regex_match(line, equals)) {auto it = map->begin();
    while(it != map->end()){
      cout << *it << endl;
      ++it;
    }

  }
}
int main(int argc, char ** argv) {
  sys_info::execname(argv[0]);
  scan_options(argc, argv);
  int success = 0;
  listmap<const string, const string, xless<const string>> *map
  = new listmap<const string, const string, xless<const string>>;

  for (int i = 1; i < argc; i++) {
    ifstream file(argv[i]);
    if (file.fail()) {
      cout << argv[0] << ": " << argv[i] << ": "
      << "No such file or directory" << endl;
      success = 1;
    } else {
      string line;
      int lineCount= 1;
      while (std::getline(file, line)) {
        cout << argv[i] << ": " << lineCount<< ": "<<line << endl;
        executeLine(line, map);
        lineCount++;
      }
    }
  }

  if ( argc==1){
    int count =1;
    string input="";
    getline(cin,input);
    while (!cin.eof()){
      cout << "-: " << count<<": "<< input<< endl;
      executeLine(input, map);
      getline(cin,input);
      count++;
    }
  }

  delete(map);

  return success;
}
