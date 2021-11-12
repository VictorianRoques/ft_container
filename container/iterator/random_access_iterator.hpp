#ifndef RANDOM_ACCESS_ITERATOR_H
# define RANDOM_ACCESS_ITERATOR_H

#include "iterator.hpp"

namespace ft {

/*
** @brief
** Random-access iterators are iterators that can be used to access elements at an arbitrary offset
** position relative to the element they point to, offering the same functionality as pointers.
** From: https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
*/

template <typename T>
class random_access_iterator: iterator<random_access_iterator_tag, T> {

public:

	typedef typename	iterator<random_access_iterator_tag, T>::value_type			value_type;
	typedef				ptrdiff_t      												difference_type;
    typedef 			T*               											pointer;
    typedef 			T&             												reference;
	typedef				const T&													const_reference;
	typedef typename 	iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

	random_access_iterator(): _elem(NULL) {}
	random_access_iterator(pointer elem): _elem(elem) {}
	random_access_iterator(const random_access_iterator& src): _elem(src._elem) {}
	random_access_iterator&		operator=(const random_access_iterator &x)
	{
		if (this == &x)
			return *this;
		_elem = x._elem;
		return *this;
	}
	virtual ~random_access_iterator() {}
	pointer base() const { return _elem; }
	// Can be compared for equivalence
	bool		operator==(const random_access_iterator &x) const { return _elem == x._elem; }
	bool		operator!=(const random_access_iterator &x) const { return _elem != x._elem; }

	// Can be dereferenced as an rvalue
	reference	operator*() const { return *_elem; }
	pointer		operator->() { return _elem; }

	// Can be incremented
	random_access_iterator&		operator++() { _elem++; return *this; }
	random_access_iterator		operator++(int) { random_access_iterator tmp(*this); _elem++; return tmp; }
	random_access_iterator&		operator--() { _elem--; return *this; }
	random_access_iterator		operator--(int ) { random_access_iterator tmp(*this); _elem--; return tmp; }

	// Supports the arithmetic operator between and iterator and integer value
	random_access_iterator	operator+(difference_type n) const { return random_access_iterator(_elem + n); }
	random_access_iterator	operator-(difference_type n) const { return random_access_iterator(_elem - n); }

	random_access_iterator&		operator-=(difference_type n) { _elem -= n; return *this; }
	random_access_iterator&		operator+=(difference_type n) { _elem += n; return *this; }

	reference					operator[](difference_type n) { return *(_elem + n); }

	operator random_access_iterator<const T> () const
        	{ return (random_access_iterator<const T>(_elem)); }

private:

	pointer _elem;

};

	template <typename T>
   		bool operator==(const random_access_iterator<T> lhs,
              			const random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

	// For iterator == const_itrator
	template<typename T_L, typename T_R>
    	bool operator==(const random_access_iterator<T_L> lhs,
              			const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

	template <typename T>
   		bool operator!=(const random_access_iterator<T> lhs,
              			const random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

	// For iterator == const_iterator
	template<typename T_L, typename T_R>
    	bool operator!=(const random_access_iterator<T_L> lhs,
            			const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

	template <typename T>
   		bool operator<(const random_access_iterator<T> lhs,
             	const random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

	/* For iterator < const_iterator */
    template<typename T_L, typename T_R>
    	bool operator<(const random_access_iterator<T_L> lhs,
              const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

	template <typename T>
   		bool operator>(const random_access_iterator<T> lhs,
              const random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

	/* For iterator > const_iterator */
    template<typename T_L, typename T_R>
    	bool operator>(const random_access_iterator<T_L> lhs,
              const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

	template <typename T>
   		bool operator<=(const random_access_iterator<T> lhs,
              const random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

	/* For iterator <= const_iterator */
    template<typename T_L, typename T_R>
    	bool operator<=(const random_access_iterator<T_L> lhs,
              const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

	template <typename T>
	bool operator>=(const random_access_iterator<T> lhs,
              const random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    /* For iterator >= const_iterator */
    template<typename T_L, typename T_R>
    bool operator>=(const random_access_iterator<T_L> lhs,
              const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

	template<typename T>
    random_access_iterator<T> operator+(
    	typename random_access_iterator<T>::difference_type n,
        typename ft::random_access_iterator<T>& rai)
    {
        return (rai + n);
    }
	
	template <typename T>
	typename random_access_iterator<T>::diffrence_type
	operator-(const random_access_iterator<T> lhs,
              const random_access_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }

	template<typename T_L, typename T_R>
    typename random_access_iterator<T_L>::difference_type
    operator-(const random_access_iterator<T_L> lhs,
              const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() - rhs.base());
    }
}

#endif