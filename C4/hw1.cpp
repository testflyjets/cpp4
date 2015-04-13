/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 13, 2015 
 * hw1.cpp
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 * 
 * A test program for multiple STL types
 */
#include <algorithm>
using std::generate_n;
using std::partition;
using std::sort;
using std::transform;

#include <deque>
using std::deque;

#include <iterator>
using std::back_inserter;
using std::ostream_iterator;

#include <numeric>
using std::accumulate;

#include <sstream>
using std::ostringstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "UnitTest++.h"

int current = 0;
// a simple function to create sequential integer values
int SequenceNumber () { return ++current; }

TEST(GenerateAccumulateDeque)
{
   // create a deq and use the generate_n algorithm and 
   // a back_inserter to populate it with the numbers 1 thru 10
   deque <int> deq;
   generate_n(back_inserter(deq), 10, SequenceNumber);

   // use the accumulate algorithm to sum the values in the deque
   int sum = 0;
   sum = accumulate(deq.begin(), deq.end(), sum);

   // test our expectations
   int expected = 55;
   CHECK_EQUAL(expected, sum);
}

TEST(TransformStringToUppercase)
{
   // convert a string of sorted lowercase letters to uppercase 
   // using the transform algorithm
   string lowerAlphabet = "abcdefghijklmnopqrstuvwxyz";
   transform(lowerAlphabet.begin(), lowerAlphabet.end(), lowerAlphabet.begin(), ::toupper);

   // test our expectations
   string upperAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   CHECK_EQUAL(upperAlphabet, lowerAlphabet);
}

// a unary function to test if a number is even
bool IsEven (int i) { return (i%2) == 0; }

TEST(PartitionSortVector)
{
   int nums[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
   // create vector using the iterator range constructor
   vector<int> vectorNums(nums, nums + sizeof(nums) / sizeof(int));

   // use partition to place the even numbers in the first half of the vector
   // and the odd numbers in the second half
   vector<int>::iterator bound;
   bound = partition(vectorNums.begin(), vectorNums.end(), IsEven);

   // sort the even and odd partitions of the vector
   sort(vectorNums.begin(), bound);
   sort(bound, vectorNums.end());

   // use an ostream_iterator to copy the values from the vector
   // into an ostring_stream
   ostringstream outputStream;
   copy(vectorNums.begin(), vectorNums.end(), ostream_iterator<int>(outputStream));
   
   // test our expectations
   string expected = "24681013579";
   CHECK_EQUAL(expected, outputStream.str());
}

int main() {
   return UnitTest::RunAllTests();
}