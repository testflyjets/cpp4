// look at std::list

#ifndef DLIST_H
#define DLIST_H

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

}

template <typename T>
Project2::dlist<T> &
Project2::dlist<T>::operator=(const dlist &rhs)
{
   this->front_ = rhs.front_;
   this->back_ = rhs.back_;
   this->size_ = rhs.size_;

   return *this;
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
   node* newNode = new node(value, nullptr, back_);
    if(back_ == nullptr)
        back_ = newNode;

    if (front_ != nullptr)
       front_->next(newNode);
    front_ = newNode;

    ++size_;
}

template <typename T>
void
Project2::dlist<T>::pop_front()
{
   if (front_ != nullptr)
   {
      front_ = front_->previous();
      delete front_->next();
      --size_;
   }
}

template <typename T>
void
Project2::dlist<T>::push_back(const T &value)
{
    node* newNode = new node(value, nullptr, back_);
    if(front_ == nullptr)
        front_ = newNode;
    if (back_ != nullptr)
       back_->previous(newNode);
    back_ = newNode;

    ++size_;
}

template <typename T>
void
Project2::dlist<T>::pop_back()
{
   if (back_ != nullptr)
   {
      back_ = back_->next();
      delete back_->previous();
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
      return position;
   }
   
   for (iterator iter = this->begin(); iter != this->end(); iter++)
   {
      if (iter == position)
      {
         node *currentNode = position.data();
         node *newNode = new node(val, currentNode->next(), currentNode);
         currentNode->next()->previous(newNode);
         currentNode->next(newNode);

         return --position;
      }
   }

   return position;
}

template <typename T>
typename Project2::dlist<T>::iterator
Project2::dlist<T>::erase(iterator position)
{
   if (this->empty())
   {
      return position;
   }

   if (this->size() == 1)
   {
      this->pop_front();
      return iterator();
   }

   node *currentNode = position.data();
   iterator nextIter = ++position;

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

   return back_ == nullptr ? iterator() : iterator(back_->previous());
}

template <typename T>
const typename Project2::dlist<T>::iterator   
Project2::dlist<T>::end() const
{
   return back_ == nullptr ? iterator() : iterator(back_->previous());
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
   pData_ = pData_->previous();
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
   pData_ = pData_->next();
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
