/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * Nune 1, 2015
 * hw8.cpp
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * A collection of object construction and const-correctness
 * code snippets.  These snippets have been corrected from those
 * provided in the homework assignment and answers to the questions
 * provided in code comments before each snippet.
 *
 */

// 1. This code won't compile because the original constructor:
//    Foo t()
// was interpreted by the compiler as a function declaration 
// instead of a default constructor.  Removing the () fixes it.
struct Foo { int i; };

int main()
{
   Foo t;
   t.i = 7;
}