/* Christopher C. McCann, U05484743
 * testflyjets@gmail.com
 * C/C++ Programming 4, Section ID 106647, Ray Mitchell III
 * April 15, 2015
 * hw2.cpp
 * Windows 8.1 Enterprise 64-bit
 * Microsoft Visual Studio 2013 Express for Desktop
 *
 * A test program for an exception-safe, exception-neutral Queue type.
 * The queue is implemented as an automatically growable circular array.
 * Two indices are used to track the head and tail of the queue, and these
 * rotate around the queue as required based on the number of elements.
 *
 * The queue is declared with an initial maximum capacity, and if an element
 * is added to the queue when it is full the queue is grown to (2*size + 1)
 * elements. 
 */

#include <algorithm>
using std::copy;

#include <cassert>

#include <stdexcept>
using std::logic_error;

#include "UnitTest++.h"

const size_t INITIAL_SIZE = 4;

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

   T &front();                      // Return ref to front elem in queue (l-value)
   const T &front() const;          // Return ref to front elem in const queue (r-value)

   bool empty() const;              // Return whether queue is empty
   size_t size() const;             // Return # of elems in queue

private:
   int next(int index) const;       // Return the index of the next array position 
                                    // after the given index in the circular array
   bool full() const;               // Return if queue is currently full

   T *v_;                           // Container for elements in queue
   size_t vsize_;                   // Current max size of queue
   int vhead_;                      // Array index of head of queue
   int vtail_;                      // Array index of tail of queue
};

template <typename T>
Queue<T>::Queue()
:  v_(0),
   vsize_(INITIAL_SIZE),
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
         // expand the container
         size_t vsize_new = vsize_ * 2 + 1;
         T *v_new = newCopy(v_, vsize_, vsize_new);

         // if the head of the queue isn't at zero
         // we have to rearrange the elements in the 
         // proper order
         if (vhead_ != 0)
         {
            for (size_t i = 0; i < vsize_; ++i)
            {
               v_new[i] = v_[vhead_];
               vhead_ = next(vhead_);
            }
            vhead_ = 0;
         }

         delete[] v_;
         v_ = v_new;
         vtail_ = vsize_;
         vsize_ = vsize_new;
         
      } 
      else
      {
         vtail_ = next(vtail_);
      }
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
         vhead_ = next(vhead_);
      }
   }
}

template <typename T>
T &
Queue<T>::front()
{
   if (empty())
   {
      throw logic_error("front of empty queue");
   }
   else
   {
      return v_[vhead_];
   }
}

template <typename T>
const T &
Queue<T>::front() const {
   if (empty())
   {
      throw logic_error("front of empty const queue");
   }
   else
   {
      return v_[vhead_];
   }
}

template <typename T>
bool
Queue<T>::full() const
{
   return next(vtail_) == vhead_;
}

template <typename T>
int
Queue<T>::next(int index) const
{
   return (index + 1) % vsize_;
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
      return (vtail_ >= vhead_) ? 
         size_t(vtail_ - vhead_ + 1)  : 
         size_t(vtail_ + vsize_ - vhead_ + 1);
   }
}

struct FullQueueFixture
{
   FullQueueFixture()            // Setup function
   {
      pQueue = new Queue<int>;
      for (int i = 1; i <= INITIAL_SIZE; ++i)
      {
         pQueue->push(i);
      }
   }

   ~FullQueueFixture()           // Teardown function
   {
      delete pQueue;
   }

   Queue<int> *pQueue;
};

TEST(QueueConstructor)
{
   try {
      Queue<int> *pQueue;
      pQueue = new Queue<int>();

      CHECK_EQUAL(0, pQueue->size());
   } 
   catch (...)
   {
      CHECK_ASSERT(false);
   }
}

TEST(QueueDestructor)
{
   try
   {
      Queue<int> *pQueue;
      pQueue = new Queue<int>();
      delete pQueue;
   }
   catch (...)
   {
      CHECK_ASSERT(false);
   }
}

TEST(QueueCopyConstructor)
{
   int expected = 42;

   Queue<int> newQueue;
   newQueue.push(expected);

   Queue<int> copyQueue(newQueue);

   CHECK_EQUAL(expected, copyQueue.front());
}

TEST(QueueCopyAssignment)
{
   int expected = 37;

   Queue<int> newQueue;
   newQueue.push(expected);

   Queue<int> copyQueue = newQueue;

   CHECK_EQUAL(expected, copyQueue.front());
}

