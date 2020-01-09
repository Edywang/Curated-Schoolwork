// $Id: listmap.tcc,v 1.13 2019-10-22 12:41:48-07 - - $
// Edwin Wang and Andrew Lyle (ekwang and alyle respectively)

#include "listmap.h"
#include "debug.h"
#include <iostream>
#include <string>
using namespace std;

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::node.
/////////////////////////////////////////////////////////////////
//

//
// listmap::node::node (link*, link*, const value_type&)
//
template <typename key_t, typename mapped_t, class less_t>
listmap<key_t,mapped_t,less_t>::node::node (node* next_, node* prev_,
                                     const value_type& value_):
            link (next_, prev_), value (value_) {
}

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename key_t, typename mapped_t, class less_t>
listmap<key_t,mapped_t,less_t>::~listmap() {
   DEBUGF ('l', reinterpret_cast<const void*> (this));
   while(anchor_.next != anchor()){
     erase(begin());
   }
   anchor_.next = NULL;
   anchor_.prev = NULL;
}


//
// iterator listmap::insert (const value_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::insert (const value_type& pair) {
   DEBUGF ('l', &pair << "->" << pair);
   listmap<key_t,mapped_t,less_t>::iterator it = begin();
   while(it != end()){
      // TODO: Handle capitalization
      if(it->first.compare(pair.first) < 0){
        ++it;
      }
      else{
        break;
      }
   }
   node* newNode = new node(it.where, it.where->prev, pair);
   newNode->prev->next = newNode;
   newNode->next->prev = newNode;
   return it;
}

//
// listmap::find(const key_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::find (const key_type& that) {
   DEBUGF ('l', that);
   listmap<key_t,mapped_t,less_t>::iterator it = begin();
   while(it != end()){
      // Check key and return iterator if found
      if(it->first == that){
         break;
      }
      // Iterate
      ++it;
   }
   // If not found, return end AKA anchor
   return it;
}

//
// iterator listmap::erase (iterator position)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::erase (iterator position) {
   DEBUGF ('l', &*position);
   if(position == end()){
      cerr << "Function erase() called on nonexistant node";
   }
   position.where->prev->next = position.where->next;
   position.where->next->prev = position.where->prev;
   position.where->prev = NULL;
   position.where->next = NULL;
   delete position.where;
   position.where = NULL;
   return position;
}


//
/////////////////////////////////////////////////////////////////
// Operations on listmap::iterator.
/////////////////////////////////////////////////////////////////
//

//
// listmap::value_type& listmap::iterator::operator*()
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::value_type&
listmap<key_t,mapped_t,less_t>::iterator::operator*() {
   DEBUGF ('l', where);
   return where->value;
}

//
// listmap::value_type* listmap::iterator::operator->()
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::value_type*
listmap<key_t,mapped_t,less_t>::iterator::operator->() {
   DEBUGF ('l', where);
   return &(where->value);
}

//
// listmap::iterator& listmap::iterator::operator++()
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator&
listmap<key_t,mapped_t,less_t>::iterator::operator++() {
   DEBUGF ('l', where);
   where = where->next;
   return *this;
}

//
// listmap::iterator& listmap::iterator::operator--()
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator&
listmap<key_t,mapped_t,less_t>::iterator::operator--() {
   DEBUGF ('l', where);
   where = where->prev;
   return *this;
}


//
// bool listmap::iterator::operator== (const iterator&)
//
template <typename key_t, typename mapped_t, class less_t>
inline bool listmap<key_t,mapped_t,less_t>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

//
// bool listmap::iterator::operator!= (const iterator&)
//
template <typename key_t, typename mapped_t, class less_t>
inline bool listmap<key_t,mapped_t,less_t>::iterator::operator!=
            (const iterator& that) const {
   return this->where != that.where;
}
