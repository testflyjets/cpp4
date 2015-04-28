/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 13, 2015 
 * BigInt.cpp
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 * 
 * Implementation file for a big integer class
 */
#include <cassert>
#include <cstdlib>
using std::atoi;

#include <stdexcept>
using std::invalid_argument;

#include <iostream>
using std::istream;
using std::ostream;

#include <string>
using std::string;

#include "BigInt.h"

static const int BASE = 10;

Project1::BigInt::BigInt()
: pos(true)
{
   val.push_back(0);
}

Project1::BigInt::BigInt(const BigInt &n)
:  val(n.val),
   pos(n.pos)
{

}

Project1::BigInt::BigInt(long long ll)
: pos(ll >= 0)
{
   val.clear();

   if (!pos)
   {
      ll = -ll;
   }

   do
   {
      lldiv_t dt = lldiv(ll, BASE);
      val.push_back((int)dt.rem);
      ll = dt.quot;
   } while (ll > 0);
}

Project1::BigInt::BigInt(const string &strInt)
{
   fromString(strInt);
}

const Project1::BigInt &
Project1::BigInt::operator=(const BigInt &rhs)
{
   BigInt temp(rhs);
   swap(temp);
   return *this;
}

const Project1::BigInt &
Project1::BigInt::operator+=(const BigInt &rhs)
{
   // if the rhs value has more digits, resize 
   // to match and set values to 0
   if (rhs.val.size() > val.size())
   {
      val.resize(rhs.val.size(), 0);
   }

   // add the corresponding elements from each
   // side, handling the case of negative numbers
   for (size_t i = 0; i < val.size(); ++i)
   {
      val[i] = (pos ? val[i] : -val[i]) + 
         (i < rhs.val.size() ? 
            (rhs.pos ? 
               rhs.val[i] : 
               -rhs.val[i]) 
            : 0);
   }
   
   // normalize the sign, digits, and leading zeroes
   normalize(false);

   return *this;
}

const Project1::BigInt &
Project1::BigInt::operator-=(const BigInt &rhs)
{
   // if the rhs value has more digits, resize 
   // to match and set values to 0
   if (rhs.val.size() > val.size())
   {
      val.resize(rhs.val.size(), 0);
   }

   // subtract the corresponding elements from each
   // side, handling the case of negative numbers
   for (size_t i = 0; i < val.size(); ++i)
   {
      val[i] = (pos ? val[i] : -val[i]) - 
         (i < rhs.val.size() ? 
            (rhs.pos ? 
               rhs.val[i] : 
               -rhs.val[i]) 
            : 0);
   }
   
   // carry digits and fix the sign as required
   normalize(false);

   return *this;
}

const Project1::BigInt 
Project1::operator+(const BigInt &lhs, const BigInt &rhs)
{  
   BigInt result(lhs);
   result += rhs;

   return result;
}

const Project1::BigInt
Project1::operator-(const BigInt &lhs, const BigInt &rhs)
{
   BigInt result(lhs);
   result -= rhs;

   return result;
}

bool Project1::operator==(const BigInt &lhs, const BigInt &rhs)
{
   // if the signs and lengths differ, they aren't equal
   if (lhs.pos != rhs.pos || lhs.val.size() != rhs.val.size())
   {
      return false;
   }

   // compare individual digits for equality
   for (int i = (int)lhs.val.size() - 1; i >= 0; --i)
   {
      if (lhs.val[i] != rhs.val[i])
      {
         return false;
      }
   }
   return true;
}

bool Project1::operator!=(const BigInt &lhs, const BigInt &rhs)
{
   return !(lhs == rhs);
}

bool Project1::operator<(const BigInt &lhs, const BigInt &rhs)
{
   // if the numbers have opposite signs then the
   // negative number is less
   if (lhs.pos && !rhs.pos)
   {
      return false;
   }
   if (!lhs.pos && rhs.pos)
   {
      return true;
   }

   // if the numbers have the same sign and one
   // has more digits than the other
   if (lhs.val.size() > rhs.val.size())
   {
      return lhs.pos ? false : true;
   }

   if (lhs.val.size() < rhs.val.size())
   {
      return lhs.pos ? true : false;
   }

   // if the numbers have the same sign and the
   // same number of digits, compare individual digits
   // beginning with the least significant digit
   for (int i = (int)lhs.val.size() - 1; i >= 0; --i)
   {
      if (lhs.val[i] < rhs.val[i])
      {
         return lhs.pos ? true : false;
      }

      if (lhs.val[i] > rhs.val[i])
      {
         return lhs.pos ? false : true;
      }
   }

   return false;
}

bool Project1::operator<=(const BigInt &lhs, const BigInt &rhs)
{
   return lhs < rhs || lhs == rhs;
}

