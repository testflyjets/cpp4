/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 13, 2015 
 * BigInt.h
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 * 
 * Header file for a big integer class
 */
#ifndef PROJECT1_BIGINT_H
#define PROJECT1_BIGINT_H

#include <iostream>
using std::istream;
using std::ostream;

#include <string>
using std::string;

namespace Project1 
{ 
   class BigInt 
   { 
      friend const BigInt operator+(const BigInt &, const BigInt &); 
      friend const BigInt operator-(const BigInt &, const BigInt &); 
      friend bool operator==(const BigInt &, const BigInt &); 
      friend bool operator!=(const BigInt &, const BigInt &); 
      friend bool operator<(const BigInt &, const BigInt &); 
      friend bool operator<=(const BigInt &, const BigInt &); 
      friend bool operator>(const BigInt &, const BigInt &); 
      friend bool operator>=(const BigInt &, const BigInt &); 
      friend ostream &operator<<(ostream &, const BigInt &); 
      friend istream &operator>>(istream &, BigInt &);

   public: 
      BigInt(); BigInt(const BigInt &); 
      BigInt(long long); 
      // Throws invalid_argument if string malformed (contains 
      // anything other than a legally formatted number) 
      BigInt(const string &);

      const BigInt &operator=(const BigInt &); 
      const BigInt &operator+=(const BigInt &); 
      const BigInt &operator-=(const BigInt &);

   private: 
   
   };
}

#endif