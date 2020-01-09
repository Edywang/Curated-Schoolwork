// $Id: file_sys.cpp,v 1.8 2019-10-27 20:59:20-07 - - $
// Edwin Wang and Andrew Lyle (ekwang and alyle respectively)

#include <iostream>
#include <stdexcept>
#include <unordered_map>

using namespace std;

#include "debug.h"
#include "file_sys.h"
#include <cstring>
int inode::next_inode_nr {1};

struct file_type_hash {
   size_t operator() (file_type type) const {
      return static_cast<size_t> (type);
   }
};

void err_print(const string& cmdname,
const string& argname, const string& errname){
  throw command_error (cmdname + ": " + argname + ": " + errname);
  // cerr << cmdname << ": " << argname << ": " << errname << endl;
}

void inode_state::setprompt(const string& newprompt){
  prompt_ =newprompt;
}

ostream& operator<< (ostream& out, file_type type) {
   static unordered_map<file_type,string,file_type_hash> hash {
      {file_type::PLAIN_TYPE, "PLAIN_TYPE"},
      {file_type::DIRECTORY_TYPE, "DIRECTORY_TYPE"},
   };
   return out << hash[type];
}

inode_state::inode_state() {
   root= make_shared<inode>(file_type::DIRECTORY_TYPE);
   directory_ptr dir = dynamic_pointer_cast<directory>(root->contents);
   dir -> dirents.insert(pair<string,inode_ptr>(".",root));
   dir -> dirents.insert(pair<string,inode_ptr>("..",root));
   cwd=root;

   DEBUGF ('i', "root = " << root << ", cwd = " << cwd
          << ", prompt = \"" << prompt() << "\"");
}

inode_state::~inode_state() {
   rmrecur(root);
   root = nullptr;
   cwd = nullptr;
}

bool inode_state::lsprint(const string& path){

   inode_ptr temp = pathDecode(path);

   directory_ptr dir= dynamic_pointer_cast<directory>(temp->contents);
   string a = ("");
   while(dir->dirents.at("..")!=temp){
      inode_ptr temp2 =dir->dirents.at("..");
      directory_ptr dir2 =
      dynamic_pointer_cast<directory>(temp2->contents);
      for (auto it=dir2->dirents.begin(); it!=dir2->dirents.end(); ++it)
        if(it->second==temp){
               a.insert(0,it->first);
               a.insert(0,"/");
            }
          temp = dir->dirents.at("..");
          dir= dynamic_pointer_cast<directory>(temp->contents);
   }
   if(a.length()>0){
       cout <<a<<":"<<endl;
   }else{
       cout <<"/"<<":"<<endl;
   }
    inode_ptr result_path;
   if(path.compare(".")==0||path.length()==0){
      result_path= cwd;
   }else{
      result_path= pathDecode(path);
   }
   if(result_path ==nullptr){
     err_print("ls", path, "Path not found");
     return true;
   }
   // Printing everything in the directory
   directory_ptr dir3 =
   dynamic_pointer_cast<directory>(result_path->contents);
   for (auto it=dir3->dirents.begin(); it!=dir3->dirents.end(); ++it){

       cout << "    "<< it -> second-> inode_nr 
       << "    " << it -> second->size() << "  ";
       cout << it->first;
       if(it -> second-> contents->error_file_type()==
       "directory"&&(it->first!="."&&it->first!=".." )){
         cout << "/";
       }
       cout << '\n';
    }
   return false;
}

void inode_state::lsr(const string& path){
    inode_ptr temp;
    if(path.find('/') == string::npos)
        temp = cwd;
    else
        temp = pathDecode(path);
    // Building absolute path to the target directory
   directory_ptr dir = dynamic_pointer_cast<directory>(temp->contents);
   string absPath = ("");
   while(dir->dirents.at("..") != temp){
      inode_ptr temp2 = dir->dirents.at("..");
      directory_ptr dir2 =
      dynamic_pointer_cast<directory>(temp2->contents);
      for (auto it = dir2->dirents.begin();
      it != dir2->dirents.end(); ++it)
        if(it->second == temp){
               absPath.insert(0,it->first);
               absPath.insert(0,"/");
            }
          temp = dir->dirents.at("..");
          dir = dynamic_pointer_cast<directory>(temp->contents);
   }
   if(absPath.empty())
      absPath = "/" + path;
   lsrecur(absPath);
}