bool Project1::operator>(const BigInt &lhs, const BigInt &rhs)
{
   return rhs < lhs;
}

bool Project1::operator>=(const BigInt &lhs, const BigInt &rhs)
{
   return lhs > rhs || lhs == rhs;
}

ostream &
Project1::operator<<(ostream &os, const BigInt &n)
{
    if (!n.pos)
    {
        os << '-';
    }

    for (int i = (int) n.val.size() - 1; i >= 0; --i)
    {
      os << n.val[i];
    }

    return os;
}

istream &
Project1::operator>>(istream &is, BigInt &n)
{
   string str;

   is >> str;
   n.fromString(str);

   return is;
}

void 
Project1::BigInt::swap(BigInt &other)
{
   // swap the digits and sign of two numbers
   vector<int> tempVal(other.val);
   other.val = val;
   val = tempVal;

   bool tempPos(other.pos);
   other.pos = pos;
   pos = tempPos;
}

void
Project1::BigInt::fromString(const string &s)
{
   pos = true;
   val.clear();

   // character position of the most significant digit
   int posMSD = 0;

   // an empty string is invalid
   if (s.length() == 0)
   {
      throw invalid_argument("number string empty");
   }

   // a string of more than one zero is invalid
   if (s.length() > 1 && s == string(s.length(), '0'))
   {
      throw invalid_argument("malformed number string");
   }

   // check the string for a sign
   if (s[0] == '-')
   {
      pos = false;
      posMSD = 1;
   }
   if (s[0] == '+')
   {
      posMSD = 1;
   }

   // just a plus or minus sign alone is invalid
   if (posMSD == 1 && s.length() == 1)
   {
      throw invalid_argument("malformed number string");
   }

   string digit;
   // start at least significant digit
   for (int k = s.length() - 1; k >= posMSD; k--)
   {
      if (!isdigit(s[k]))
      {
         throw invalid_argument("malformed number string");
      }
      digit = s.substr(k, 1);
      val.push_back(atoi(digit.c_str()));
   }

   // normalize the number; it already has a valid sign
   normalize(true);
}

void
Project1::BigInt::normalize(const bool hasValidSign)
{
   truncateToBase();

   // don't allow -0 (negative zero)
   if (val.size() == 1 && val[0] == 0)
   {
      pos = true;
   }

   if (equalizeSigns())
   {
      pos = ((val.size() == 1 && val[0] == 0) || !hasValidSign) ? true : pos;
   }
   else
   {
      pos = hasValidSign ? !pos : false;
      for (size_t i = 0; i < val.size(); ++i)
      {
         val[i] = abs(val[i]);
      }
   }

   removeLeadingZeroes();
}

bool
Project1::BigInt::equalizeSigns()
{
   bool isPositive = true;
   int i = (int)((val.size())) - 1;
   for (; i >= 0; --i)
   {
      if (val[i] != 0)
      {
         isPositive = val[i--] > 0;
         break;
      }
   }

   if (isPositive)
   {
      for (; i >= 0; --i)
      {
         if (val[i] < 0)
         {
            int k = 0, index = i + 1;
            // count adjacent zeros on left
            for (; (size_t)(index) < val.size() && val[index] == 0; ++k, ++index); 
            { 
               // number on the left is positive
               val[index] -= 1;
               val[i] += BASE;
               for (; k > 0; --k)
               {
                  val[i + k] = 9;
               }
            }
         }
      }
   }
   else
   {
      for (; i >= 0; --i)
      {
         if (val[i] > 0)
         {
            int k = 0, index = i + 1;
            // count adjacent zeros on right
            for (; (size_t)(index) < val.size() && val[index] == 0; ++k, ++index); 
            { 
               // number on the left is negative
               val[index] += 1;
               val[i] -= BASE;
               for (; k > 0; --k)
               {
                  val[i + k] = -9;
               }
            }
         }
      }
   }

   return isPositive;
}

void 
Project1::BigInt::truncateToBase()
{
   // truncate each digit to the base value
   // and carry base overflows up to the next
   // digit
   for (size_t i = 0; i < val.size(); ++i) 
   {
      if (val[i] >= BASE || val[i] <= -BASE)
      {
         div_t dt = div(val[i], BASE);
         val[i] = dt.rem;
         if (i + 1 >= val.size())
         {
            val.push_back(dt.quot);
         }
         else
         {
            val[i + 1] += dt.quot;
         }
      }
   }
}

void
Project1::BigInt::removeLeadingZeroes()
{
   for (int i = (int)(val.size()) - 1; i > 0; --i) 
   {
      if (val[i] != 0)
      {
         return;
      }
      else
      {
         val.erase(val.begin() + i);
      }
   }
}