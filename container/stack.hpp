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

	explicit stack(const container_type& ctnr = container_type()): _vct(ctnr) {}
	virtual	~stack() {}
	bool empty()						const { return _vct.empty(); }
	size_type							size() const { return _vct.size(); }
	value_type&							top() { return _vct.back(); }
	const value_type&					top() const { return _vct.back(); }
	void push (const value_type& val)	{ _vct.push_back(val); }
	void pop() 							{ _vct.pop_back(); }

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

	container_type _vct;

	};

	// Each of the operator call the same operator of the underluing container objects
template <class T, class Container>
  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs._vct == rhs._vct; }

template <class T, class Container>
  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs._vct != rhs._vct; }

template <class T, class Container>
  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs._vct < rhs._vct; }

template <class T, class Container>
  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return lhs._vct <= rhs._vct; }
	
template <class T, class Container>
  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return lhs._vct > rhs._vct; }
	
template <class T, class Container>
  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return lhs._vct >= rhs._vct; }

}

#endif