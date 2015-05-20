/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * May 14, 2015
 * hw5.cpp
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * A test program for an implementation of the auto_ptr
 * class.
 * 
 */
#include <iostream>
using std::cout;

#include <string>

#include "auto_ptr.h"
using namespace ChrisMcCann::hw5;

#include "UnitTest++.h"

class TestClass
{
public:
   TestClass(int i = 0) : testInt(i)
   {
   }

   ~TestClass()
   {
   }

   void setInt(int i)
   {
      testInt = i;
   }

   int getInt()
   {
      return testInt;
   }

private:
   int testInt;
};

class DerivedTestClass : public TestClass
{

};

TEST(DefaultConstructor)
{
   auto_ptr<TestClass> ap;
   
   CHECK(ap.get() == nullptr);
}

TEST(Constructor)
{
   auto_ptr<TestClass> ap(new TestClass);

   CHECK(ap.get() != nullptr);
}

TEST(CopyConstructor)
{  
   TestClass *ptr = new TestClass(42);
   auto_ptr<TestClass> ap(ptr);

   auto_ptr<TestClass> apCopy(ap);

   CHECK(ap.get() == nullptr);
   CHECK(apCopy.get() == ptr);
}

TEST(CopyConstructorDerivedClass)
{
   auto_ptr<DerivedTestClass> rhs(new DerivedTestClass);
   auto_ptr<TestClass> apBase(rhs);

   CHECK(apBase->getInt() == 0);
}

TEST(Destructor)
{
   TestClass *ptr = new TestClass;
   auto_ptr<TestClass> *ap = new auto_ptr<TestClass>(ptr);

   try
   {
      delete ap;
   }
   catch (...)
   {
      CHECK(false);
   }
   
}

TEST(GetAutoPtr)
{
   TestClass *ptr = new TestClass(42);
   auto_ptr<TestClass> ap(ptr);

   CHECK(ap.get() == ptr);
}

TEST(DereferenceAutoPtr)
{
   auto_ptr<TestClass> ap(new TestClass(42));

   CHECK((*ap).getInt() == 42);
}


TEST(AutoPtrArrowOperator)
{
   auto_ptr<TestClass> ap(new TestClass(42));

   CHECK(ap->getInt() == 42);
}

TEST(AssignmentOperator)
{
   auto_ptr<TestClass> ap(new TestClass(1));
   auto_ptr<TestClass> rhs(new TestClass(2));

   CHECK(ap->getInt() == 1);
   ap = rhs;
   CHECK(ap->getInt() == 2);
}

TEST(DerivedClassAssignmentOperator)
{
   auto_ptr<TestClass> ap(new TestClass(42));
   auto_ptr<DerivedTestClass> rhs(new DerivedTestClass);

   CHECK(ap->getInt() == 42);
   ap = rhs;
   CHECK(ap->getInt() == 0);
}

TEST(ReleaseAutoPtr)
{
   auto_ptr<TestClass> ap(new TestClass(42));
   TestClass *newPtr = ap.release();

   CHECK(ap.get() == nullptr);
   CHECK(newPtr->getInt() == 42);
}

TEST(DefaultResetAutoPtr)
{
   auto_ptr<TestClass> ap(new TestClass(1));
   
   ap.reset();

   CHECK(ap.get() == nullptr);
}

TEST(ResetAutoPtr)
{
   TestClass *ptr1 = new TestClass(1);
   auto_ptr<TestClass> ap(ptr1);

   TestClass *ptr2 = new TestClass(2);
   
   ap.reset(ptr2);

   CHECK(ap->getInt() == 2);
}

TEST(ResetPreventSelfAssignment)
{
   TestClass *ptr1 = new TestClass(1);
   auto_ptr<TestClass> ap(ptr1);
   
   ap.reset(ptr1);

   CHECK(ap.get() == ptr1);
}

int main() {
   cout << "Running tests for C4 HW5..." << "\n\n";
   return UnitTest::RunAllTests();
}