/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 20, 2015
 * DigitStrippingSPA.cpp

 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * Implementation of a stream processing algorithm that ...
 */

#include <string>

#include "DigitStrippingSPA.h"
using namespace hw3;

const static string DIGITS = "0123456789";

DigitStrippingSPA::DigitStrippingSPA(
   istream &in,
   ostream &out)
   : StreamProcessorAlgorithm(in, out)
{
}

DigitStrippingSPA::~DigitStrippingSPA()
{

}

bool
DigitStrippingSPA::filterToken(const string &token) const
{
   return token.find_first_of(DIGITS) != std::string::npos;
}

void
DigitStrippingSPA::processToken(string &token) const
{
   size_t found = token.find_first_of(DIGITS);
   while (found != std::string::npos)
   {
      token.erase(found, 1);
      found = token.find_first_of(DIGITS, found);
   }
}