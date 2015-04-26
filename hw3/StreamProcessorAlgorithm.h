/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 20, 2015
 * StreamProcessingAlgorithm.h

 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * StreamProcessorAlgorithm is an implementation of a
 * stream processing algorithm using the Template Method
 * design pattern.
 */

#ifndef STREAMPROCESSORALGORITHM_H
#define STREAMPROCESSORALGORITHM_H

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

      // For each whitespace separated string (token) read from the input stream:
      //  - If the token passes through the filter (i.e. filterToken returns true):
      //    - Process the token and output it to the output stream
      void process();

   private:
      // determines if a token is passed through for processing
      virtual bool filterToken(const string &token) const = 0;
      // processes tokens, possibly modifying them
      virtual void processToken(string &token) const = 0;

      // the input stream from which tokens are parsed
      istream &in_;
      // the output stream to which tokens are written
      ostream &out_;
   };
}

#endif