void inode_state::lsrecur(const string& path){
    lsprint(path);
    inode_ptr target = pathDecode(path);
    if((*target).size() <= 2){
        return;
    }
    directory_ptr dir =
    dynamic_pointer_cast<directory>(target->contents);
    auto it = dir->dirents.begin();
    ++it;
    ++it;
    for (; it != dir->dirents.end(); it++)
        // Grab the value from the iterator (inode_ptr) and recur
        if((*(it->second)).type() == "directory")
            lsrecur(path + "/" + it->first);
}

void inode_state::rm(const string& path){
  // Get necessary pointers
  inode_ptr parent = cwd;
  string filename = path;
   if(path.find('/') != string::npos){
      size_t index_of_last = filename.find_last_of("/");
      filename = path.substr(index_of_last + 1);
      parent = pathDecode(filename.substr(0,index_of_last));
   }
   inode_ptr target = pathDecode(path);
   // Error checking
   if(target == nullptr){
    err_print("rm", path, "Target not found");
    return;
   }
   else if(target == parent){
    err_print("rm", path, "Called on root");
    return;
   }
   else if((*target).type() == "directory" && (*target).size() > 2){
    err_print("rm", path, "Called on directory with children");
    return;
   }
   // Erase the reference
  directory_ptr dir = dynamic_pointer_cast<directory>(parent->contents);
  dir->dirents.erase(filename);
}

void inode_state::rmr(const string& path){
    // Get necessary pointers
  inode_ptr parent = cwd;
  string filename = path;
   if(path.find('/') != string::npos){
      size_t index_of_last = filename.find_last_of("/");
      filename = path.substr(index_of_last + 1);
      parent = pathDecode(filename.substr(0,index_of_last));
   }
   inode_ptr target = pathDecode(path);
   // Error checking
   if(target == nullptr){
    err_print("rm", path, "Target not found");
    return;
   }
   else if(target == parent){
    err_print("rm", path, "Called on root");
    return;
   }
   rmrecur(target);
   // Erase the reference
   directory_ptr dir =
   dynamic_pointer_cast<directory>(parent->contents);
   dir->dirents.erase(filename);
}

void inode_state::rmrecur(inode_ptr target){
  if((*target).type() == "directory" && (*target).size() > 2){
    directory_ptr dir =
    dynamic_pointer_cast<directory>(target->contents);
    auto next = dir->dirents.begin();
    ++next;
    ++next;
    auto current = next;
    while(next != dir->dirents.end()){
      ++next;
      rmrecur(current->second);
      dir->dirents.erase(current->first);
      current = next;
    }
    dir->dirents.erase("..");
    dir->dirents.erase(".");
  }
}

bool inode_state::pwd(){
   inode_ptr temp = cwd;
   directory_ptr dir= dynamic_pointer_cast<directory>(temp->contents);
   string a= ("");
   while(dir->dirents.at("..")!=temp){
      inode_ptr temp2 =dir->dirents.at("..");
      directory_ptr dir2 =
      dynamic_pointer_cast<directory>(temp2->contents);
      for (auto it=dir2->dirents.begin(); it!=dir2->dirents.end(); ++it)
        if(it->second==temp){
               a.insert(0,it->first);
               a.insert(0,"/");
                 //cout <<it->first;
            }
          temp = dir->dirents.at("..");
          dir= dynamic_pointer_cast<directory>(temp->contents);
   }
   if(a.length()>0){
       cout <<a<<endl;
   }else{
       cout <<"/"<<endl;
   }
   return false;
}

bool inode_state::make_file(const string& filename, const string& text){
   inode_ptr path= cwd;
   string file;
   if(filename.find("/") != string::npos){
      size_t index_of_last = filename.find_last_of("/");
      path = pathDecode(filename.substr(0,index_of_last));
      file =filename.substr(index_of_last+1);
      if(path ==nullptr){
      err_print("make", filename, "Path to file not found");
        return true;
      }

   }else{
      file= filename;
   }
   directory_ptr dir = dynamic_pointer_cast<directory>(path->contents);
   if(dir->mkfile(file)==nullptr){
     err_print("make",filename,  "Path to file already exists");
     return true;
   }
   file_ptr ptr_to_file =
   dynamic_pointer_cast<plain_file>(dir->dirents.at(file)->contents);

   ptr_to_file->writefile(text);
   return false;

}

bool inode_state::mkdir_at_cwd(const string& filename){
   inode_ptr path = cwd;
   string file;
   if(filename.find('/') != string::npos){
      size_t index_of_last = filename.find_last_of("/");

      path = pathDecode(filename.substr(0,index_of_last));
      file =filename.substr(index_of_last+1);

      if(path ==nullptr){
        err_print("mkdir", filename, "Path to directory not found");
        return true;
      }
   }else{
      file= filename;
   }
   directory_ptr dir= dynamic_pointer_cast<directory>(path->contents);
   if(dir->mkdir(file)==nullptr){
     err_print("mkdir", filename, "File already exists");
     return true;
   }
   return false;
}

