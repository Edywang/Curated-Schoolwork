// $Id: bigint.cpp,v 1.78 2019-04-03 16:44:33-07 - - $
// Edwin Wang and Andrew Lyle (ekwang and alyle respectively)
 
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include <iomanip> 
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint (long that){
  if (that<0){
    is_negative=true;
    that*=-1;
  }
  uvalue=ubigint{static_cast<std::make_unsigned
  <decltype(that)>::type>(that)};
  //make long unsigned and positive
  DEBUGF ('~', this << " -> " << uvalue)
}

bigint::bigint (const ubigint& uvalue_, bool is_negative_):
                uvalue(uvalue_), is_negative(is_negative_) {
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+ () const {
   return *this;
}

bigint bigint::operator- () const {
   return {uvalue, not is_negative};
}

bigint bigint::operator+ (const bigint& that) const {
  // Negative this + Non-Negative that, would generally be that - this
  if(is_negative and not that.is_negative){
    // This <= that, easy case
    if(uvalue <= that.uvalue){
      return {that.uvalue - uvalue, false};
    }
    // Effectively this > that, harder case
    else {
      return {uvalue - that.uvalue, true};
    }
  }
  // Non-Negative this + Negative that, would generally be this - that
  else if(not is_negative and that.is_negative){
    // This >= that, easy case
    if(uvalue >= that.uvalue){
      return {uvalue - that.uvalue, false};
    }
    // Effectively this > that, harder case
    else {
      return {that.uvalue - uvalue, true};
    }
  }
  // Same signs, simple addition
  else {
    return {uvalue + that.uvalue, is_negative};
  }
}

bigint bigint::operator- (const bigint& that) const {
  // Different signs, easy case
    if((is_negative and not that.is_negative) 
         or (not is_negative and is_negative))
    return {uvalue + that.uvalue, is_negative};
  // Same signs, slightly harder
  else {
    if(uvalue == that.uvalue)
      return {false};
    else if(uvalue > that.uvalue)
      return {uvalue - that.uvalue, is_negative};
    // uvalue < that.uvalue
    else
      return {that.uvalue - uvalue, not is_negative};
  }
}

bigint bigint::operator* (const bigint& that) const {
  bigint result;
  if(uvalue == 0 or that.uvalue == 0)
    return {false};
  else if(is_negative == that.is_negative)
    return {uvalue * that.uvalue, false};
  else
    return {uvalue * that.uvalue, true};
  return result;
}

bigint bigint::operator/ (const bigint& that) const {
   bigint result;
  if(uvalue == 0){
      return {false};
  }
  else if(is_negative == that.is_negative)
    return {uvalue / that.uvalue, false};
  else
    return {uvalue / that.uvalue, true};
}

bigint bigint::operator% (const bigint& that) const {
    return {uvalue % that.uvalue, is_negative};
}

bool bigint::operator== (const bigint& that) const {
   return is_negative == that.is_negative and uvalue == that.uvalue;
}

bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that) {
   ostringstream stream;
   stream << (that.is_negative ? "-" : "") << that.uvalue;
   string str =  stream.str();
   for ( int i =0; i< static_cast<int> (str.length()); i++){
      if (i%69 ==0&& i!=0){
         out << "\\"<<endl;
      }  
   out << str[i];
   }
return out ;
   
}

