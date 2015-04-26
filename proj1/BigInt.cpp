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

#include <iostream>
using std::istream;
using std::ostream;

#include <string>
using std::string;

#include "BigInt.h"

Project1::BigInt::BigInt()
: pos(true)
{
   val.push_back(0);
}

Project1::BigInt::BigInt(const BigInt &bi)
: pos(bi.pos)
{

}

Project1::BigInt::BigInt(long long ll)
: pos(ll > 0)
{

}

Project1::BigInt::BigInt(const string &strInt)
{

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
Project1::operator<<(ostream &os, const BigInt &bi)
{
   return os;
}

istream &
Project1::operator>>(istream &is, BigInt &bi)
{
   return is;
}