// look at std::list

#ifndef DLIST_H
#define DLIST_H

#include <algorithm>

#include <cassert>

namespace Project2 
{ 
  template <typename T> 
  class dlist
  {
  public:
     // Types 
     class iterator;
     class node;

     typedef size_t size_type;
     typedef T value_type;
     typedef const T const_reference;

     // Default constructor 
     dlist();

     // Copy constructor 
     dlist(const dlist &);

     // Iterator range constructor 
     template <typename InputIterator> dlist(InputIterator first, InputIterator last);

     // Destructor 
     ~dlist();

     // Copy assginment operator 
     dlist &operator=(const dlist &);

     // convenience Swap function
     void Swap(dlist &);

     // empty() & size() 
     bool empty() const;
     size_type size() const;

     // front() & back() 
     T &front();
     const T &front() const;
     T &back();
     const T &back() const;

     // Modifiers 
     void push_front(const T &);
     void pop_front();
     void push_back(const T &);
     void pop_back();
     iterator insert(iterator, const T &);
     iterator erase(iterator);

     // Comparison 
     bool operator==(const dlist &) const;
     bool operator!=(const dlist &) const;
     bool operator<(const dlist &) const;
     bool operator<=(const dlist &) const;
     bool operator>(const dlist &) const;
     bool operator>=(const dlist &) const;

     // Iterators 
     iterator begin();
     const iterator begin() const;
     iterator end();
     const iterator end() const;

  private:
     node *front_;
     node *back_;
     size_type size_;

  };

  template <typename T>
  class dlist<T>::node
  {
  public:
     node() : 
        value_(0), 
        next_(0), 
        previous_(0)
     {}

     node(const T & value, node *previous, node *next) : 
        value_(value), 
        previous_(previous),
        next_(next) 
     {}

     node *next()
     {
        return next_;
     }

     void next(node *next)
     {
        next_ = next;
     }

     node *previous()
     {
        return previous_;
     }

     void previous(node *previous)
     {
        previous_ = previous;
     }

     T & value()
     {
        return value_;
     }

  private:
     node *next_;
     node *previous_;

     T value_;
  };

  template <typename T> 
  class dlist<T>::iterator : public std::iterator<bidirectional_iterator_tag, T> 
  { 
    friend class dlist<T>;

  public: 
    typedef const T const_reference;

    iterator(); 
    explicit iterator(typename dlist<T>::node *);

    bool operator==(const iterator &) const; 
    bool operator!=(const iterator &) const;

    T &operator*(); 
    const T &operator*() const;

    T *operator->(); 
    const T *operator->() const;

    iterator &operator++(); 
    const iterator operator++(int); 
    iterator &operator--(); 
    const iterator operator--(int);

    typename dlist<T>::node *data() const;

  private: 
     typename dlist<T>::node *pData_;
  };
}

template <typename T>
Project2::dlist<T>::dlist() 
: front_(nullptr), back_(nullptr), size_(0)
{

}

template <typename T>
Project2::dlist<T>::dlist(const dlist &other) 
: front_(nullptr), back_(nullptr), size_(0)
{
   // iterate over other and copy its nodes
   typename Project2::dlist<T>::iterator iter;
   if (!other.empty())
   {
      for (iter = other.begin(); iter != other.end(); iter++)
      {
         this->push_back(*iter);
      }
   }
}

template <typename T>
template <typename InputIterator> Project2::dlist<T>::dlist(InputIterator first, InputIterator last)
: front_(nullptr), back_(nullptr), size_(0)
{
   InputIterator iter;
   for (iter = first; iter != last; iter++)
   {
      this->push_back(*iter);
   }
}

template <typename T>
Project2::dlist<T>::~dlist()
{
   node *pDel = front_;
   while (pDel != nullptr)
   {
      front_ = front_->next();
      delete pDel;
      pDel = front_;
   }
}

