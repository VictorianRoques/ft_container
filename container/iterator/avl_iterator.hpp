#ifndef AVL_ITERATOR_H
#define AVL_ITERATOR_H

#include "iterator.hpp"
#include "../avl_tree.hpp"
#include "../utils.hpp"

namespace ft
{
    template <typename T, typename node>
    class avl_iterator : iterator<bidirectional_iterator_tag, T>
    {
    public:

        typedef typename            iterator<bidirectional_iterator_tag, T>::value_type value_type;
        typedef ptrdiff_t           difference_type;
        typedef value_type*         pointer;
        typedef value_type&         reference;
        typedef value_type const &  const_reference;
        typedef typename            iterator<bidirectional_iterator_tag, T>::iterator_category iterator_category;

        avl_iterator() : _current(NULL) {}
        avl_iterator(node *x, node *ghost) : _current(x), _ghost(ghost) {}
        avl_iterator(const avl_iterator &src) : _current(src._current), _ghost(src._ghost) {}
        avl_iterator &operator=(const avl_iterator &src)
        {
            if (this == &src)
                return *this;
            _current = src._current;
            _ghost = src._ghost;
            return *this;
        }

        operator avl_iterator<const T, node>() const { return (avl_iterator<const T, node>(_current, _ghost)); };
        ~avl_iterator() {}

        bool operator==(const avl_iterator &x) const { return _current == x._current; }
        bool operator!=(const avl_iterator &x) const { return !(_current == x._current); }

        reference   operator*() const { return _current->value; }
        pointer     operator->() const { return &_current->value; }

        avl_iterator &operator++()
        {
            if (_current->right != NULL)
            {
                _current = minValueNode(_current->right);
            }
            else if (_current->parent != NULL)
            {
                node *tmp = _current;
                _current = _current->parent;
                while (_current && tmp == _current->right)
                {
                    tmp = _current;
                    _current = _current->parent;
                }
            }
            return *this;
        }

        avl_iterator operator++(int)
        {
            avl_iterator tmp(*this);
            this->operator++();
            return tmp;
        }

        avl_iterator &operator--()
        {
            if (_current->left != NULL)
            {
                _current = maxValueNode(_current->left);
            }
            else if (_current->parent)
            {
                node *tmp = _current;
                _current = _current->parent;
                while (_current && tmp == _current->left)
                {
                    tmp = _current;
                    _current = _current->parent;
                }
            }
             return *this;
        }

        avl_iterator operator--(int)
        {
            avl_iterator tmp(*this);
            this->operator--();
            return tmp;
        }

    protected:
    
    node *_current;
    node *_ghost;

    };
}

#endif