TEST(QueuePush)
{
   int expectedSize = 1;
   int expectedFront = 13;

   Queue<int> newQueue;
   newQueue.push(expectedFront);

   CHECK(!newQueue.empty());
   CHECK_EQUAL(expectedFront, newQueue.front());
   CHECK_EQUAL(expectedSize, newQueue.size());

   newQueue.push(42);
   CHECK_EQUAL(expectedFront, newQueue.front());
}

TEST_FIXTURE(FullQueueFixture, QueuePushCircular)
{
   // Test the circular array by pushing and popping
   // elements so that we go all the way around the array

   // Starting with a full queue, check its size
   // and the front element (should be 1)
   CHECK_EQUAL(INITIAL_SIZE, pQueue->size());
   CHECK_EQUAL(1, pQueue->front());

   // pop 2 elements off the queue and check the size
   pQueue->pop();
   pQueue->pop();
   
   CHECK_EQUAL(INITIAL_SIZE - 2, pQueue->size());

   // push 2 elements back onto the queue and
   // check the size and the front element, which
   // should be 3
   pQueue->push(5);
   pQueue->push(6);

   CHECK_EQUAL(INITIAL_SIZE, pQueue->size());
   CHECK_EQUAL(3, pQueue->front());
}

TEST_FIXTURE(FullQueueFixture, QueuePushExpanded)
{
   // Test that the queue expands properly so that 
   // the front element remains unchanged when the 
   // tail index is less than the head index

   // pop an element off the queue, front should be [2]
   pQueue->pop();
   CHECK_EQUAL(2, pQueue->front());

   // push another element on, front should still be [2]
   pQueue->push(11);
   CHECK_EQUAL(2, pQueue->front());

   // push another element on, queue should expand 
   // and front should still be [2]
   pQueue->push(13);
   CHECK_EQUAL(2, pQueue->front());
}

TEST(QueuePopEmpty)
{
   Queue<int> newQueue;

   CHECK_THROW(newQueue.pop(), logic_error);
}

TEST(QueuePop)
{
   Queue<int> newQueue;
   newQueue.push(2);
   newQueue.pop();

   CHECK_EQUAL(0, newQueue.size());

   newQueue.push(3);
   newQueue.push(4);
   newQueue.pop();

   CHECK_EQUAL(1, newQueue.size());
}

TEST(QueueFrontEmpty)
{
   Queue<int> newQueue;

   CHECK_THROW(newQueue.front(), logic_error);
}

TEST(QueueFront)
{
   int expected = 3;
   Queue<int> newQueue;
   newQueue.push(expected);

   CHECK_EQUAL(expected, newQueue.front());

   newQueue.push(5);

   CHECK_EQUAL(expected, newQueue.front());
}

TEST(ConstQueueFrontEmpty)
{  
   const Queue<int> constQueue;
   
   CHECK_THROW(constQueue.front(), logic_error);
}

TEST(ConstQueueFront)
{
   int expectedFront = 42;

   Queue<int> newQueue;
   newQueue.push(expectedFront);

   const Queue<int> constQueue(newQueue);

   CHECK_EQUAL(expectedFront, constQueue.front());
}

TEST(QueueIsEmpty)
{
   Queue<int> newQueue;
   CHECK(newQueue.empty());
}

TEST(QueueSizeEmpty)
{
   // check empty size
   Queue<int> newQueue;

   CHECK_EQUAL(0, newQueue.size());
}

TEST(QueueSizeOneElement)
{
   // check the queue size with one element,
   // when head == tail
   Queue<int> newQueue;

   newQueue.push(1);

   CHECK_EQUAL(1, newQueue.size());
}

TEST_FIXTURE(FullQueueFixture, QueueSizeFull)
{  
   // check the size of a full queue,
   // when head > tail
   CHECK_EQUAL(INITIAL_SIZE, pQueue->size());
}

TEST_FIXTURE(FullQueueFixture, QueueSizeWrappedAround)
{  
   // check the size of a full queue that
   // has wrapped around so that head < tail
   
   // remove the item at the head of the queue
   pQueue->pop();

   // add another item to the tail; this will
   // cause the queue to wrap around so that the
   // the head index == 1 and the tail index == 0
   pQueue->push(42);

   CHECK_EQUAL(INITIAL_SIZE, pQueue->size());
}

TEST_FIXTURE(FullQueueFixture, QueueSizeExpands)
{
   // start with a full queue
   CHECK_EQUAL(INITIAL_SIZE, pQueue->size());

   // Add another element to the queue and verify size 
   // increases beyond the initial max size
   pQueue->push(42);

   CHECK_EQUAL(INITIAL_SIZE + 1, pQueue->size());
}

int main() {
   return UnitTest::RunAllTests();
}