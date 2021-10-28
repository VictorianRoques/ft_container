#ifndef VECTOR_H
# define VECTOR_H

# include <memory>
# include <stdexcept>
# include <stddef.h>
# include "utils.hpp"

namespace ft {

template < typename T, typename Alloc = std::allocator<T> >
class vector {

    public:

    typedef T 														value_type;
    typedef Alloc 													allocator_type;
    typedef typename std::allocator<value_type>::reference			reference;
    typedef typename std::allocator<value_type>::const_reference 	const_reference;
    typedef typename std::allocator<value_type>::pointer 			pointer;
    typedef typename std::allocator<value_type>::const_pointer 		const_pointer;
    typedef ptrdiff_t												difference_type;
    typedef size_t													size_type;
	
	/**************/
	/** ITERATOR **/
	/**************/
	
	class iterator {
	
	public:

		// typedef iterator_category	random_access_iterator_tag;
		typedef T					value_type;
		typedef	value_type&			reference;
		typedef value_type const&	const_reference;
		typedef value_type*			pointer;
		typedef	ptrdiff_t			difference_type;
		typedef size_t				size_type;

		iterator(void) : _ptr(NULL) {};
		iterator(pointer src) : _ptr(src) {};
		iterator(const iterator& src): _ptr(src._ptr) {};
		iterator&  operator=(const iterator & src) { 
			if (this != &src)
			{
				_ptr = src._ptr;
			}
			return *this;
		}
		bool			operator==(const iterator &rhs) const { return _ptr  == rhs._ptr; };
		bool			operator!= (const iterator &rhs) const { return _ptr != rhs._ptr; };
		bool			operator<(const iterator &rhs) const { return _ptr < rhs._ptr; };
		bool			operator<=(const iterator &rhs) const { return _ptr <= rhs._ptr; };
		bool			operator>(const iterator &rhs) const { return _ptr > rhs._ptr; };
		bool			operator>=(const iterator &rhs) const { return _ptr >= rhs._ptr; };

		reference		operator*() { return *_ptr; };
		pointer			operator->() { return _ptr; };
		reference		operator[](size_type n) 		{ return _ptr[n]; };
		const_reference	operator[](size_type n) const	{ return _ptr[n]; };
		iterator		&operator++() { _ptr++; return *this; };
		iterator		operator++(int) { iterator tmp(*this); operator++(); return tmp; };
		iterator		&operator--() { _ptr--; return *this; };
		iterator		operator--(int) { iterator tmp(*this); operator--(); return tmp; };
		iterator		operator+(difference_type n) { return _ptr + n; };
		friend iterator operator+(const iterator &a, const iterator &b) { return a._ptr + b._ptr; };
		iterator		operator-(difference_type n) { return _ptr - n; };
		difference_type	operator-(iterator &x) const { return _ptr - x._ptr; };


	private:
		pointer	 _ptr;
	};

	/**********************/
	/** REVERSE ITERATOR **/
	/**********************/

	class reverse_iterator {
		
		public:

		typedef T					value_type;
		typedef	value_type&			reference;
		typedef value_type const&	const_reference;
		typedef value_type*			pointer;
		typedef	ptrdiff_t			difference_type;
		typedef size_t				size_type;

		reverse_iterator(void) : _ptr(NULL) {};
		reverse_iterator(pointer src) : _ptr(src) {};
		reverse_iterator(const reverse_iterator& src): _ptr(src._ptr) {};
		reverse_iterator& operator=(const reverse_iterator & src) { 
			if (this != &src)
			{
				_ptr = src._ptr;
			}
			return *this;
		}

		bool			operator!= (const reverse_iterator &rhs) const { return _ptr != rhs._ptr; };

		reference			operator*() { return *_ptr; };
		pointer				operator->() { return _ptr; };
		reference			operator[](size_type n) 		{ return _ptr[n]; };
		const_reference		operator[](size_type n) const	{ return _ptr[n]; };
		reverse_iterator	&operator++() { _ptr--; return *this; };
		reverse_iterator	operator++(int) {reverse_iterator tmp(*this); operator++(); return tmp; };
		reverse_iterator	&operator--() { _ptr++; return *this; };
		reverse_iterator	operator--(int) { reverse_iterator tmp(*this); operator--(); return tmp; };
		reverse_iterator	operator+(difference_type n) { return _ptr - n; };
		reverse_iterator	operator-(difference_type n) { return _ptr + n; };
	
		private:
			pointer	 _ptr;
	};

	iterator			begin() { return iterator(_tab); };
	iterator			end() { return iterator(_tab + _size); };
	reverse_iterator	rbegin() { return  reverse_iterator(_tab + (_size - 1)); };
	reverse_iterator	rend() { return reverse_iterator (_tab - 1); };

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
		_tab = _alloc.allocate(_capacity);
		for (; first != last; first++)
		{
			_alloc.construct(&_tab[_size++], *first);
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
	bool 			empty() const { return  _size ? true : false; };
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
		if (_size == _capacity)
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
			if (_size + n > _capacity * 2)
				_capacity = _size + n;
			else if (_size + n > _capacity)
				_capacity = _size * 2;

			vector<value_type> tmp;
			iterator it = begin();
			size_type i = 0;
			tmp._size = _capacity;
			tmp._tab = _alloc.allocate(_capacity);
			for (; it != position; it++)
			{
				_alloc.construct(tmp._tab + i, *it);
				i++;
			}
			for (size_type j = i + n; i < j; i++)
				_alloc.construct(tmp._tab + i, val);
			for (; it != end(); it++)
			{
				_alloc.construct(tmp._tab + i, *it);
				i++;
			}

			size_type len = iterator_len(begin(), position);
			for (size_type a = len; a < tmp._size; a++)
			{
				if (a > _size)
					_alloc.construct(_tab + a, tmp._tab[a]);
				else
					_tab[a] = tmp._tab[a];
			}
			_size += n;
			tmp.clear();
		}
	}

	template <class InputIterator>
    void insert (iterator position, InputIterator first,
				typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last)
	{
		size_type len = iterator_len(first, last);
		if (!len)
			return ;
		if (_size + len > _capacity * 2)
			_capacity = _size + len;
		else if (_size + len > _capacity)
			_capacity = _size * 2;

		vector<value_type> tmp;
		tmp._tab = _alloc.allocate(_capacity);
		iterator start = begin();

		size_type i = 0;
		for (; start != position; start++)
		{
			_alloc.construct(tmp._tab + i, *start);
			i++;
		}
		while (first != last)
		{
			_alloc.construct(tmp._tab + i, *first);
			first++;
			i++;
		}
		for (; start != end(); start++)
		{
			_alloc.construct(tmp._tab + i, *start);
			i++;
		}
		for (size_type x = 0; x < _size + len ; x++)
		{
			if (x > _size)
				_alloc.construct(_tab + x, tmp._tab[x]);
			else
				_tab[x] = tmp._tab[x];
		}
		_size += len;
		tmp.clear();
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


	private:

	value_type													*_tab;
	size_type													_size;
	size_type													_max_size;
	allocator_type												_alloc;
	size_type													_capacity;
	
	void		clear()
	{
		for (size_t i = 0; i < _size; i++)
			_alloc.destroy(_tab + i);
		_alloc.deallocate(_tab, _capacity);
		_tab = NULL; _size = 0; _capacity = 0;
	};
};
};

#endif