/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 20, 2015
 * StreamProcessingAlgorithm.h

 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * StreamProcessingAlgorithm is an implementation of a
 * stream processing algorithm using the Template Method
 * design pattern.
 */

#ifndef STREAMPROCESSINGALGORITHM_H
#define STREAMPROCESSINGALGORITHM_H

#include <iostream>
using std::istream;
using std::ostream;

#include <string>
using std::string;

namespace hw3 
{
   class StreamProcessorAlgorithm
   {
   public:
      StreamProcessorAlgorithm(istream &in, ostream &out);
      virtual ~StreamProcessorAlgorithm();

      // process():
      //
      // For each whitespace separated string (token) read from the input stream:
      // If the token passes through the filter (i.e. filterToken returns true):
      // Process the token and output it to the output stream
      void process();

   private:
      virtual bool filterToken(const string &token) const = 0;
      virtual void processToken(string &token) const = 0;
      istream &in_;
      ostream &out_;
   };
}

#endif
