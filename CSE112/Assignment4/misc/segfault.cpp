// $Id: segfault.cpp,v 1.3 2020-11-22 17:58:44-08 - - $
#include <cstdint>
int main() {
   uintptr_t u = 4;
   int* p = reinterpret_cast<int*> (u);
   *p = 3;
}
