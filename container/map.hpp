#ifndef MAP_H
# define MAP_H

# include <memory>
# include "avl_tree.hpp"
# include "iterator/avl_iterator.hpp"
# include "iterator/reverse_iterator.hpp"

namespace ft
{

template < class Key,                                    
           class T,                                      
           class Compare = std::less<Key>,                    
           class Alloc = std::allocator<pair<const Key, T> >
           >
class map
{
    public:

    typedef Key                                                 key_type;
    typedef T                                                   mapped_type;
    typedef ft::pair<const key_type, mapped_type>               value_type;
    typedef Compare                                             key_compare;
    typedef Alloc                                               allocator_type;
    typedef typename allocator_type::reference                  reference;
    typedef typename allocator_type::const_reference            const_reference;
    typedef typename allocator_type::pointer                    pointer;
    typedef typename allocator_type::const_pointer              const_pointer;

    typedef ft::Node<value_type>                                node_type;

    typedef ft::avl_iterator<value_type, node_type>		        iterator;
	typedef ft::avl_iterator<const value_type, node_type>       const_iterator;
	typedef ft::reverse_iterator<iterator>					    reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			    const_reverse_iterator;

    typedef ptrdiff_t                                           difference_type;
    typedef size_t                                              size_type;
    typedef Node<value_type>                                    node;

    class value_compare
    {
        friend class map;
			public:
				Compare comp;
				value_compare (Compare c) 
             : comp(c) {}
			public:
				typedef bool	result_type;
				typedef			value_type first_argument_type;
				typedef			value_type second_argument_type;
				bool			operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); };
    };

    explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        : _comp(comp), _alloc(alloc) {}

    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : _comp(comp), _alloc(alloc)
    {
        insert(first, last);
    }

    map(const map &x): _comp(x._comp)
    {
        insert(x.begin(), x.end());
    }

    ~map() {}

    map& operator=(const map& x)
    {
        if (this != &x)
        {
            _tree.clear();
            insert(x.begin(), x.end());            
        }
        return *this;
    }

    /*
    ** ITERATOR ** 
    */

    iterator                begin()         { return iterator(_tree.begin()); }
    const_iterator          begin() const   { return const_iterator(_tree.begin()); }
    iterator                end()           { return iterator (_tree.end()); }
    const_iterator          end() const     { return const_iterator(_tree.end()); }

    reverse_iterator        rbegin()        { return reverse_iterator(_tree.end()); }
    const_reverse_iterator  rbegin() const  { return const_reverse_iterator(_tree.end()); }
    reverse_iterator        rend()          { return reverse_iterator(_tree.begin()); }
    const_reverse_iterator  rend() const    { return const_reverse_iterator(_tree.begin()); }
    
    /*
    ** Capacity
    */

    bool                empty() const       { return _tree.empty(); }
    size_type           size() const        { return _tree.getSize(); }
    size_type           max_size() const    { return _tree.getMaxSize(); }

    /*
    ** Element Access
    */

    mapped_type& operator[] (const key_type& k)
    {
        pair<iterator, bool> ret = insert(value_type(k, mapped_type()));
        return ret.first->second;
    }

    /*
    ** Modifiers
    */

    pair<iterator, bool> insert(const value_type &val)
    {
        pair<iterator, bool> ret;
        if (count(val.first))
            ret.second = false;
        else
        {
            _tree.insert(val);
            ret.second = true;
        }
        ret.first = find(val.first);
        return ret;
    }

    iterator insert (iterator position, const value_type& val)
    {
        (void)position;
        return insert(val).first;
    }

    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        while (first != last)
        {
            insert(*first);
            first++;
        }
    }
    void    clear()
    {
        _tree.clear();
    }
    void    swap(map& x)
    {
        _tree.swap(x._tree);
    }

    void    erase(iterator position)
    {
        if (count(position->first))
            _tree.erase(position->first);
    }

    size_type erase (const key_type& k)
    {
        if (count(k))
        {
            _tree.erase(k); 
            return 1;
        }
        return 0;
    }

    void    erase(iterator first, iterator last)
    {
        while (first != last)
        {
            erase(first);
            first++;
        }
    }

    /*
    ** Observers
    */

    key_compare     key_comp() const    { return key_compare(); }
    value_compare   value_comp() const  { return value_compare(key_compare()); }

    /*
    ** Operations
    */

    iterator    find(const key_type& k)
    {
        iterator it = this->begin();
        iterator ite = this->end();
        while (it != ite)
        {
            if (!key_comp()(k, it->first) && !key_comp()(it->first, k))
                return it;
            it++;
        }
        return ++it;
    }

    const_iterator find (const key_type& k) const
    {
        const_iterator it = begin();
        const_iterator ite = end();
        while (it != ite)
        {
            if (!key_comp()(k, it->first) && !key_comp()(it->first, k))
                return it;
            it++;
        }
        return ++it;
    }

    size_type       count(const key_type& k) const {

        if (_tree.empty())
            return 0;
        const_iterator it = begin();
        const_iterator ite = end();
        while (it != ite)
        {
            if (!key_comp()(k, it->first) && !key_comp()(it->first, k))
                return 1;
            it++;
        }
        return 0;
    }

    iterator lower_bound (const key_type& k)
    {
        iterator it = begin(), ite = end();
	    while (it != ite)
	    {
		    if (!_comp(it->first, k))
			    break;
		    ++it;
	    }
	    return it;
    }

    const_iterator lower_bound (const key_type& k) const
    {
        const_iterator it = begin(), ite = end();
	    while (it != ite)
	    {
		    if (!_comp(it->first, k))
			    break;
		    ++it;
	    }
	    return it;
    }

    iterator    upper_bound(const key_type& k)
    {
        iterator it = begin(), ite = end();
	    while (it != ite)
	    {
		    if (_comp(k, it->first))
			    break;
		    ++it;
	    }
	    return it;
    }

    const_iterator upper_bound (const key_type& k) const
    {
        const_iterator it = begin(), ite = end();
	    while (it != ite)
	    {
		    if (_comp(k, it->first))
			    break;
		    ++it;
	    }
	    return it;
    }
    
    pair<const_iterator,const_iterator> equal_range (const key_type& k) const
    {
        ft::pair<const_iterator, const_iterator>    ret;

	    ret.first = lower_bound(k);
        ret.second = upper_bound(k);
        return ret;
    }

    pair<iterator,iterator>             equal_range (const key_type& k)
    {
        ft::pair<iterator, iterator>    ret;

	    ret.first = lower_bound(k);
        ret.second = upper_bound(k);
        return ret;
    }

    allocator_type get_allocator() const
    {
        return allocator_type();
    }

    private:

    key_compare                             _comp;
    allocator_type                          _alloc;
    AVL_tree<Key, T, Compare, Alloc>                        _tree;
};

template<class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
{
    return (lhs == rhs ? false : true);
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), --lhs.end(), rhs.begin(), --rhs.end());
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
{
	return !(rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
{
	return (rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
{
	return !(lhs < rhs);
}

template<class Key, class T, class Compare, class Alloc>
void	swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs)
{
	lhs.swap(rhs);
}
}

#endif