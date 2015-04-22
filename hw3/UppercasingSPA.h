/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 20, 2015
 * UppercasingSPA.h

 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * A concrete implementation of the StreamProcessingAlgorigthm
 * that operates as follows:
 *    - filter: passes through all tokens
 *    - process: converts all characters in the token to their uppercase form
 *      if an uppercase exists, otherwise leaves characters as-is
 */

#ifndef UPPERCASINGSPA_H
#define UPPERCASINGSPA_H

#include "StreamProcessorAlgorithm.h"

namespace hw3
{
   class UppercasingSPA : public StreamProcessorAlgorithm
   {
   public:
      UppercasingSPA(istream &in, ostream &out);
      ~UppercasingSPA();
  
   private:
      bool filterToken(const string &token) const;
      void processToken(string &token) const;
   };
}

#endif