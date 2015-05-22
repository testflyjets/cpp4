
#include <algorithm>
using std::copy;

#include <iostream>
using std::cout;

#include <iterator>
using std::ostream_iterator;

#include <sstream>
using std::ostringstream;

#include <string>
using std::string;

#include "UnitTest++.h"

#include "IntegerRange.h"

struct IteratorStringstreamFixture
{
   IteratorStringstreamFixture()
   {
   }

   ~IteratorStringstreamFixture()
   {
   }

   ostringstream oss;
};

TEST_FIXTURE(IteratorStringstreamFixture, CopyShortRangeToOutputStream)
{
   IntegerRange<short> r1(-5, 0);
   copy(r1.begin(), r1.end(), ostream_iterator<short>(oss, " "));

   string expected = "-5 -4 -3 -2 -1 ";
   CHECK_EQUAL(expected, oss.str());
}

TEST_FIXTURE(IteratorStringstreamFixture, CopyIntRangeToOutputStream)
{
   IntegerRange<int> r1(-2, 3);
   copy(r1.begin(), r1.end(), ostream_iterator<int>(oss, " "));

   string expected = "-2 -1 0 1 2 ";
   CHECK_EQUAL(expected, oss.str());
}

TEST_FIXTURE(IteratorStringstreamFixture, CopyUnsignedRangeToOutputStream)
{
   IntegerRange<unsigned> r2(0, 6);
   copy(r2.begin(), r2.end(), ostream_iterator<unsigned>(oss, " ")); 
   
   string expected = "0 1 2 3 4 5 ";
   CHECK_EQUAL(expected, oss.str());
}

TEST_FIXTURE(IteratorStringstreamFixture, CopyLongRangeToOutputStream)
{
   IntegerRange<long> r2(10, 16);
   copy(r2.begin(), r2.end(), ostream_iterator<long>(oss, " ")); 
   
   string expected = "10 11 12 13 14 15 ";
   CHECK_EQUAL(expected, oss.str());
}

int main() {
   cout << "Running tests for C4 HW7 - IntegerRange::iterator..." << "\n\n";

   int result = UnitTest::RunAllTests();

   cout << "\n";

   return result;
}