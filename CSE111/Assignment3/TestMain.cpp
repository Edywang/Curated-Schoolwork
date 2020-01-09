// $Id: main.cpp,v 1.11 2018-01-25 14:19:29-08 - - $
// Edwin Wang and Andrew Lyle (ekwang and alyle respectively)

#include <cstdlib>

#include <exception>

#include <iostream>

#include <string>

#include <unistd.h>

#include <fstream>

#include <regex>


using namespace std;

#include "listmap.h"

#include "xpair.h"

#include "util.h"

void print(listmap<const string,
  const string,
  xless<const string>> *map){
    auto it = map->begin();
  while(it != map->end()){
  	cout << *it << endl;
  	++it;
  }
  } 
int main(int argc, char ** argv) {
  listmap<const string, const string, xless<const string>> *map 
  = new listmap<const string, const string, xless<const string>>;


 
  xpair<const string,
  const string> a("z","value");
  map->insert(a);
  //cout << *(map.find("key")) << endl;


  xpair<const string,
  const string> b("test","value2");
  map->insert(b);
  //cout << *(map.find("key2")) << endl;


  xpair<const string,
  const string> c("Vest","value2");
  map->insert(c);
   print(map);

  auto it = map->begin();
  while(it != map->end()){
  	cout << *it << endl;
  	++it;
  }
  cout << "Finished a print" << endl;
  map->erase(map->find("z"));
  it = map->begin();
  while(it != map->end()){
  	cout << *it << endl;
  	++it;
  }
  cout << "Finished a print" << endl;
  map->erase(map->find("test"));
  it = map->begin();
  while(it != map->end()){
  	cout << *it << endl;
  	++it;
  }
  cout << "Finished a print" << endl;
  delete(map);
}
