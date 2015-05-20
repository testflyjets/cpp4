#ifndef INTEGERRANGE_H
#define INTEGERRANGE_H

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

#endif