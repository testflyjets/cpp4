/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 20, 2015
 * DigitStrippingSPA.h

 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * A concrete implementation of the StreamProcessingAlgorigthm
 * that ...
 */

#ifndef DIGITSTRIPPINGSPA_H
#define DIGITSTRIPPINGSPA_H

#include "StreamProcessingAlgorithm.h"

namespace hw3
{
   class DigitStrippingSPA : public StreamProcessorAlgorithm
   {
   public:
      DigitStrippingSPA(istream &in, ostream &out);
      virtual ~DigitStrippingSPA();

      // process():
      //
      void process();
   
   private:
      bool filterToken(const string &token) const = 0;
      void processToken(string &token) const = 0;
   };
}

#endif