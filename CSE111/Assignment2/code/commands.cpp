// $Id: commands.cpp,v 1.19 2019-10-27 20:59:20-07 - - $
// Edwin Wang and Andrew Lyle (ekwang and alyle respectively)

#include "commands.h"
#include "debug.h"

command_hash cmd_hash {
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
   {"rmr"   , fn_rmr   },
   {"#"     , fn_nothing},
};

command_fn find_command_fn (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   DEBUGF ('c', "[" << cmd << "]");
   const auto result = cmd_hash.find (cmd);
   if (result == cmd_hash.end()) {
      throw command_error (cmd + ": no such function");
   }
   return result->second;
}

int exit_status_message() {
   int status = exec::status();
   cout << exec::execname() << ": exit(" << status << ")" << endl;
   
   return status;
}

void fn_nothing(inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_cat (inode_state& state, const wordvec& words){
  if(words.size()==1){
      err_print("cat", " ", "Incorrect number of arguments");
      exec::status(1);
  }else{
    for(size_t i=1;i<words.size();i++){
      try{
        state.cat(words[i]);
      }catch(command_error& error){
        exec::status(1);
      }
     }
   }
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_cd (inode_state& state, const wordvec& words){
   if(words.size()==1){
      state.cd ("/");
   }
   else if(words.size()>2){
       err_print("cd", words[1], "Incorrect number of arguments");
       exec::status(1);
   }else if (state.cd (words[1])){
       exec::status(1);
   }
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_echo (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   cout << word_range (words.cbegin() + 1, words.cend()) << endl;
}


void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size() > 1)
    exec::status(stoi(words[1]));
   throw ysh_exit();
}

void fn_ls (inode_state& state, const wordvec& words){
   if(words.size()==1)
      state.lsprint(".");
   else
     for(size_t i=1;i<words.size();i++)
        if(state.lsprint(words[i]))
            exec::status(1);
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_lsr (inode_state& state, const wordvec& words){
   if(words.size()==1)
      state.lsr("");
   else
     for(size_t i=1;i<words.size();i++)
        state.lsr(words[i]);

   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_make (inode_state& state, const wordvec& words){
   if(words.size()<2){
       err_print("make", " ", "Incorrect number of arguments");
       exec::status(1);
   }else{
       string text= ("");
       for(size_t i=2;i<words.size();i++){
         text.append(words[i]);
         if(i!=words.size()-1)
             text.append(" ");

     }

     if(state.make_file(words[1],text)){
       exec::status(1);

     }
   }
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_mkdir (inode_state& state, const wordvec& words){
   if( words.size() != 2){
     if(words.size()==1)
       err_print("mkdir", " ", "Incorrect number of arguments");
     else
       err_print("mkdir", words[1], "Incorrect number of arguments");
      exec::status(1);
   }else if (state.mkdir_at_cwd(words[1])){
      exec::status(1);
   }
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_prompt (inode_state& state, const wordvec& words){
   string text= ("");
   for(size_t i=1;i<words.size();i++){
      text.append(words[i]);
      if(i!=words.size()-1)
         text.append(" ");
   }
   state.setprompt(text+" ");
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_pwd (inode_state& state, const wordvec& words){
   if(words.size()>1){
     exec::status(1);
     err_print("pwd", words[1], "Incorrect number of arguments");
   }else if(state.pwd()){
     exec::status(1);
   }
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_rm (inode_state& state, const wordvec& words){
   if(words.size()!=2){
      cerr << "Function rm called with invalid number of args";
      return;
   }
   state.rm(words[1]);
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_rmr (inode_state& state, const wordvec& words){
  if(words.size()!=2){
      cerr << "Function rmr called with invalid number of args";
      return;
   }
   state.rmr(words[1]);
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}