template <typename T>
Project2::dlist<T> &
Project2::dlist<T>::operator=(const dlist &other)
{
   dlist temp(other);
   Swap(temp);
   return *this;
}

template <typename T>
void
Project2::dlist<T>::Swap(dlist &other)
{
   std::swap(front_, other.front_);
   std::swap(back_, other.back_);
   std::swap(size_, other.size_);

}

template <typename T>
bool
Project2::dlist<T>::empty() const
{
   return size_ == 0;
}

template <typename T>
typename Project2::dlist<T>::size_type
Project2::dlist<T>::size() const
{
   return size_;
}

template <typename T>
T &
Project2::dlist<T>::front()
{
   return front_->value();
}

template <typename T>
const T &
Project2::dlist<T>::front() const
{
   return front_->value();
}

template <typename T>
T &
Project2::dlist<T>::back()
{
   return back_->value();
}

template <typename T>
const T &
Project2::dlist<T>::back() const
{
   return back_->value();
}

template <typename T>
void
Project2::dlist<T>::push_front(const T &value)
{
   node* newNode = new node(value, nullptr, front_);

   // make the current front node point to the
   // new node as its previous
   if (front_ != nullptr)
   {
      front_->previous(newNode);
   }

   // set the back node if it's null
   if (back_ == nullptr)
   {
      back_ = newNode;
   }

   // set the new node as front
   front_ = newNode;

   ++size_;
}

template <typename T>
void
Project2::dlist<T>::pop_front()
{
   if (front_ != nullptr)
   {
      front_ = front_->next();
      delete front_->previous();
      --size_;
   }
}

template <typename T>
void
Project2::dlist<T>::push_back(const T &value)
{
    node* newNode = new node(value, back_, nullptr);

    // set the front node if it's null
    if (front_ == nullptr)
    {
        front_ = newNode;
    }

    // make the new node the old back node's
    // next node
    if (back_ != nullptr)
    {
       back_->next(newNode);
    }

    back_ = newNode;

    ++size_;
}

template <typename T>
void
Project2::dlist<T>::pop_back()
{
   if (back_ != nullptr)
   {
      back_ = back_->previous();
      delete back_->next();
      back_->next(nullptr);

      --size_;
   }
}

template <typename T>
typename Project2::dlist<T>::iterator
Project2::dlist<T>::insert(iterator position, const T &val)
{
   if (this->empty())
   {
      this->push_front(val);
      return iterator(front_);
   }
   
   // get the node at the iterator position, handle the case
   // where position == end()
   node *currentNode;
   if (position == this->end())
   {
      currentNode = back_;
      position = iterator(back_);
   }
   else
   {
      currentNode = position.data();
   }

   // create a new node that's ahead of the current node
   node *newNode = new node(val, currentNode->previous(), currentNode);

   // handle the case where there were 2 or more nodes in
   // the list; point the current node's previous node's next() at
   // the newly inserted node
   if (currentNode->previous() != nullptr)
   {
      currentNode->previous()->next(newNode);
   }
   else
   {
      // the insertion point is at the front, so update front
      this->front_ = newNode;
   }

   // point the current node back to the newly inserted node
   currentNode->previous(newNode);


   // return the iterator one before the given position
   return --position;
}

template <typename T>
typename Project2::dlist<T>::iterator
Project2::dlist<T>::erase(iterator position)
{
   // handle an empty list
   if (this->empty())
   {
      return position;
   }

   // handle a list with one element
   if (this->size() == 1)
   {
      this->pop_front();
      return iterator();
   }

   // get the node at the current iterator position
   node *currentNode = position.data();

   // get an iterator pointing one past the current position
   iterator nextIter = ++position;

   // fix up the node pointers on either side as required
   if (currentNode->previous() != nullptr)
   {
      currentNode->previous()->next(currentNode->next());
   }
   if (currentNode->next() != nullptr)
   {
      currentNode->next()->previous(currentNode->previous());
   }

   delete currentNode;
   --size_;

   return nextIter;
}

