#ifndef ITERATOR_TRAITS_H
# define ITERATOR_TRAITS_H

/*
** @brief 
** Traits class defining proprietes of iterators.
** Standard algorithms determine certain proprieties of the iterator passed to them
** For every iterator type, a corresponding specialization of iterator_traits class tempalte shall be defined
** From : https://www.cplusplus.com/reference/iterator/iterator_traits/
*/

namespace ft {

template <class Iterator>
struct iterator_traits {
	
	typedef typename		Iterator::difference_type 	difference_type;
	typedef typename		Iterator::value_type		value_type;
	typedef typename		Iterator::pointer			pointer;
	typedef typename		Iterator::reference			reference;
	typedef typename		Iterator::iterator_category	iterator_category;

};

template <class T> struct iterator_traits<T*>
{
	typedef ptrdiff_t					difference_type;
	typedef T 							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <class T> struct iterator_traits<const T*>
{
	typedef	ptrdiff_t					difference_type;
	typedef	T							value_type;
	typedef	const T*					pointer;
	typedef const T&					reference;
	typedef random_access_iterator_tag	iterator_category;
};

}

#endif