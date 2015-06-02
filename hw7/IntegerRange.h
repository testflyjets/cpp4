/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * June 1, 2015
 * IntegerRange.h
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * A template class that represents a range of integer values,
 * along with a bidirectional iterator that supports it.
 * 
 */

#ifndef INTEGERRANGE_H
#define INTEGERRANGE_H

#include <cassert>

#include <iterator>
using std::bidirectional_iterator_tag;

// Represents all integer values in the range [low, high).
// low must be <= high.
template <typename T>
class IntegerRange
{
public:
   class iterator;

   IntegerRange(T low, T high) : low_(low), high_(high)
   {
      assert(low <= high);
   }

   const iterator begin() const { return iterator(low_); }
   const iterator end()   const { return iterator(high_); }

private:
   const T low_, high_;
};

template <typename T>
class IntegerRange<T>::iterator
   : public std::iterator<bidirectional_iterator_tag, T>
{
public:
   // default constructor
   iterator() : pData_(0)
   {}

   // constructor from T *
   explicit iterator(T pData) : pData_(pData)
   {}

   // preincrement
   iterator &operator++()
   {
      ++pData_;
      return *this;
   }

   // postincrement
   iterator &operator++(int)
   {
      iterator temp(*this);
      operator++();
      return temp;
   }

   // predecrement
   iterator &operator--()
   {
      --pData_;
      return *this;
   }

   // postdecrement
   iterator &operator--(int)
   {
      iterator temp(*this);
      operator--();
      return temp;
   }

   // operator==
   bool operator==(const iterator &other) const
   {
      return pData_ == other.pData_;
   }

   // operator!=
   bool operator!=(const iterator &other) const
   {
      return !operator==(other);
   }

   // operator* r-value
   const T &operator*() const
   {
      return pData_;
   }

   // operator* l-value
   T &operator*()
   {
      return pData_;
   }

   // operator-> r-value
   const T *operator->() const
   {
      return pData_;
   }

   // operator-> l-value
   T *operator->()
   {
      return pData_;
   }

private:
   T pData_;
};

#endif