template <typename T>
bool
Project2::dlist<T>::operator==(const dlist &rhs) const
{
   if (this->size() != rhs.size())
      return false;

   iterator iterLhs = this->begin();
   iterator iterRhs = rhs.begin();

   for (; iterLhs != this->end(); ++iterLhs)
   {
      if (*iterLhs != *iterRhs)
         return false;
      ++iterRhs;
   }
   return true;
}

template <typename T>
bool 
Project2::dlist<T>::operator!=(const dlist &rhs) const
{
   return !operator==(rhs);
}

template <typename T>
bool 
Project2::dlist<T>::operator<(const dlist &rhs) const
{
   if (this->size() < rhs.size())
      return true;
   if (this->size() > rhs.size())
      return false;

   iterator iterLhs = this->begin();
   iterator iterRhs = rhs.begin();

   for (; iterLhs != this->end(); ++iterLhs)
   {
      if (*iterLhs < *iterRhs)
         return true;
      ++iterRhs;
   }
   return false;
}

template <typename T>
bool 
Project2::dlist<T>::operator<=(const dlist &rhs) const
{
   return operator==(rhs) || operator<(rhs);
}

template <typename T>
bool 
Project2::dlist<T>::operator>(const dlist &rhs) const
{
   return !operator<=(rhs);
}

template <typename T>
bool 
Project2::dlist<T>::operator>=(const dlist &rhs) const
{
   return !operator<(rhs);
}

template <typename T>
typename Project2::dlist<T>::iterator
Project2::dlist<T>::begin()
{
   return iterator(front_);
}

template <typename T>
const typename Project2::dlist<T>::iterator 
Project2::dlist<T>::begin() const
{
   return iterator(front_);
}

template <typename T>
typename Project2::dlist<T>::iterator  
Project2::dlist<T>::end()
{
   // we need to return the element after the 
   // last element, so get the previous node

   return back_ == nullptr ? iterator() : iterator(back_->next());
}

template <typename T>
const typename Project2::dlist<T>::iterator   
Project2::dlist<T>::end() const
{
   return back_ == nullptr ? iterator() : iterator(back_->next());
}

//
// iterator methods
//

template <typename T>
Project2::dlist<T>::iterator::iterator()
: pData_(0)
{}

template <typename T>
Project2::dlist<T>::iterator::iterator(typename dlist<T>::node *pData)
: pData_(pData)
{}

template <typename T>
bool
Project2::dlist<T>::iterator::operator==(const iterator &other) const
{
   return pData_ == other.pData_;
}

template <typename T>
bool
Project2::dlist<T>::iterator::operator!=(const iterator &other) const
{
   return !operator==(other);
}

template <typename T>
T &
Project2::dlist<T>::iterator::operator*()
{
   return pData_->value();
}

template <typename T>
const T &
Project2::dlist<T>::iterator::operator*() const
{
   return pData_->value();
}

template <typename T>
T *
Project2::dlist<T>::iterator::operator->()
{
   return &pData_->value();
}

template <typename T>
const T *
Project2::dlist<T>::iterator::operator->() const
{
   return &pData_->value();
}

template <typename T>
typename Project2::dlist<T>::iterator &
Project2::dlist<T>::iterator::operator++()
{
   pData_ = pData_->next();
   return *this;
}

template <typename T>
const typename Project2::dlist<T>::iterator
Project2::dlist<T>::iterator::operator++(int)
{
   iterator temp(*this);
   operator++();
   return temp;
}

template <typename T>
typename Project2::dlist<T>::iterator &
Project2::dlist<T>::iterator::operator--()
{
   pData_ = pData_->previous();
   return *this;
}

template <typename T>
const typename Project2::dlist<T>::iterator
Project2::dlist<T>::iterator::operator--(int)
{
   iterator temp(*this);
   operator--();
   return temp;
}

template <typename T>
typename Project2::dlist<T>::node *
Project2::dlist<T>::iterator::data() const
{
   return pData_;
}

#endif
