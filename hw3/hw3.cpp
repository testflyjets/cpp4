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

#include <sstream>
using std::istringstream;
using std::ostringstream;

#include <string>
using std::string;

#include "DigitStrippingSPA.h"
#include "UppercasingSPA.h"

using namespace hw3;

#include "UnitTest++.h"

TEST(DigitStrippingSPAConstructor)
{
   DigitStrippingSPA dsSPA(cin, cout);
}

TEST(UppercasingSPAConstructor)
{
   UppercasingSPA ucSPA(cin, cout);
}

TEST(UppercasingSPAEmpty)
{
   istringstream testIn("");
   ostringstream testOut;
   string expectedOut("");

   UppercasingSPA ucSPA(testIn, testOut);
   ucSPA.process();

   CHECK_EQUAL(expectedOut, testOut.str());
}

TEST(UppercasingSPAShortText)
{
   istringstream testIn("hello world");
   ostringstream testOut;
   string expectedOut("HELLOWORLD");

   UppercasingSPA ucSPA(testIn, testOut);
   ucSPA.process();

   CHECK_EQUAL(expectedOut, testOut.str());
}

TEST(UppercasingSPALongText)
{
   istringstream testIn("Wait1! Wait2!   Don't tell me!");
   ostringstream testOut;
   string expectedOut("WAIT1!WAIT2!DON'TTELLME!");

   UppercasingSPA ucSPA(testIn, testOut);
   ucSPA.process();

   CHECK_EQUAL(expectedOut, testOut.str());
}

int main() {
   return UnitTest::RunAllTests();
}