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
#include <iostream>
using std::cout;

#include <iterator>
using std::ostream_iterator;

#include <list>
using std::list;

#include <sstream>
using std::ostringstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "UnitTest++.h"

#include "algorithms.h"

using namespace ChrisMcCann::hw6;

TEST(PalindromeEmptyList)
{
   int data = {};
   list<int> ls(data, data);

   CHECK(palindrome(ls.begin(), ls.end()) == true);
}

TEST(PalindromeValidOdd)
{
   int data[] = { 1, 2, 3, 4, 3, 2, 1 };
   list<int> ls1(data, data + 7);

   CHECK(palindrome(ls1.begin(), ls1.end()) == true);
}

TEST(PalindromeValidEven)
{
   int data[] = { 1, 2, 3, 4, 4, 3, 2, 1 };
   list<int> ls1(data, data + 8);

   CHECK(palindrome(ls1.begin(), ls1.end()) == true);
}

TEST(PalindromeInvalidOdd)
{
   int data[] = { 1, 2, 3, 4, 5, 6, 7 };
   list<int> ls2(data, data + 7);

   CHECK(palindrome(ls2.begin(), ls2.end()) != true);
}

TEST(PalindromeInvalidEven)
{
   int data[] = { 0, 2, 3, 4, 4, 3, 2, 1 };
   list<int> ls1(data, data + 8);

   CHECK(palindrome(ls1.begin(), ls1.end()) != true);
}

TEST(PalindromeEmptyStringVector)
{ 
   vector<string> v;

   CHECK(palindrome(v.begin(), v.end()) == true);
}

TEST(PalindromeValidOddString)
{
   vector<string> v;
   v.push_back("a");
   v.push_back("b");
   v.push_back("c");
   v.push_back("b");
   v.push_back("a");

   CHECK(palindrome(v.begin(), v.end()) == true);
}

TEST(PalindromeInvalidOddString)
{
   vector<string> v;
   v.push_back("a");
   v.push_back("b");
   v.push_back("c");
   v.push_back("d");
   v.push_back("e");

   CHECK(palindrome(v.begin(), v.end()) == false);
}

TEST(CompressEmptyIntList)
{
   int data = {};
   list<int> ls(data, data), lsOut;

   compress(ls.begin(), ls.end(), back_inserter(lsOut));

   CHECK(ls == lsOut);
}

TEST(CompressIntNoDuplicates)
{
   int data[] = { 1, 2, 3, 1, 2, 3 };
   list<int> ls(data, data + 6), lsOut;

   compress(ls.begin(), ls.end(), back_inserter(lsOut));

   CHECK(lsOut == ls);
}

TEST(CompressIntWithDuplicates)
{
   int data[] = { 1, 1, 2, 2, 1, 1 };

   // expected test result
   int expData[] = {1, 2, 1};

   list<int> ls(data, data + 6), lsOut, lsExpected(expData, expData + 3);

   compress(ls.begin(), ls.end(), back_inserter(lsOut));

   CHECK(lsExpected == lsOut);
}


TEST(CompressEmptyStringList)
{
   vector<string> v, vOut, vExpected;

   compress(v.begin(), v.end(), back_inserter(vOut));

   CHECK(vExpected == vOut);
}

TEST(CompressStringListWithDuplicates)
{
   vector<string> v, vOut, vExpected;

   v.push_back("foo");
   v.push_back("bar");
   v.push_back("bar");
   v.push_back("baz");

   // expected test result
   vExpected.push_back("foo");
   vExpected.push_back("bar");
   vExpected.push_back("baz");

   compress(v.begin(), v.end(), back_inserter(vOut));

   CHECK(vExpected == vOut);
}

TEST(CompressStringListWithoutDuplicates)
{
   vector<string> v, vOut;

   v.push_back("foo");
   v.push_back("bar");
   v.push_back("baz");
   v.push_back("boom");

   compress(v.begin(), v.end(), back_inserter(vOut));

   CHECK(v == vOut);
}

int main() {
   return UnitTest::RunAllTests();
}