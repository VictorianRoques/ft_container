#ifndef VECTOR_H
# define VECTOR_H

# include <memory>
# include <stdexcept>
# include <stddef.h>
# include "iterator/random_access_iterator.hpp"
# include "iterator/reverse_iterator.hpp"
# include "utils.hpp"

namespace ft {

/*
** @brief 
** Vectors are sequence containers representing arrays that can change in size.
** From: https://www.cplusplus.com/reference/vector/vector/
*/

template < typename T, typename Alloc = std::allocator<T> >
class vector {

    public:

    typedef 			T 												value_type;
    typedef 			Alloc 											allocator_type;
    typedef typename	allocator_type::reference						reference;
    typedef typename	allocator_type::const_reference 				const_reference;
    typedef typename	allocator_type::pointer 						pointer;
    typedef typename	allocator_type::const_pointer 					const_pointer;
	typedef				ft::random_access_iterator<value_type>			iterator;
	typedef 			ft::random_access_iterator<const value_type>    const_iterator;
	typedef				ft::reverse_iterator<iterator>					reverse_iterator;
	typedef				ft::reverse_iterator<const_iterator>			const_reverse_iterator;
    typedef ptrdiff_t													difference_type;
    typedef size_t														size_type;
	
	/**************/
	/** ITERATOR **/
	/**************/
	
	iterator				begin() { return iterator(_tab); };
	const_iterator			begin() const { return const_iterator(_tab); };
	iterator				end() { return iterator(_tab + _size); };
	const_iterator			end() const { return const_iterator(_tab + _size); };
	reverse_iterator		rbegin() { return  reverse_iterator(_tab + _size); };
	const_reverse_iterator	rbegin() const { return const_reverse_iterator(_tab + _size); }
	reverse_iterator		rend() { return reverse_iterator (_tab); };
	const_reverse_iterator	rend() const { return const_reverse_iterator (_tab); };

	/**********************/
	/**	MEMBER FUNCTIONS **/
	/**********************/

	explicit vector(const allocator_type& alloc = allocator_type()): _tab(NULL),
				_size(0), _max_size(alloc.max_size()), _alloc(alloc), _capacity(0) {}
	
	explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()): _size(n),
				_max_size(alloc.max_size()), _alloc(alloc), _capacity(n)
	{
		_tab = _alloc.allocate(n);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(_tab + i, val);
	}

	template <class InputIterator>
    vector (typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first,
		InputIterator last, const allocator_type& alloc = allocator_type()):
		 _max_size(alloc.max_size()), _alloc(alloc)
	{
		_capacity = iterator_len(first, last);
		_size = _capacity;
		_tab = _alloc.allocate(_capacity);
		for (size_t i = 0; first != last; first++)
		{
			_alloc.construct(_tab + i, *first);
			i++;
		}
	}

