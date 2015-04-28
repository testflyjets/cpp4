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

#include <vector>
using std::vector;

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
      BigInt(); 
      BigInt(const BigInt &); 
      BigInt(long long); 
      // Throws invalid_argument if string malformed (contains 
      // anything other than a legally formatted number) 
      BigInt(const string &);

      const BigInt &operator=(const BigInt &); 
      const BigInt &operator+=(const BigInt &); 
      const BigInt &operator-=(const BigInt &);

   private: 
      // create a BigInt from a string
      void fromString(const string &);
      // swap contents between this and another instance
      void swap(BigInt &);

      // the number of digits
      size_t numberOfDigits() const;

      // correct the sign of the number
      void correctSign(const bool hasValidSign = true);
      bool equalizeSigns();

      // truncate individual digits to the base value,
      // effectively doing the "carry the 1" action
      void truncateToBase();

      // remove leading zeroes
      void removeLeadingZeroes();

      vector<int> val;
      bool pos;
   };
}

#endif