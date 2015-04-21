/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 20, 2015
 * UppercasingSPA.cpp

 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * Implementation of a stream processing algorithm that ...
 *
 */

#include "UppercasingSPA.h"

using namespace hw3;

UppercasingSPA::UppercasingSPA(
   istream &in,
   ostream &out)
   : StreamProcessorAlgorithm(in, out)
{

}

bool
UppercasingSPA::filterToken(const string &token) const
{
   return false;
}

void 
UppercasingSPA::processToken(string &token) const
{

}
