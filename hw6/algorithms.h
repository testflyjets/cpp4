/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * May 18, 2015
 * algorithms.h
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * The header file that defines two algorithms, palindrome
 * and compress.
 * 
 */

#ifndef CHRISMCCANN_HW6_ALGORITHMS_H
#define CHRISMCCANN_HW6_ALGORITHMS_H

#include <algorithm>
using std::equal;

#include <iterator>

namespace ChrisMcCann { namespace hw6 {

   template <typename BidirectionalIterator>
   bool palindrome(BidirectionalIterator first, BidirectionalIterator last)
   {
      for (; first != last && first != --last; ++first)
      if (*first != *last)
         return false;

      return true;
   }

   template <typename ForwardIterator, typename OutputIterator>
   void compress(ForwardIterator first, ForwardIterator last, OutputIterator result)
   {
      if (first != last)
      {
         // always add the first element
         result = *first;

         // sequence through the rest of the elements,
         // add the next element if it's not the same
         // as the previous one
         ForwardIterator next = first; 
         ++next;
         while (next != last)
         {
            if (*next != *first)
            {
               result = *next;
            }
            ++first;
            ++next;
         }
      }
   }
}}

#endif