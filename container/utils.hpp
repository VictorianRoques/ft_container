#ifndef UTILS_H
# define UTILS_H

# include <iostream>

namespace ft {

	typedef size_t										size_type;
	template <class InputIterator>
	size_type	iterator_len(InputIterator first, InputIterator last)
	{
		size_type i = 0;
		while (first != last)
		{
			first++;
			i++;
		}
		return i;
	}


	template < bool B, class T = void >
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <class I> struct is_integral { static const bool value = false;};
	template <> struct is_integral<bool> { static const bool value = true; };
	template <> struct is_integral<char> { static const bool value = true; };
	template <> struct is_integral<short int> { static const bool value = true; };
	template <> struct is_integral<int> { static const bool value = true; };
	template <> struct is_integral<long int> { static const bool value = true; };
	template <> struct is_integral<long long int> { static const bool value = true; };
	template <> struct is_integral<unsigned char> { static const bool value = true; };
	template <> struct is_integral<unsigned short int> { static const bool value = true; };
	template <> struct is_integral<unsigned int> { static const bool value = true; };
	template <> struct is_integral<unsigned long int> { static const bool value = true; };
	template <> struct is_integral<unsigned long long int> { static const bool value = true; };

	
	// Lexicographical_compare
	template <class InputIterator1, class InputIterator2>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || *first2 < *first1) return false;
                else if (*first1 < *first2) return true;
                ++first1;
                ++first2;
            }
            return (first2 != last2);
        }

}
#endif