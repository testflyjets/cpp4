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
: pos(ll > 0)
{

}

Project1::BigInt::BigInt(const string &strInt)
{
   fromString(strInt);
}

const Project1::BigInt &
Project1::BigInt::operator=(const BigInt &rhs)
{
   // see pp. 82-83 in course notes (Ray: "use this approach")
   // BigInt temp(rhs);
   // Swap(temp);
   // return *this;
   return rhs;
}

const Project1::BigInt &
Project1::BigInt::operator+=(const BigInt &rhs)
{
   return rhs;
}

const Project1::BigInt &
Project1::BigInt::operator-=(const BigInt &rhs)
{
   return rhs;
}

const Project1::BigInt 
Project1::operator+(const BigInt &lhs, const BigInt &rhs)
{
   return lhs;
}

const Project1::BigInt
Project1::operator-(const BigInt &lhs, const BigInt &rhs)
{
   return lhs;
}

bool Project1::operator==(const BigInt &lhs, const BigInt &rhs)
{
   return true;
}

bool Project1::operator!=(const BigInt &lhs, const BigInt &rhs)
{
   return true;
}

bool Project1::operator<(const BigInt &lhs, const BigInt &rhs)
{
   return true;
}

bool Project1::operator<=(const BigInt &lhs, const BigInt &rhs)
{
   return true;
}

bool Project1::operator>(const BigInt &lhs, const BigInt &rhs)
{
   return true;
}

bool Project1::operator>=(const BigInt &lhs, const BigInt &rhs)
{
   return true;
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
Project1::operator>>(istream &is, BigInt &bi)
{
   return is;
}

void
Project1::BigInt::fromString(const string &s)
{
   pos = true;
   val.clear();

   // character position of most significant digit
   int posMSD = 0;

   if (s.length() == 0)
   {
      return;
   }

   if (s[0] == '-')
   {
      pos = false;
      posMSD = 1;
   }

   if (s[0] == '+')
   {
      posMSD = 1;
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
}

size_t
Project1::BigInt::numberOfDigits() const
{
   return val.size();
}