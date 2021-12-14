#ifndef STACK_H
# define STACK_H

# include "vector.hpp"

namespace ft {

template <class T, class Container = vector<T> >
class stack {
	
public:

	typedef	T						value_type;
	typedef Container				container_type;
	typedef	size_t					size_type;

	explicit stack(const container_type& ctnr = container_type()): c(ctnr) {}
	bool empty()						const { return c.empty(); }
	size_type							size() const { return c.size(); }
	value_type&							top() { return c.back(); }
	const value_type&					top() const { return c.back(); }
	void push (const value_type& val)	{ c.push_back(val); }
	void pop() 							{ c.pop_back(); }

	template <class Tn, class ContainerN>
	friend bool operator== (const stack<Tn, ContainerN>& lhs, const stack<Tn, ContainerN>& rhs);

	template <class Tn, class ContainerN>
	friend bool operator!= (const stack<Tn, ContainerN>& lhs, const stack<Tn, ContainerN>& rhs);
		
	template <class Tn, class ContainerN>
	friend bool operator< (const stack<Tn, ContainerN>& lhs, const stack<Tn, ContainerN>& rhs);

	template <class Tn, class ContainerN>
	friend bool operator<= (const stack<Tn, ContainerN>& lhs, const stack<Tn, ContainerN>& rhs);

	template <class Tn, class ContainerN>
	friend bool operator> (const stack<Tn, ContainerN>& lhs, const stack<Tn, ContainerN>& rhs);

	template <class Tn, class ContainerN>
	friend bool operator>= (const stack<Tn, ContainerN>& lhs, const stack<Tn, ContainerN>& rhs);

protected:

	container_type c;

	};

	// Each of the operator call the same operator of the underluing container objects
template <class T, class Container>
  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs.c == rhs.c; }

template <class T, class Container>
  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs.c != rhs.c; }

template <class T, class Container>
  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs.c < rhs.c; }

template <class T, class Container>
  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return lhs.c <= rhs.c; }
	
template <class T, class Container>
  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return lhs.c > rhs.c; }
	
template <class T, class Container>
  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return lhs.c >= rhs.c; }

}

#endif