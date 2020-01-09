// $Id: ubigint.cpp,v 1.16 2019-04-02 16:28:42-07 - - $
// Edwin Wang and Andrew Lyle (ekwang and alyle respectively)

#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include <string>
#include <bits/stdc++.h> 
using namespace std;

#include "ubigint.h"
#include "debug.h"

ubigint::ubigint (unsigned long that){
  DEBUGF ('~', this << " -> " << that);
  while (that!=0){
    ubig_value.push_back(that%10+48);
    that/=10;
    
  }
  if(ubig_value.size()==0){
        ubig_value.push_back('0');
  }
} 
ubigint::ubigint (ubigvalue_t that){
  ubig_value=that;
} 

ubigint::ubigint (const string& that) {
  DEBUGF ('~', "that = \"" << that << "\"");
    
  for (char digit: that) {
    if (not isdigit (digit)) {
      throw invalid_argument ("ubigint::ubigint(" + that + ")");
    }
    ubig_value.push_back(digit);
  }
  reverse(ubig_value.begin(),ubig_value.end());
}


ubigint ubigint::operator+ (const ubigint& that) const {

  auto iter1= that.ubig_value.begin();
  auto iter2= ubig_value.begin();
  int carryIn=0;
  string val="";
  ubigvalue_t result;

  while (iter1 <that.ubig_value.end()||iter2 <ubig_value.end()){

    int value1=0;
    if(iter1 <that.ubig_value.end())
      value1=*iter1-48;

    int value2=0;
    if(iter2 <ubig_value.end())
      value2=*iter2-48;
    

    int added = value1+value2+ carryIn;
    carryIn=added/10;
    char digit= (added%10+48);

    result.push_back(digit);
    iter1++;
    iter2++;
  }
if (carryIn !=0)
    result.push_back(carryIn+48);

  int index= result.size()-1;
  while(result.at(index)=='0'&&index!=0){
    result.pop_back();
    index--;
  }
  return {result};

}


ubigint ubigint::operator- (const ubigint& that) const {
  
  if(that.ubig_value.size()>ubig_value.size()){
    cout << "Failed because value one is less than value two";
    cout << *this<< " " << that;
    exit (EXIT_FAILURE);
  }
  if(that.ubig_value.size()==ubig_value.size()){
    auto itera= ubig_value.end()-1;
    auto iterb= that.ubig_value.end()-1;
    bool cont=true;
    while (itera >= ubig_value.begin()
        &&iterb >= that.ubig_value.begin()
        &&cont){
      if(*itera<*iterb){
        cout << "Failed because value one is less than value two";
            cout << *this<< " " << that;
        exit (EXIT_FAILURE);
      }else if (*itera>*iterb){
        cont= false;
      }
      itera--;
      iterb--;
    }
    
  }
  
  auto iter1= ubig_value.begin();
  auto iter2= that.ubig_value.begin();
  int carryIn=0;
  string val="";
  ubigvalue_t result;
  while (iter1 <ubig_value.end()||iter2 <that.ubig_value.end()){

    int value1=0;
    if(iter1 <ubig_value.end())
      value1=*iter1-48;

    int value2=0;
    if(iter2 <that.ubig_value.end())
      value2=*iter2-48;
    

    int added = value1-value2+ carryIn;
    if(added<0){
      carryIn=-1;
      added+=10;
    }else{
        carryIn=0;
    }
    char digit= (added+48);

    result.push_back(digit);
    iter1++;
    iter2++;
  }
  
  int index= result.size()-1;
  while(result.at(index)=='0'&&index!=0){
    result.pop_back();
    index--;
  }
  
  return {result};

}

ubigint ubigint::operator* (const ubigint& that) const {
  vector<int> intVals(ubig_value.size()+that.ubig_value.size());

  ubigvalue_t result(ubig_value.size()+that.ubig_value.size());
  unsigned int i=0;
  
  for(char a :ubig_value){
    int j=0;
    for(char b :that.ubig_value){
      intVals.at(i+j)=(a-48)*(b-48)+intVals.at(i+j);
      j++;
    }
    i++;
  }

  unsigned int ind=0;

  for(i = 0; i < result.size(); i++){
    if(ind+1<result.size()){
      intVals.at(ind+1)+=intVals.at(ind)/10;
        intVals.at(ind)%=10;
      result.at(ind)=intVals.at(ind)+48;
      ind++;

    }else{
        result.at(ind)=intVals.at(ind)+48;
    }
  }

  int index= result.size()-1;
  while(result.at(index)=='0'&&index!=0){
   result.pop_back();
   index--;
  }

  return {result};
} 



void ubigint::multiply_by_2() {
   *this= (*this) * 2;
}

void ubigint::divide_by_2() {
  auto iter= ubig_value.end()-1;
  int carryIn=0;
  ubigvalue_t result;

  while (iter >=ubig_value.begin()){
    int valueAtIndex= *iter-48+carryIn;
    result.push_back(valueAtIndex/2+48);
    carryIn = (valueAtIndex%2)*10;    
    iter--;
  }
  reverse(result.begin(), result.end());
  int index= result.size()-1;
  while(result.at(index)=='0'&&index!=0){
    result.pop_back();
    index--;
  }
  ubig_value =result ;

}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, const ubigint& divisor_) {
   // NOTE: udivide is a non-member function.
   ubigint divisor {divisor_};
   ubigint zero {0};
   if (divisor == zero) throw domain_error ("udivide by zero");
   ubigint power_of_2 {1};
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   return {.quotient = quotient, .remainder = remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return udivide (*this, that).quotient;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return udivide (*this, that).remainder;
}

bool ubigint::operator== (const ubigint& that) const {
  if(ubig_value.size()!=that.ubig_value.size()){
    return false;
  }
  if(that.ubig_value.size()==ubig_value.size()){
    auto itera= ubig_value.begin();
    auto iterb= that.ubig_value.begin();

    while (itera !=ubig_value.end()&&iterb !=that.ubig_value.end()){
      if(*itera!=*iterb){
        return false;
      }
      itera++;
      iterb++;
    }
    
  }
  return true;
}

bool ubigint::operator< (const ubigint& that) const {
  if(ubig_value.size()<that.ubig_value.size()){
    return true;
  }else if(ubig_value.size()>that.ubig_value.size()){
    return false;
  }

    auto itera= ubig_value.end()-1;
    auto iterb= that.ubig_value.end()-1;
    while (itera >=ubig_value.begin()&&iterb >=that.ubig_value.begin()){
      if (*itera>*iterb)
        return false;
      if (*itera<*iterb)
        return true;
      itera--;
      iterb--;
    }
    
  
  return false;
}

bool ubigint::operator> (const ubigint& that) const {
  if (*this < that || *this == that){
    return false;
  }

  return true;
}
bool ubigint::operator>= (const ubigint& that) const {
  if (*this < that){
    return false;
  }
  return true;
}
bool ubigint::operator<= (const ubigint& that) const {
  if (*this > that){
    return false;
  }
  return true;
}
bool ubigint::operator!= (const ubigint& that) const {
  if (*this == that){
    return false;
  }
  return true;
}


ostream& operator<< (ostream& out, const ubigint& that) { 
  string outStr="";

  for(char digit: that.ubig_value){
    outStr+=digit;
  }
  reverse(outStr.begin(),outStr.end());

  return out << outStr;
}





