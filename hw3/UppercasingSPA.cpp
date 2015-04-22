/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 20, 2015
 * UppercasingSPA.cpp

 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * Implementation of a stream processing algorithm that 
 * allows all tokens to pass through and converts to upper 
 * case all letters in the tokens that pass through.
 *
 */

#include <cctype>

#include "UppercasingSPA.h"

using namespace hw3;

UppercasingSPA::UppercasingSPA(
   istream &in,
   ostream &out)
   : StreamProcessorAlgorithm(in, out)
{

}

UppercasingSPA::~UppercasingSPA()
{

}

bool
UppercasingSPA::filterToken(const string &token) const
{
   return true;
}

void 
UppercasingSPA::processToken(string &token) const
{
   for (size_t i = 0; i < token.length(); ++i)
   {
      token[i] = toupper(token[i]);
   }
}
