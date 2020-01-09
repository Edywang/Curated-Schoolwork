// $Id: listmap.h,v 1.17 2019-10-25 14:56:22-07 - - $
// Edwin Wang and Andrew Lyle (ekwang and alyle respectively)

#ifndef __LISTMAP_H__
#define __LISTMAP_H__

#include "xless.h"
#include "xpair.h"
#include <iostream>
using namespace std;

template <typename key_t, typename mapped_t, class less_t=xless<key_t>>
class listmap {
   public:
      using key_type = key_t;
      using mapped_type = mapped_t;
      using value_type = xpair<const key_type, mapped_type>;
   private:
      less_t less;
      struct node;
      struct link {
         node* next{};
         node* prev{};
         link (node* next_, node* prev_): next(next_), prev(prev_){}
      };
      struct node: link {
         value_type value{};
         node (node* next, node* prev, const value_type&);
      };
      node* anchor() { return static_cast<node*> (&anchor_); }
      link anchor_ {anchor(), anchor()};
   public:
      class iterator;
      listmap(){};
      listmap (const listmap&);
      listmap& operator= (const listmap&);
      ~listmap();
      iterator insert (const value_type&);
      iterator find (const key_type&);
      iterator erase (iterator position);
      iterator begin() { return anchor()->next; }
      iterator end() { return anchor(); }
      bool empty() const { return anchor_->next == anchor_; }
};
 

template <typename key_t, typename mapped_t, class less_t>
class listmap<key_t,mapped_t,less_t>::iterator {
   private:
      friend class listmap<key_t,mapped_t,less_t>;
      listmap<key_t,mapped_t,less_t>::node* where {nullptr};
      iterator (node* where_): where(where_){};
   public:
      iterator(){}
      value_type& operator*();
      value_type* operator->(); 
      iterator& operator++(); //++itor
      iterator& operator--(); //--itor
      void erase();
      bool operator== (const iterator&) const;
      bool operator!= (const iterator&) const;
};

#include "listmap.tcc"
#endif
