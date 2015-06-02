/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * Nune 1, 2015
 * hw7.cpp
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * A test program for an implementation of a templated integer range
 * class and its bidirectional iterator.
 * 
 */

#include <algorithm>
using std::any_of;
using std::copy;
using std::count_if;
using std::equal;
using std::transform;

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

TEST(AnyOfShortIntegerRange)
{
   IntegerRange<short> r1(-5, 1);
   
   // any_of will return true if the predicate (s>0) is true for
   // any element in the iterator range.  Since IntegerRange does
   // not include the end element, the predicate should not return
   // true.
   CHECK(!any_of(r1.begin(), r1.end(), [](short s){ return s > 0; }));
}

TEST_FIXTURE(IteratorStringstreamFixture, CopyIntRangeToOutputStream)
{
   IntegerRange<int> r1(-2, 3);
   copy(r1.begin(), r1.end(), ostream_iterator<int>(oss, " "));

   string expected = "-2 -1 0 1 2 ";
   CHECK_EQUAL(expected, oss.str());
}

bool IsNegative(int i) { return i < 0; }

TEST(CountIfNegativeIntIntegerRange)
{
   IntegerRange<int> r1(-2, 3);
   int negativeCount = count_if(r1.begin(), r1.end(), IsNegative);
   
   // expect 2 values in range to be negative
   int expectedCount = 2;
   CHECK_EQUAL(expectedCount, negativeCount);
}

TEST_FIXTURE(IteratorStringstreamFixture, CopyUnsignedRangeToOutputStream)
{
   IntegerRange<unsigned> r2(0, 6);
   copy(r2.begin(), r2.end(), ostream_iterator<unsigned>(oss, " ")); 
   
   string expected = "0 1 2 3 4 5 ";
   CHECK_EQUAL(expected, oss.str());
}

TEST(EqualUnsignedIntegerRanges)
{
   IntegerRange<unsigned> r1(0, 6);
   IntegerRange<unsigned> r2(0, 6);

   CHECK(equal(r1.begin(), r1.end(), r2.begin()));

   IntegerRange<unsigned> r3(1, 7);

   CHECK(!equal(r1.begin(), r1.end(), r3.begin()));
}

TEST_FIXTURE(IteratorStringstreamFixture, CopyLongRangeToOutputStream)
{
   IntegerRange<long> r2(10, 16);
   copy(r2.begin(), r2.end(), ostream_iterator<long>(oss, " ")); 
   
   string expected = "10 11 12 13 14 15 ";
   CHECK_EQUAL(expected, oss.str());
}

// a unary function to test the InterRange iterator using std::transform
int order_of_magnitudinize (long l) { return l*10; }

TEST_FIXTURE(IteratorStringstreamFixture, TransformLongRangeToOutputStream)
{
   IntegerRange<long> r2(10, 16);
   transform(r2.begin(), r2.end(), ostream_iterator<long>(oss, " "), order_of_magnitudinize); 
   
   string expected = "100 110 120 130 140 150 ";
   CHECK_EQUAL(expected, oss.str());
}

int main() {
   cout << "Running tests for C4 HW7 - IntegerRange::iterator..." << "\n\n";

   int result = UnitTest::RunAllTests();

   cout << "\n";

   return result;
}