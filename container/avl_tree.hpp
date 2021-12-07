#ifndef AVL_TREE_H
# define AVL_TREE_H

# include "utils.hpp"
# include "iterator/avl_iterator.hpp"

namespace ft
{

template <  class Key,
            class T,
            class Compare = std::less<Key>,
            class Alloc = std::allocator<pair<const Key, T> >
        >

class AVL_tree
{
    public:

    typedef Key                                 key_type;
    typedef T                                   mapped_type;
    typedef ft::pair<const Key, T>              value_type;
    typedef Compare                             key_compare;
    typedef Node<value_type>                    node;
    typedef Alloc                               allocator_type;
    typedef ft::avl_iterator<value_type, node>  iterator;
    typedef size_t                              size_type;

    AVL_tree(const allocator_type& alloc = allocator_type())
    : _pairAlloc(alloc), _root(NULL), _lastElem(NULL), _size(0)
    {
        _ghost = _nodeAlloc.allocate(1);
        _ghost->height = 0;
        _ghost->right = NULL;
        _ghost->left = NULL;
    }

    ~AVL_tree() { delete_nodes(_root);
    _nodeAlloc.deallocate(_ghost, 1);
    }

    void                clear()
    {
        delete_nodes(_root);
        _root = NULL;
        _lastElem = NULL;
        _size = 0;
    }

    void       insert(value_type value)
    {
        _root = _insert(_root, NULL, value);
        if (!_size)
        {
            _lastElem = _root;
            _lastElem->right = _ghost;
            _ghost->parent = _lastElem;
        }
        else if (!key_comp()(value.first, _lastElem->value.first))
        {
            _lastElem = _getLastElem(_root);
            _lastElem->right = _ghost;
            _ghost->parent = _lastElem;
        }
        _size++;
    }

    void        erase(const key_type& k)
    {
        bool updateLastElem = false;
        if (!_root || !_lastElem)
            return ;
        if (!key_comp()(k, _lastElem->value.first) && !key_comp()(_lastElem->value.first, k))
            updateLastElem = true;
        _root = _deleteNode(_root, k);
        if (!_size)
        {
            _root = NULL;
            _lastElem = NULL;
            return ;
        }
        if (updateLastElem)
        {
            _lastElem = _getLastElem(_root);
            _lastElem->right = _ghost;
            _ghost->parent = _lastElem;
        }
    }

    void        swap(AVL_tree& x)
    {
        if (this != &x)
        {
            allocator_type          tmpPairAlloc = _pairAlloc;
            std::allocator<node>    tmpNodeAlloc = _nodeAlloc;
            node*                   tmpRoot = _root;
            node*                   tmpLastElem = _lastElem;
            node*                   tmpGhost = _ghost;
            size_t                  tmpSize = _size;

            _pairAlloc = x._pairAlloc;
            _nodeAlloc = x._nodeAlloc;
            _root = x._root;
            _lastElem = tmpLastElem;
            _ghost = x._ghost;
            _size = x._size;

            x._pairAlloc = tmpPairAlloc;
            x._nodeAlloc = tmpNodeAlloc;
            x._root = tmpRoot;
            x._lastElem = tmpLastElem;
            x._ghost = tmpGhost;
            x._size = tmpSize;
        }
    }

    void        deleteNode(Key key)
    {
        _root = _deleteNode(_root, key);
    }

    node*   getRoot() { return _root; }

    node*   begin() const { return minValueNode(_root);}

    node*   end () const
    { 
        if (!_size || !_root)
            return _root;
        return _ghost;
    }

    bool    empty() const                       { return _size ? false : true; }
    size_t  getSize() const                     { return _size; }
    size_t  getMaxSize() const                  { return _nodeAlloc.max_size(); }
    allocator_type  get_allocator() const       { return _pairAlloc; }

    private:

    key_compare     key_comp() const { return key_compare(); }

    int     height(node *x){

        if (!x || x == _ghost)
            return 0;
        return x->height;
    }

    int     max(int a, int b)
    {
        return a > b ? a : b;
    }

    int     getBalance(node *x)
    {
        return height(x->left) - height(x->right);
    }

    node*       createNode(node* parent, value_type value)
    {
        node* tmp = _nodeAlloc.allocate(1);
        _pairAlloc.construct(&tmp->value, value);
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->height = 1;
        tmp->parent = parent;
        return tmp;
    }

    node*        _insert(node *x, node *parent, value_type value)
    {
        if (!x || x == _ghost)
            return createNode(parent, value);
        if (key_comp()(value.first, x->value.first))
            x->left = _insert(x->left, x, value);
        else if (!key_comp()(value.first, x->value.first))
            x->right = _insert(x->right, x, value);
        else
            return x;    
        return x;
    }

    node*         _deleteNode(node *x, const key_type& key)
    {
        if (!x || x == _ghost)
            return x;
          if (key_comp()(key, x->value.first))
            x->left = _deleteNode(x->left, key);
        else if (key_comp()(x->value.first, key))
            x->right = _deleteNode(x->right, key);
        else
        {
            if (!x->left && !x->right)
		    {
		    	_pairAlloc.destroy(&x->value);
                _size--;
		    	return NULL;
		    }
		    else if (!x->left)
		    {
		    	node* tmp = x->right;
		    	tmp->parent = x->parent;
		    	_pairAlloc.destroy(&x->value);
                _size--;
		    	return tmp;
		    }
		    else if (!x->right)
		    {
		    	node* tmp = x->left;
		    	tmp->parent = x->parent;
		    	_pairAlloc.destroy(&x->value);
                _size--;
		    	return tmp;
		    }
		    node* tmp = minValueNode(x->right);
		    _pairAlloc.destroy(&x->value);
		    _pairAlloc.construct(&x->value, tmp->value);
		    x->right = _deleteNode(x->right, tmp->value.first);
        }
        return x;
    }

    node*   rightRotate(node *z)
    {
        node *y = z->left;
        node *T3 = y->right;

        y->right = z;

        y->parent = z->parent;

        z->parent = y;
        z->left = T3;

        if (T3)
            T3->parent = z;
    
        y->height = 1 + max(height(y->left), height(y->right));
        z->height = 1 + max(height(z->left), height(z->right));

        return y;
    }

    node*       leftRotate(node *z)
    {
        node *y = z->right;
        node *T3 = y->left;

        y->left = z;
        y->parent = z->parent;
        z->parent = y;
        z->right = T3;

        if (T3)
            T3->parent = z;

        y->height = 1 + max(height(y->left), height(y->right));
        z->height = 1 + max(height(z->left), height(z->right));

        return y;
    }

    void       preOrder_rec(node *x)
    {
        if (x == NULL)
            return ;
        preOrder_rec(x->left);
        std::cout << x->value.first << " ";
        preOrder_rec(x->right);
    }

    void        delete_nodes(node *x)
    {
        if (x == NULL)
            return ;
        delete_nodes(x->left);
        if (x->right != _ghost)
            delete_nodes(x->right);
        _pairAlloc.destroy(&x->value);
        _nodeAlloc.deallocate(x, 1);
    }

    node*               _getLastElem(node* x)
    {
        while (x && x->right && x->right != _ghost)
            x = x->right;
        return x;
    }

    allocator_type          _pairAlloc;
    std::allocator<node>    _nodeAlloc;
    node*                   _root;
    node*                   _lastElem;
    node*                   _ghost;
    size_t                  _size;

};

}

#endif