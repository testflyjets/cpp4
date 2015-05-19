/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * May 18, 2015
 * hw6.cpp
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * A test program for an implementation of the two algorithms,
 * palindrome and compress.
 * 
 */
#include <list>
using std::list;

#include "UnitTest++.h"

#include "algorithms.h"

using namespace ChrisMcCann::hw6;

TEST(EmptyListPalindrome)
{
   int data = {};
   list<int> ls(data, data);

   CHECK(palindrome(ls.begin(), ls.end()) == true);
}

TEST(ValidOddPalindrome)
{
   int data[] = { 1, 2, 3, 4, 3, 2, 1 };
   list<int> ls1(data, data + 7);

   CHECK(palindrome(ls1.begin(), ls1.end()) == true);
}

TEST(ValidEvenPalindrome)
{
   int data[] = { 1, 2, 3, 4, 4, 3, 2, 1 };
   list<int> ls1(data, data + 8);

   CHECK(palindrome(ls1.begin(), ls1.end()) == true);
}

TEST(InvalidOddPalindrome)
{
   int data[] = { 1, 2, 3, 4, 5, 6, 7 };
   list<int> ls2(data, data + 7);

   CHECK(palindrome(ls2.begin(), ls2.end()) != true);
}

TEST(InvalidEvenPalindrome)
{
   int data[] = { 0, 2, 3, 4, 4, 3, 2, 1 };
   list<int> ls1(data, data + 8);

   CHECK(palindrome(ls1.begin(), ls1.end()) != true);
}

TEST(EmptyListCompress)
{
   int data = {};
   list<int> ls(data, data), ls1;

   compress(ls.begin(), ls.end(), back_inserter(ls1));

   CHECK_EQUAL(data, data);
}

TEST(CompressNoDuplicates)
{
   int data[] = { 1, 2, 3, 1, 2, 3 };
   list<int> ls(data, data + 6), ls1;

   compress(ls.begin(), ls.end(), back_inserter(ls1));

   CHECK_ARRAY_EQUAL(ls1, ls, 6);
}

TEST(CompressWithDuplicates)
{
   int data[] = { 1, 1, 2, 2, 1, 1 };
   list<int> ls(data, data + 6), ls1;

   compress(ls.begin(), ls.end(), back_inserter(ls1));

   CHECK_ARRAY_EQUAL(data, data, 6);
}

int main() {
   return UnitTest::RunAllTests();
}