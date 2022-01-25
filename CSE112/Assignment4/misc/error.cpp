// $Id: error.cpp,v 1.2 2020-11-22 19:42:39-08 - - $
#include <string>
int main (int argc, char**argv) {
   return argc == 1 ? 0 : std::stoi (argv[1]);
}
