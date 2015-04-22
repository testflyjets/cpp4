/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 20, 2015
 * StreamProcessingAlgorithm.cpp

 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * Implementation of a stream processing algorithm using the 
 * Template Method design pattern.
 */

#include <string>
using std::string;

#include "StreamProcessorAlgorithm.h"
using namespace hw3;

StreamProcessorAlgorithm::StreamProcessorAlgorithm(
   istream &in, 
   ostream &out)
   : in_(in),
     out_(out)
{
}

StreamProcessorAlgorithm::~StreamProcessorAlgorithm()
{
   // nothing to do here -- all the member vars are automatics
}

void
StreamProcessorAlgorithm::process()
{
   string token;

   // read tokens via the stream extraction operator
   while (in_ >> token)
   {
      if (filterToken(token))
      {
         processToken(token);
         out_ << token;
      }
   }
}
