/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 15, 2015
 * hw2.cpp
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * A test program for an exception-safe, exception-neutral Queue type
 */
#include <algorithm>
using std::copy;

#include <cassert>

#include "UnitTest++.h"

template <typename T>
class Queue
{
public:
   Queue();                         // Construct empty queue
   ~Queue();                        // Destructor
   Queue(const Queue &);            // Copy constructor
   Queue &operator=(const Queue &); // Copy assignment operator
   void push(const T &);            // Add elem to back of queue
   void pop();                      // Remove front elem from queue
   T &front();                      // Return ref to front elem in queue
   const T &front() const;          // Return ref to front elem in queue
   bool empty() const;              // Return whether queue is empty
   size_t size() const;             // Return # of elems in queue

private:
   bool full() const;               // Return if queue is currently full
   T *v_;                           // Elements in queue
   size_t vsize_;                   // Size of queue
   int vhead_;                      // Array index of head of queue
   int vtail_;                      // Array index of tail of queue

   const size_t INITIAL_SIZE = 10;
};

template <typename T>
Queue<T>::Queue()
:  v_(0),
   vsize_(10),
   vhead_(-1),
   vtail_(-1)
{
   v_ = new T[vsize_];
}

template <typename T>
Queue<T>::~Queue()
{
   delete[] v_;
}

template <typename T>
T*
newCopy(const T *src, size_t src_size, size_t dest_size)
{
   assert(dest_size >= src_size);
   T *dest = new T[dest_size];
   try
   {
      copy(src, src + src_size, dest);
   }
   catch (...)
   {
      delete[] dest;
      throw;
   }
   return dest;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &other)
:  v_(newCopy(other.v_,
              other.vsize_,
              other.vsize_)),
   vsize_(other.vsize_),
   vhead_(other.vhead_),
   vtail_(other.vtail_)
{

}

template <typename T>
Queue<T> &
Queue<T>::operator=(const Queue<T> &other)
{
   if (this != &other)
   {
      T *v_new = newCopy(other.v_,
         other.vsize_,
         other.vsize_);

      delete[] v_;
      v_ = v_new; 
      vsize_ = other.vsize_;
      vhead_ = other.vhead_;
      vtail_ = other.vtail_;
   }
   return *this;
}

template <typename T>
void
Queue<T>::push(const T& t)
{
   if (empty())
   {
      vhead_ = vtail_ = 0;
   }
   else
   {
      if (full())
      {
         size_t vsize_new = vsize_ * 2 + 1;
         T *v_new = newCopy(v_, vsize_, vsize_new);
         delete[] v_;
         v_ = v_new;
         vsize_ = vsize_new;
      }
      vtail_ = (vtail_ + 1) % vsize_;
   }

   v_[vtail_] = t; 
}

template <typename T>
void
Queue<T>::pop()
{
   if (empty())
   {
      throw logic_error("pop from empty queue");
   }
   else
   {
      if (vhead_ == vtail_)
      {
         vhead_ = vtail_ = -1;
      }
      else
      {
         vhead_ = (vhead_ + 1) % vsize_;
      }
   }
}

template <typename T>
T &
Queue<T>::front()
{
   return v_[vhead_];
}

template <typename T>
bool
Queue<T>::full() const
{
   return (vtail_ + 1) % vsize_ == vhead_;
}

template <typename T>
bool 
Queue<T>::empty() const
{
   return vhead_ == -1 && vtail_ == -1;
}

template <typename T>
size_t
Queue<T>::size() const
{
   if (empty())
   {
      return 0;
   }
   else
   {
      return (vhead_ >= vtail_) ? 
         size_t(vhead_ - vtail_ + 1)  : 
         size_t(vhead_ + vsize_ - vtail_ + 1);
   }
}

TEST(QueueConstructor)
{
   Queue<int> intQueue;

}

TEST(QueueDestructor)
{

}

TEST(QueueCopyConstructor)
{

}

TEST(QueueCopyAssignment)
{

}

TEST(QueuePush)
{
   Queue<int> newQueue;

   newQueue.push(1);

   CHECK(!newQueue.empty());
   CHECK_EQUAL(1, newQueue.size());
}

TEST(QueueIsEmpty)
{
   Queue<int> newQueue;
   CHECK(newQueue.empty());
}

TEST(QueueSize)
{
   Queue<int> newQueue;
   CHECK_EQUAL(0, newQueue.size());
}

int main() {
   return UnitTest::RunAllTests();
}