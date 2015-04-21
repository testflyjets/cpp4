/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 20, 2015
 * hw3.cpp
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * A test harness for a virtual stream processing algorithm class
 * and some concrete implementations of it.
 */

#include <iostream>
using std::cin;
using std::cout;

#include "DigitStrippingSPA.h"

using namespace hw3;

#include "UnitTest++.h"

TEST(DigitStrippingSPAConstructor)
{
   DigitStrippingSPA dsSPA(cin, cout);
}

int main() {
   return UnitTest::RunAllTests();
}