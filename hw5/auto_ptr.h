/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * May 14, 2015
 * auto_ptr.h
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * The header file that defines an implementation of 
 * the auto_ptr class.
 * 
 */

#ifndef CHRISMCCANN_HW5_AUTOPTR_H
#define CHRISMCCANN_HW5_AUTOPTR_H

namespace ChrisMcCann { namespace hw5 {

   template <typename X>
   class auto_ptr
   {
   public:
      // Constructors
      explicit auto_ptr(X * = 0) throw();
      auto_ptr(auto_ptr &) throw();
      template <typename Y> auto_ptr(auto_ptr<Y> &) throw();

      // Destructor
      ~auto_ptr() throw();

      // Access
      X *get() const throw();
      X &operator*() const throw();
      X *operator->() const throw();

      // Assignment
      auto_ptr &operator=(auto_ptr &) throw();
      template <typename Y> auto_ptr &operator=(auto_ptr<Y> &) throw();

      // Release & Reset
      X *release() throw();
      void reset(X * = 0) throw();

   private:
      X *ap;
   };

template <typename X>
auto_ptr<X>::auto_ptr(X *ptr) throw()
: ap(ptr)
{
}

template <typename X>
auto_ptr<X>::auto_ptr(auto_ptr &rhs)
: ap(rhs.release())
{
}

template <typename X>
template <typename Y>
auto_ptr<X>::auto_ptr(auto_ptr<Y> &rhs)
: ap(rhs.release())
{
}

template <typename X>
auto_ptr<X>::~auto_ptr()
{
   delete ap;
}

template <typename X>
X *
auto_ptr<X>::get() const
{
   return ap;
}

template <typename X>
X &
auto_ptr<X>::operator*() const
{
   return *ap;
}

template <typename X>
X *
auto_ptr<X>::operator->() const
{
   return ap;
}

template <typename X>
auto_ptr<X> &
auto_ptr<X>::operator=(auto_ptr<X> &rhs)
{
   reset(rhs.release());
   return *this;
}

template <typename X>
template <typename Y> 
auto_ptr<X> &
auto_ptr<X>::operator=(auto_ptr<Y> &rhs)
{
   reset(rhs.release());
   return *this;
}

template <typename X>
X *
auto_ptr<X>::release()
{
   X* tmp(ap);
   ap = 0;
   return tmp;
}

template <typename X>
void
auto_ptr<X>::reset(X *ptr)
{
   if (ap != ptr) {
      delete ap;
      ap = ptr;
   }
}

}}

#endif