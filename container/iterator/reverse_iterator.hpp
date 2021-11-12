#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H

#include "iterator_traits.hpp"

/*
** @brief
** reverse_iterator is an iterator adaptator that reverse the direction
** of a given iterator wich must be at least a biredirecional iterator
** From : https://en.cppreference.com/w/cpp/iterator/reverse_iterator
*/

namespace ft {

template< class Iter>
class reverse_iterator {
	
	public:
	typedef Iter													iterator_type;
	typedef typename 	iterator_traits<Iter>::iterator_category 	iterator_category;
	typedef typename 	iterator_traits<Iter>::value_type			value_type;
	typedef typename 	iterator_traits<Iter>::difference_type		difference_type;
	typedef typename	iterator_traits<Iter>::pointer				pointer;
	typedef typename	iterator_traits<Iter>::reference			reference;


	// constructor
	reverse_iterator(): _base() {}
	explicit reverse_iterator(iterator_type x ): _base(x) {}
	template< class U >
	reverse_iterator(const reverse_iterator<U>& other ): _base(other.base()) {}

	template< class U >
	reverse_iterator& operator=( const reverse_iterator<U>& other ) {
		if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&other))
			return (*this);
		_base = other.base();
		return (*this);
	}

	iterator_type		base() const { return _base; }

	reference			operator*() const { return *(_base - 1); }
	pointer				operator->() { return &operator*(); }

	reverse_iterator	&operator++() { --_base; return *this; }
	reverse_iterator	&operator--() {++_base; return *this; }
	reverse_iterator	operator++(int) { return reverse_iterator(_base--); }
	reverse_iterator	operator--(int) { return reverse_iterator(_base++); }

	reverse_iterator 	operator+( difference_type n ) const { return reverse_iterator(_base - n); }
	reverse_iterator 	operator-( difference_type n ) const { return reverse_iterator(_base + n); }
	reverse_iterator& 	operator+=( difference_type n ) { _base -= n; return *this; }
	reverse_iterator& 	operator-=( difference_type n ) { _base += n; return *this; }
	
	reference			operator[]( difference_type n ) const {return _base.base()[-n - 1]; }

	operator reverse_iterator<const Iter> () const
        	{ return (reverse_iterator<const Iter>(_base)); }
		
	protected:

	Iter _base;
};


template< class Iterator1, class Iterator2 >
bool operator==( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator!=( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() != rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() > rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<=( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() >= rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() < rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>=( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() <= rhs.base());
}

template< class Iter >
reverse_iterator<Iter>
    operator+( typename reverse_iterator<Iter>::difference_type n,
               const reverse_iterator<Iter>& it )
{
	return reverse_iterator<Iter>(it.base() - n);
}

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type
    operator-( const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs )
{
	return (rhs.base() - lhs.base());
}
// for const iterator

template < class Iter1, class Iter2 >
typename reverse_iterator<Iter1>::difference_type
operator-(const reverse_iterator<Iter1> lhs,
		  const reverse_iterator<Iter2> rhs)
{
	return (rhs.base() - lhs.base());
}

};

#endif