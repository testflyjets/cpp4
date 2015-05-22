// look at std::list

#ifndef DLIST_H
#define DLIST_H

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
     // You decide what goes here

  };

  template <typename T>
  class dlist<T>::node
  {
  public:
     node() : data_(0), next_(0), previous_(0)
     {}

     node(T data) : data_(data)
     {}

     node *next()
     {
        return next_;
     }

     node *previous()
     {
        return previous_;
     }

  private:
     node *next_;
     node *previous_;

     T data_;
      
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

  private: 
    // You decide what goes here 
  };
}

#endif
