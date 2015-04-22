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

// a function template to make testing easier
template <typename T>
void testSPA(
   string testString,
   string expectedString)
{
   istringstream testIn(testString);
   ostringstream testOut;
   string expectedOut(expectedString);

   StreamProcessorAlgorithm *spa = new T(testIn, testOut);
   spa->process();

   CHECK_EQUAL(expectedOut, testOut.str());

   delete spa;
}

TEST(UppercasingSPAConstructor)
{
   UppercasingSPA ucSPA(cin, cout);
}

TEST(UppercasingSPAEmptyString)
{
   testSPA<UppercasingSPA>("", "");
}

TEST(UppercasingSPAShortString)
{
   testSPA<UppercasingSPA>(
      "hello world", 
      "HELLOWORLD");
}

TEST(UppercasingSPAAllUppers)
{
   testSPA<UppercasingSPA>(
      "HELLO WORLD",
      "HELLOWORLD");
}

TEST(UppercasingSPALongString)
{
   testSPA<UppercasingSPA>(
      "Wait1! Wait2!   Don't tell me!", 
      "WAIT1!WAIT2!DON'TTELLME!");
}

TEST(UppercasingSPAAllNonAlpha)
{
   testSPA<UppercasingSPA>(
      "123#@$ 0987) (*(&", 
      "123#@$0987)(*(&");
}

TEST(DigitStrippingSPAConstructor)
{
   DigitStrippingSPA dsSPA(cin, cout);
}

TEST(DigitStrippingSPAEmptyString)
{
   testSPA<DigitStrippingSPA>("", "");
}

TEST(DigitStrippingSPANoDigits)
{
   testSPA<DigitStrippingSPA>("hello world", "");
}

TEST(DigitStrippingSPAShortString)
{
   testSPA<DigitStrippingSPA>("h3llo world", "hllo");
}

TEST(DigitStrippingSPAMultiDigit)
{
   testSPA<DigitStrippingSPA>("h42ll0", "hll");
}

TEST(DigitStrippingSPAAllDigits)
{
   testSPA<DigitStrippingSPA>("98765", "");
}

int main() {
   return UnitTest::RunAllTests();
}