#ifndef RANDOMITERATOR_HPP
# define RANDOMITERATOR_HPP

namespace ft {
	template <typename type>
	class Random {

		protected:
		type			*_ptr;

		public:

		typedef  type				value_type;
		typedef	value_type&			reference;
		typedef value_type const&	const_reference;
		typedef value_type*			pointer;
		typedef	ptrdiff_t			difference_type;
		typedef size_t				size_type;
		Random(): _ptr(NULL) {};
		Random (type *src): _ptr(src) {};
		Random(const Random & src) { *this = src; };
		virtual ~Random() {};
		Random& operator=(Random const &rhs) {
			if (this != &rhs)
				_ptr = rhs._ptr;
			return *this;
		};

		value_type		*getValue(void) const {return _ptr; };
		bool			operator==(const Random &rhs) const { return _ptr  == rhs._ptr; };
		bool			operator!= (const Random &rhs) const { return _ptr != rhs._ptr; };
		bool			operator<(const Random &rhs) const { return _ptr < rhs._ptr; };
		bool			operator<=(const Random &rhs) const { return _ptr <= rhs._ptr; };
		bool			operator>(const Random &rhs) const { return _ptr > rhs._ptr; };
		bool			operator>=(const Random &rhs) const { return _ptr >= rhs._ptr; };

		value_type		operator*() { return *_ptr; };
		pointer			operator->() { return _ptr; };
		reference		operator[](size_type n) 		{ return _ptr[n]; };
		const_reference	operator[](size_type n) const	{ return _ptr[n]; };
		Random<type>	&operator++() { _ptr++; return *this; };
		Random<type>	operator++(int) { Random<type> tmp(*this); operator++(); return tmp; };
		Random<type>	&operator--() { _ptr--; return *this; };
		Random<type>	operator--(int) { Random<type> tmp(*this); operator--(); return tmp; };

		difference_type	operator-(const Random &rhs) const { return (_ptr - rhs._ptr); };
		Random<type>	operator+(difference_type n) const { return Random(_ptr + n); };
		Random<type>	operator+(difference_type);
		Random<type>	operator-(difference_type n) const { return Random(_ptr - n); };
		// friend Random<type>	operator+(difference_type n, const Random &rhs) { return rhs._ptr + n; };

		Random<type>	operator+=(difference_type n) { _ptr += n; return _ptr; };
		Random<type>	operator-=(difference_type n) { _ptr -= n; return _ptr; };

	};
}

#endif