bool inode_state::cat(const string& filename){
   inode_ptr path = pathDecode(filename);
   if(path ==nullptr){
     err_print("cat",filename, "Path to file chosen not valid");
     return true;
   }
   if (path -> contents->error_file_type()=="plain file"){
      file_ptr ptr_to_file =
      dynamic_pointer_cast<plain_file>(path->contents);
      cout << ptr_to_file-> readfile()<<endl;
   }else{
    err_print("cat", filename, "Target is a directory");
     return true;
   }
   return false;
}

inode_ptr inode_state::pathDecode(const string& path){
  inode_ptr ret = cwd;

  if(path.at(0)==('/'))
    ret = root;

    //absolutePath
  wordvec words = split (path, "/");


  bool foundall= true;

  for(string& subdir : words){
     directory_ptr dir= dynamic_pointer_cast<directory>(ret->contents);
       try {
           ret = dir->dirents.at(subdir);
       }
       catch (const out_of_range& err) {
           foundall= false;
           break;
       }
  }
  if(!foundall){
    return nullptr;
  }
  return ret;
}

bool inode_state::cd (const string& path){
   inode_ptr newCWD = pathDecode(path);
   if(newCWD==nullptr){
      err_print("cd", path, "Directory not found");
     return true;
   }else if((*newCWD).type() == "plain"){
      err_print("cd", path, "Target is a plain file");
      return true;
   }
   else {
     cwd= newCWD;
     return false;
   }
}

const string& inode_state::prompt() const { return prompt_; }

ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

inode::inode(file_type type): inode_nr (next_inode_nr++) {
   switch (type) {
      case file_type::PLAIN_TYPE:
           fileType = "plain";
           contents = make_shared<plain_file>();
           break;
      case file_type::DIRECTORY_TYPE:
           fileType = "directory";
           contents = make_shared<directory>();
           break;
   }
   DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
}

int inode::get_inode_nr() const {
   DEBUGF ('i', "inode = " << inode_nr);
   return inode_nr;
}

int inode::size() const {
  DEBUGF ('i', "size = " << (*contents).size());
  return (*contents).size();
}

string inode::type() const {
  DEBUGF ('i', "type = " << fileType);
  return fileType;
}


file_error::file_error (const string& what):
            runtime_error (what) {
}

const string& base_file::readfile() const {
   throw file_error ("is a " + error_file_type());
}

void base_file::writefile (const string&) {
   throw file_error ("is a " + error_file_type());
}

void base_file::remove (const string&) {
   throw file_error ("is a " + error_file_type());
}

inode_ptr base_file::mkdir (const string&) {
   throw file_error ("is a " + error_file_type());
}

inode_ptr base_file::mkfile (const string&) {
   throw file_error ("is a " + error_file_type());
}


size_t plain_file::size() const {
   size_t size {data.length()};
   DEBUGF ('i', "size = " << size);
   return size;
}

const string& plain_file::readfile() const {
   DEBUGF ('i', data);
   return data;
}

void plain_file::writefile (const string& words) {
   data= words;
   DEBUGF ('i', words);
}

size_t directory::size() const {
   size_t size {dirents.size()};
   DEBUGF ('i', "size = " << size);
   return size;
}

void directory::remove (const string& filename) {
   DEBUGF ('i', filename);
}

inode_ptr directory::mkdir (const string& dirname) {
   auto iter = dirents.find(dirname);
   if( iter!=dirents.end()){
      return nullptr;
   }
   inode_ptr node = make_shared<inode>(file_type::DIRECTORY_TYPE);
   base_file_ptr fil=node->contents;
   directory_ptr dir= dynamic_pointer_cast<directory>(fil);
   dir -> dirents.insert(pair<string,inode_ptr>(".",node));
   dir -> dirents.insert(pair<string,inode_ptr>("..",dirents.at(".")));
   dirents.insert(pair<string,inode_ptr>(dirname,node));
   DEBUGF ('i', dirname);
   return node;
}

inode_ptr directory::mkfile (const string& filename) {
  auto iter = dirents.find(filename);
  if( iter!=dirents.end()){
     return nullptr;
  }
   inode_ptr node = make_shared<inode>(file_type::PLAIN_TYPE);
   base_file_ptr fil=node->contents;
   file_ptr file= dynamic_pointer_cast<plain_file>(fil);
   dirents.insert(pair<string,inode_ptr>(filename,node));
   DEBUGF ('i', filename);
   return node;
}
