// Question 2:
//
// What will the following program output? 
//   The program will output "7".
//
// How can the code in main() be changed to follow the recommended 
// guidelines for object construction?
//   main() was changed to use the copy constructor syntax instead
//   of copy assignment, per the guidelines.

#include <iostream>

struct Foo
{
   Foo(const Foo &)
   {
      std::cout << "bar";
   }

   Foo(int i)
   {
      std::cout << i;
   }
};

int main()
{
   Foo t(7);
}