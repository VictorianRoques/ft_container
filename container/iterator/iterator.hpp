#ifndef ITERATOR_H
# define ITERATOR_H

#include <cstddef>

/*
** @brief 
** This is a base class template, it's not an iterator class,
** it just provides some member type needed for iterator_trait class
** who are required for any valid iterator type 
** From : https://www.cplusplus.com/reference/iterator/iterator/ 
*/

namespace ft {

template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
  struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

/*
** @brief
** Empty class to identify the category of an iterator
*/

struct	random_access_iterator_tag {};
struct	bidirectional_iterator_tag {};
struct 	forward_iterator_tag {};
struct 	output_iterator_tag {};
struct 	input_iterator_tag {};

}
#endif