	vector(const vector & src): _size(src._size), _max_size(src._max_size), _capacity(src._capacity)
	{
		_tab = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.construct(_tab + i, src[i]);
		}
	}

	~vector() { clear(); };

	vector&			operator=(const vector& rhs)
	{
		if (this != &rhs)
		{
			clear();
			_capacity = rhs._capacity;
			_size = rhs._size;
			_tab = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(_tab + i, rhs[i]);
			}
		}
		return *this;
	}

	/************************/
	/**** CAPACITY FUNCTION**/
	/************************/

	size_type		size() const { return _size ;};
	size_type 		max_size() const { return _max_size; };
	void resize 	(size_type n, value_type val = value_type())
	{
		if (n < _size)
		{
			while (_size > n)
			{
				_alloc.destroy(_tab + (_size - 1));
				_size--;
			}
		}
		else if (n > _capacity)
		{
			reserve(n);
			for (size_type i = _size; i < n; i++)
				_alloc.construct(_tab + i, val);
			_size = n;
		}

	}
	size_type 		capacity() const { return _capacity; };
	bool 			empty() const { return  _size ? false : true; };
	void 			reserve (size_type n)
	{
		if (n > _capacity)
		{
			if (n > _max_size)
				throw std::length_error("vector");
			vector<value_type> tmp(*this);
			clear();
			_capacity = n;
			_size = tmp._size;
			_tab = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_tab + i, tmp[i]);
			tmp.clear();
		}
	}

	/*******************/
	/*** ELEMENT ACCESS*/
	/*******************/

	reference		operator[](size_type n) { return _tab[n]; };
	const_reference operator[](size_type n) const { return _tab[n]; };
	reference		at(size_type n) {
		if (n >= _size)
			throw std::out_of_range("vector");
		return _tab[n];
	}
	const_reference	at(size_type n) const {
		if (n >= _size)
			throw std::out_of_range("vector");
		return _tab[n];
	}

	reference		front() { return _tab[0]; };
	const_reference	front() const { return _tab[0]; };
	reference		back() { return _tab[_size - 1]; };
	const_reference back() const { return _tab[_size - 1]; };

	/*******************/
	/*** MODIFIERS *****/
	/*******************/

	template <class InputIterator>
	void assign (InputIterator first,
				typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last)
	{
		size_type len = iterator_len(first, last);
		if (!len)
			return ;
		if (len > _capacity)
		{
			clear();
			_capacity = len;
			_size = len;
			_tab = _alloc.allocate(_capacity);
			for (size_type i = 0; first != last; i++)
			{
				_alloc.construct(_tab + i, *first);
				first++;
			}
		}
		else
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_tab + i);
			for (size_type i = 0; first != last; i++)
			{
				_alloc.construct(_tab + i, *first);
				first++;
			}
			_size = len;
		}
	}

	void assign (size_type n, const value_type& val)
	{
		if (!n)
			return ;
		if (n > _capacity)
		{
			clear();
			_capacity = n;
			_size = n;
			_tab = _alloc.allocate(_capacity);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_tab + i, val);
		}
		else
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_tab + i);
			for (size_type i = 0;i < n; i++)
				_alloc.construct(_tab + i, val);
			_size = n;
		}
	}

	void		push_back(const value_type& val)
	{
		if (!_size)
			reserve(1);
		else if (_size == _capacity)
			reserve(_size * 2);
		_alloc.construct(_tab + _size, val);
		_size++;
	}
	
	void		pop_back()
	{
		if (_size)
			_alloc.destroy(_tab + --_size);
	}

	iterator insert (iterator position, const value_type& val)
	{
		if (position == end())
		{
			push_back(val);
			return iterator(end() - 1);
		}
		size_type i = position - begin();
		insert(position, 1, val);
		return (iterator(begin() + i));

	}

	void		insert(iterator position, size_type n, const value_type& val)
	{
		if (!n)
			return ;
		if (position == end())
		{
			while (n)
			{
				push_back(val);
				n--;
			}
		}
		else
		{
			if (_size + n <= _capacity)
			{
				vector<value_type> tmp(position, end());
				_size += n;
				iterator it = position + n;
				iterator ite = end();
				iterator it_tmp = tmp.begin();
				while (it != ite)
				{
					_alloc.construct(it.operator->(), *it_tmp);
					it++;
					it_tmp++;
				}
				it = position;
				while (it != position + n)
				{
					*it = val;
					it++;
				}
			}
			else
			{
				size_type new_capacity;
				if (_size + n > _capacity * 2)
					new_capacity = _size + n;
				else
					new_capacity = _size * 2;
				
				size_t len_position = iterator_len(begin(), position);
				pointer new_tab = _alloc.allocate(new_capacity);
				size_t	i = 0;
				while (i < len_position)
				{
					_alloc.construct(new_tab + i, _tab[i]);
					i++;
				}
				size_t insert = i + n;
				while (i < insert)
				{
					_alloc.construct(new_tab + i, val);
					i++;
				}
				while (i < _size + n)
				{
					_alloc.construct(new_tab + i, _tab[len_position]);
					len_position++;
					i++;
				}
				for (size_t a = 0; a < _size; a++)
				{
					_alloc.destroy(_tab + a);
				}
				_alloc.deallocate(_tab, _capacity);
				_capacity = new_capacity;
				_size += n;
				_tab = new_tab;
			}
		}
	}

	template <class InputIterator>
    void insert (iterator position, InputIterator first,
				typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last)
	{
		size_type len_range = iterator_len(first, last);
		if (!len_range)
			return ;
		if (_size + len_range <= _capacity)
		{
			vector<value_type> tmp_move (position,  end());
			_size+= len_range;
			iterator it = position + len_range;
			iterator ite = end();
			iterator it_tmp = tmp_move.begin();
			while (it != ite)
			{
				_alloc.construct(it.operator->(), *it_tmp);
				it++;
				it_tmp++;
			}
			it = position;
			while (it != position + len_range)
			{
				*it = *first;
				it++;
				first++;
			}
		}
		else
		{
			size_type new_capacity;
			if (_size + len_range > _capacity * 2)
				new_capacity = _size + len_range;
			else
				new_capacity = _size * 2;
			
			size_t len_position = iterator_len(begin(), position);
			pointer new_tab = _alloc.allocate(new_capacity);
			size_t	i = 0;
			while (i < len_position)
			{
				_alloc.construct(new_tab + i, _tab[i]);
				i++;
			}
			size_t insert = i + len_range;
			while (i < insert)
			{
				_alloc.construct(new_tab + i, *first);
				i++;
				first++;
			}
			while (i < _size + len_range)
			{
				_alloc.construct(new_tab + i, _tab[len_position]);
				len_position++;
				i++;
			}
			for (size_t a = 0; a < _size; a++)
			{
				_alloc.destroy(_tab + a);
			}
			_alloc.deallocate(_tab, _capacity);
			_capacity = new_capacity;
			_size += len_range;
			_tab = new_tab;
		}
	}

	iterator erase (iterator position)
	{
		return erase(position, position + 1);
	}

	iterator erase (iterator first, iterator last) {

		iterator			it_tmp = first;
		size_type			len = iterator_len(first, last);
	
		while (last != end())
		{
			*first = *last;
			first++;
			last++;
		}
		while (len--)
			_alloc.destroy(&_tab[--_size]);

		return it_tmp;
	}

	void	swap(vector& x)
	{
		pointer			tmp_tab = _tab;
		size_type		tmp_size = _size;
		size_type		tmp_capacity = _capacity;
		allocator_type	tmp_alloc = _alloc;

		_tab = x._tab;
		_size = x._size;
		_capacity = x._capacity;
		_alloc = x._alloc;

		x._tab = tmp_tab;
		x._size = tmp_size;
		x._capacity = tmp_capacity;
		x._alloc = tmp_alloc;
	}

	void		clear()
	{
		for (size_t i = 0; i < _size; i++)
			_alloc.destroy(_tab + i);
		_alloc.deallocate(_tab, _capacity);
		_tab = NULL; _size = 0; _capacity = 0;
	};

	private:

	value_type													*_tab;
	size_type													_size;
	size_type													_max_size;
	allocator_type												_alloc;
	size_type													_capacity;
	
};

// Non-member function overloads
	
template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	for (size_t i = 0; i < lhs.size(); i++)
		if (lhs[i] != rhs[i])
			return false;
	return true;
}

	template <class T, class Alloc>
		bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}
	
	template <class T, class Alloc>
		bool operator<  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template <class T, class Alloc>
		bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}

	template <class T, class Alloc>
		bool operator>  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (rhs < lhs);
		}

	template <class T, class Alloc>
		bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}
	
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>&y)
		{
			x.swap(y);
		}

};

#endif