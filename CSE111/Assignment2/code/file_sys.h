// $Id: file_sys.h,v 1.11 2019-10-27 21:05:44-07 - - $.
// Edwin Wang and Andrew Lyle (ekwang and alyle respectively)

#ifndef __INODE_H__
#define __INODE_H__

#include <exception>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
using namespace std;
#include "util.h"

// inode_t -
//    An inode is either a directory or a plain file.

enum class file_type {PLAIN_TYPE, DIRECTORY_TYPE};
class inode;
class base_file;
class plain_file;
class directory;
using inode_ptr = shared_ptr<inode>;
using base_file_ptr = shared_ptr<base_file>;
using directory_ptr = shared_ptr<directory>;
using file_ptr = shared_ptr<plain_file>;
ostream& operator<< (ostream&, file_type);

void err_print(const string& cmdname,
const string& argname, const string& errname);


// inode_state -
//    A small convenient class to maintain the state of the simulated
//    process:  the root (/), the current directory (.), and the
//    prompt.

class inode_state {
   friend class inode;
   friend class plain_file;
   friend class base_file;
   friend class directory;
   friend ostream& operator<< (ostream& out, const inode_state&);
   private:
      inode_ptr root {nullptr};
      inode_ptr cwd {nullptr};
      string prompt_ {"% "};
      void rmrecur(inode_ptr target);
      void lsrecur(const string& path);
   public:
      ~inode_state();
      inode_state (const inode_state&) = delete; // copy ctor
      inode_state& operator= (const inode_state&) = delete; // op=
      inode_state();
      void rmr(const string& path);
      void rm(const string& path);
      bool lsprint(const string& path);
      void lsr(const string& path);
      bool pwd();
      bool mkdir_at_cwd(const string& filename);
      bool make_file(const string& filename, const string& text);
      bool cat(const string& filename);
      bool cd(const string& path);
      inode_ptr pathDecode(const string& path);
      const string& prompt() const;
      void setprompt(const string& newprompt);
};

// class inode -
// inode ctor -
//    Create a new inode of the given type.
// get_inode_nr -
//    Retrieves the serial number of the inode.  Inode numbers are
//    allocated in sequence by small integer.
// size -
//    Returns the size of an inode.  For a directory, this is the
//    number of dirents.  For a text file, the number of characters
//    when printed (the sum of the lengths of each word, plus the
//    number of words.
//

class inode {
   friend class inode_state;
   friend class plain_file;
   friend class base_file;
   friend class directory;
   private:
      static int next_inode_nr;
      int inode_nr;
      base_file_ptr contents;
      string fileType;
   public:
      inode (file_type);
      int get_inode_nr() const;
      int size() const;
      string type() const;
};


// class base_file -
// Just a base class at which an inode can point.  No data or
// functions.  Makes the synthesized members useable only from
// the derived classes.

class base_file {
   friend class inode_state;
   friend class inode;
   friend class plain_file;
   friend class directory;
   protected:
      base_file() = default;
      virtual const string error_file_type() const = 0;
   public:
      virtual ~base_file() = default;
      base_file (const base_file&) = delete;
      base_file& operator= (const base_file&) = delete;
      virtual size_t size() const = 0;
      virtual const string& readfile() const;
      virtual void writefile (const string& newdata);
      virtual void remove (const string& filename);
      virtual inode_ptr mkdir (const string& dirname);
      virtual inode_ptr mkfile (const string& filename);
};

class file_error: public runtime_error {
   public:
      explicit file_error (const string& what);
};


// class plain_file -
// Used to hold data.
// synthesized default ctor -
//    Default vector<string> is a an empty vector.
// readfile -
//    Returns a copy of the contents of the wordvec in the file.
// writefile -
//    Replaces the contents of a file with new contents.

class plain_file: public base_file {
   friend class inode_state;
   friend class inode;
   friend class base_file;
   friend class directory;
   private:
      string data;
      virtual const string error_file_type() const override {
         return "plain file";
      }
   public:
      virtual size_t size() const override;
      virtual const string& readfile() const override;
      virtual void writefile (const string& newdata) override;
};

// class directory -
// Used to map filenames onto inode pointers.
// default ctor -
//    Creates a new map with keys "." and "..".
// remove -
//    Removes the file or subdirectory from the current inode.
//    Throws an file_error if this is not a directory, the file
//    does not exist, or the subdirectory is not empty.
//    Here empty means the only entries are dot (.) and dotdot (..).
// mkdir -
//    Creates a new directory under the current directory and
//    immediately adds the directories dot (.) and dotdot (..) to it.
//    Note that the parent (..) of / is / itself.  It is an error
//    if the entry already exists.
// mkfile -
//    Create a new empty text file with the given name.  Error if
//    a dirent with that name exists.

class directory: public base_file {
   friend class inode_state;
   friend class inode;
   friend class plain_file;
   friend class base_file;
   private:
      // Must be a map, not unordered_map, so printing is lexicographic
      map<string,inode_ptr> dirents;
      virtual const string error_file_type() const override {
         return "directory";
      }
   public:
      virtual size_t size() const override;
      virtual void remove (const string& filename) override;
      virtual inode_ptr mkdir (const string& dirname) override;
      virtual inode_ptr mkfile (const string& filename) override;
};

#endif
