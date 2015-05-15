
#include "auto_ptr.h"

using namespace ChrisMcCann::hw5;

template <typename X>
auto_ptr<X>::auto_ptr(X *ptX)
{

}

template <typename X>
auto_ptr<X>::auto_ptr(auto_ptr &ap)
{

}

template <typename X>
template <typename Y>
auto_ptr<X>::auto_ptr(auto_ptr<Y> &apy)
{

}

template <typename X>
auto_ptr<X>::~auto_ptr()
{

}

template <typename X>
X *
auto_ptr<X>::get() const
{

}

template <typename X>
X &
auto_ptr<X>::operator*() const
{

}

template <typename X>
X *
auto_ptr<X>::operator->() const
{

}

template <typename X>
auto_ptr<X> &
auto_ptr<X>::operator=(auto_ptr<X> &rhs)
{

}

template <typename X>
template <typename Y> auto_ptr<X> &
auto_ptr<X>::operator=(auto_ptr<Y> &rhs)
{

}

template <typename X>
X *
auto_ptr<X>::release()
{

}

template <typename X>
void
auto_ptr<X>::reset(X *ptX)
{

}