
#include <algorithm>
using std::copy;

#include <iostream>
using std::cout;

#include <iterator>
using std::ostream_iterator;

#include "UnitTest++.h"

#include "IntegerRange.h"

TEST(CopyIntRangeToOutputStream)
{
   IntegerRange<int> r1(-2, 3);
   copy(r1.begin(), r1.end(), ostream_iterator<int>(cout, " ")); // -2 -1 0 1 2
}

TEST(CopyUnsignedRangeToOutputStream)
{
   IntegerRange<unsigned> r2(0, 6);
   //copy(r2.begin(), r2.end(), ostream_iterator<unsigned>(cout, " ")); // 0 1 2 3 4 5
}

int main() {
   cout << "Running tests for C4 HW7 - IntegerRange::iterator..." << "\n\n";

   int result = UnitTest::RunAllTests();

   cout << "\n";

   return result;
}