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
   const iterator end() const { return iterator(high_); }
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
   explicit iterator(T *pData) : pData_(pData)
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

   // operator !=
   bool operator!=(const iterator &other) const
   {
      return !operator==(other);
   }



private:
   T * pData_;
};

#endif