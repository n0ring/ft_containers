#ifndef BINARY_TREE
#define BINARY_TREE

#include "pair.hpp"


template<typename Key, typename Value>
struct node
{
		typedef Key								key_type;
		typedef Value							mapped_type;
		typedef	node<key_type, mapped_type>		node_type;
		typedef ft::Pair<const key_type, mapped_type> pair_type;		
		typedef pair_type&						reference_type;		
		typedef pair_type*						pointer;		
		
		node_type	*left;
		node_type	*right;
		node_type	*parrent;
		pair_type	pair;
		bool		isNil;
		int			height;
	
	node(node const *other) : left(other->left), right(other->right),
		parrent(other->right), pair(other->pair), isNil(false), height(other->height)
	{
	}

	node(pair_type const &p, node *nil) : left(nil), right(nil),
		parrent(nil), pair(p), isNil(false), height(0)
	{
	}
	
	node(void) : left(NULL), right(NULL), parrent(NULL), pair(), isNil(true), height(0)
	{
	}

	node &operator=(node const &other)
	{
		if (this != &other)
		{
			left = other.left;
			right = other.right;
			parrent = other.parrent;
			pair = other->pair;
			isNil = other->isNil;
		}
		return *this;
	}

	~node(void) {}


	node *subtree_first(node *locale_root)
	{
		node *tmp = locale_root;
		while (tmp->left->isNil == false)
			tmp = tmp->left;
		return (tmp);
	}

	node *subtree_first(void)
	{
		node *tmp = this;
		while (tmp->left->isNil == false)
			tmp = tmp->left;
		return (tmp);
	}

	node *subtree_last(node *root)
	{
		node *tmp = root;
		while (tmp->right->isNil == false)
			tmp = tmp->right;
		return (tmp);
	}

	node *subtree_last(void)
	{
		node *tmp = this;
		while (tmp->right->isNil == false)
			tmp = tmp->right;
		return (tmp);
	}


	node *successor(void)
	{
		node	*tmp		= this;
		node	*parrent	= tmp->parrent;

		if (tmp->right->isNil == false)
			return (subtree_first(tmp->right));
		while (parrent->isNil == false && parrent->right == tmp)
		{
			tmp = parrent;
			parrent = parrent->parrent;
		}
		return (parrent);
	}

	node *predecessor()
	{
		node *tmp		= this;
		node *parrent	= tmp->parrent;

		if (tmp->left->isNil == false)
			return (subtree_last(tmp->left));
		if (tmp->parrent->right == tmp)
			return (tmp->parrent);
		
		while (parrent->isNil == false && parrent->right != tmp)
		{
			tmp = parrent;
			parrent = parrent->parrent;
		}
		return (tmp->parrent);
	}

};

	template<typename Key, typename Value>
	bool operator==(node<Key, Value> &a, node<Key, Value> &b)
	{
		return (ft::equal(a->pair.first, b->pair.first) && ft::equal(a->pair.second, b->pair.second));
	}

	template<typename Key, typename Value>
	bool operator!=(node<Key, Value> &a, node<Key, Value> &b)
	{
		return !(a == b);
	}

	template<typename Key, typename Value>
	bool operator<(node<Key, Value> &a, node<Key, Value> &b)
	{
		if (a.pair->first < b.pair.first)
			return true;
		if (a.pair->first == b.pair.first && a.pair->second < b.pair.second)
			return true;
		return false;
	}

	template<typename Key, typename Value>
	bool operator<=(node<Key, Value> &a, node<Key, Value> &b)
	{
		return (a < b || a == b);
	}

	template<typename Key, typename Value>
	bool operator>(node<Key, Value> &a, node<Key, Value> &b)
	{
		return (b < a);
	}

	template<typename Key, typename Value>
	bool operator>=(node<Key, Value> &a, node<Key, Value> &b)
	{
		return (b < a || b == a);
	}

template<typename T, typename M, typename Alloc, typename Compare = std::less<T> >
class BStree
{
public:
		typedef node<T, M>					node;
		typedef typename node::key_type		key_type;
		typedef typename node::mapped_type	mapped_type;
		typedef ft::Pair<const key_type, mapped_type> value_type;		
		typedef Alloc												allocator_type;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::size_type					size_type;
		typedef	Compare												key_compare;
		// typedef ft::Pair<const Key, mapped_type> 					value_type;
		
		pointer 	root;
		pointer 	nil;
		Alloc		_alloc;
		key_compare _comp;
		size_type 	_size;

public:

	BStree(const key_compare& comp = key_compare(), size_type size = 0) : _comp(comp), _size(size)
	{
		nil = make_node();
		nil->left = nil;
		nil->right = nil;
		nil->parrent = nil;
		root = nil;
	}

	~BStree()
	{
		delete_tree(root);
		delete_node(nil);
	}

	// BStree(BStree const & other)
	// {
	

	// }

	BStree &operator=(BStree &other)
	{
		if (this != &other)
		{
			delete_tree(root);
			root = nil;
			root = other.clone_tree(other.root, root, nil);
			_size = other._size;
			_alloc = other._alloc;
			_comp = other._comp;
		}
		return (*this);
	}

	int subtree_size(node *subtree)
	{
		if (subtree == nil)
			return 0;
		if (subtree->left == nil && subtree->right == nil)
			return 1;
		return (subtree_size(subtree->left) + subtree_size(subtree->right) + 1);
	}

	node *find(const key_type &value) const
	{
		node *tmp = root;
		node *tmp_p = nil;

		while (tmp != nil)
		{
			if (tmp->pair.first == value)
				return tmp;
			tmp_p = tmp;
			if (_comp(value, tmp->pair.first))
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		return (tmp_p);
	}

	node *get_root() { return root; }

	void delete_node(node * to_del)
	{
		_alloc.destroy(to_del);
		_alloc.deallocate(to_del, sizeof(node));
	}

	pointer make_node(const node node_type = node()) 
	{
		node * new_node = _alloc.allocate(1);
		_alloc.construct(new_node, node_type);
		return (new_node);
	}

	pointer make_node(value_type const &p)
	{
		node *new_node = _alloc.allocate(1);
		_alloc.construct(new_node, node(p, nil));
		return (new_node);
	}

	void delete_tree(node *root)
	{
		if (root == nil)
			return ;
		delete_tree(root->left);
		delete_tree(root->right);
		delete_node(root);
	}

 	node *clone_tree(node *root, node *parrent, node *nil)
    {	
        if (root->isNil)
			return (nil);
		node *new_el = make_node(*root);
		new_el->parrent = parrent;
		new_el->left = clone_tree(root->left, new_el, nil);
		new_el->right = clone_tree(root->right, new_el, nil);
		return new_el;
    }

	node *insert_element(const key_type& k) // insert by key
	{
		node *new_node;
		node *subtree 	= find(k);
		
		if (subtree->isNil == false && subtree->pair.first == k)
			return subtree;
		new_node = make_node(ft::make_pair(k, mapped_type()));	
		_size++;
		if (subtree == nil)
		{
			root = new_node;
			return (new_node);
		}
		if (_comp(new_node->pair.first, subtree->pair.first))
			return subtree_insert_before(subtree, new_node);
		else
			return subtree_insert_after(subtree, new_node);
	}

	node *insert_element(const value_type& val) // insert pair
	{
		node *new_node;
		node *subtree 	= find(val.first);
		if (subtree->isNil == false && subtree->pair.first == val.first)
			return subtree;
		new_node = make_node(val);	
		_size++;
		if (subtree == nil)
		{
			root = new_node;
			return (new_node);
		}
		if (_comp(new_node->pair.first, subtree->pair.first))
			return subtree_insert_before(subtree, new_node);
		else
			return subtree_insert_after(subtree, new_node);
	}

	void left_rotate(node *x)
	{
		if (x->right == nil)
			return ;
		node *y = x->right;
		x->right = y->left;

		if (y->left != nil)
			y->left->parrent = x;
		y->parrent = x->parrent;
		if (x->parrent == nil)
			root = y;
		else if (x == x->parrent->left)
			x->parrent->left = y;
		else
			x->parrent->right = y;
		y->left = x;
		x->parrent = y;
        update_subtree_props(x);
	}

	void right_rotate(node *x)
	{
        if (x->left == nil)
			return ;
		node *y = x->left;
		x->left = y->right;

		if (y->right != nil)
			y->right->parrent = x;
		y->parrent = x->parrent;
		if (x->parrent == nil)
			root = y;
		else if (x == x->parrent->left)
			x->parrent->left = y;
		else
			x->parrent->right = y;
		y->right = x;
		x->parrent = y;
        update_subtree_props(x);
    }

	void update_subtree_props(node *leaf) // go up to root and update height of every node
	{
		node	*tmp = leaf;

		while (tmp->isNil == false)
		{
			if (tmp->right->isNil && tmp->left->isNil)
				tmp->height = 0;
			else
				tmp->height = std::max(tmp->left->height, tmp->right->height) + 1;
			tmp = tmp->parrent;
		}
	}

	int subtree_height(node *subtree)
	{
		if (subtree->left->isNil && subtree->right->isNil)
			return 0;
		int h_left = subtree_height(subtree->left);
		int h_right = subtree_height(subtree->right);
		return std::max(h_left, h_right) + 1;
	}

    void rotate(node *y)
    {
        node	*x;
        node	*parrent_tmp = y->parrent;

        if (y->left->height > y->right->height)
            x = y->left;
        else
            x = y->right;
        if (x->isNil || y->isNil)
            return ;
        if (y->parrent->left == y && x == y->left)
            right_rotate(y->parrent);
        else if (y->parrent->left == y && x == y->right)
        {
            left_rotate(y);
            right_rotate(parrent_tmp);
        }
        else if (y == y->parrent->right && x == y->right)
            left_rotate(parrent_tmp);
        else if (y == y->parrent->right && x == y->left)
        {
            right_rotate(y);
            left_rotate(parrent_tmp);
        }
    }

	void maintainBalance(node *subtree)
	{
		node	*subtree_to_check = subtree;
		int		skew;

		while (subtree_to_check->isNil == false)
		{
			skew = subtree_to_check->right->height - subtree_to_check->left->height;
			if (skew > 1)
            {
				rotate(subtree_to_check->right);
				return ; // need to stop?? test without
			}
			else if (skew < -1)
            {
				rotate(subtree_to_check->left);
				return ;
			}
			subtree_to_check = subtree_to_check->parrent;
		}
	}

	node* subtree_insert_after(node* subtree, node *new_el)
	{
		new_el->parrent = subtree;

		if (subtree->right == nil)
			subtree->right = new_el;
		else
			subtree->successor()->left = new_el;
		update_subtree_props(new_el);
		maintainBalance(subtree);
		return new_el;
	}

	node *subtree_insert_before(node *subtree, node *new_el)
	{
		node *prec;
		if (subtree->left == nil)
		{
			subtree->left = new_el;
			new_el->parrent = subtree;
		}
		else
		{
			prec = subtree->predecessor();
			prec->right = new_el;
			new_el = prec;
		}
		update_subtree_props(new_el);
		maintainBalance(subtree);
		return new_el;
	}

	void subtree_delete(node *el)
	{
		node *parrent = el->parrent;
		// case 1: no child
		if (el->left->isNil && el->right->isNil)
		{
			if (el != root)
			{
				if (parrent->isNil == false && parrent->left == el)
					parrent->left = nil;
				else if (parrent->isNil == false)
					parrent->right = nil;
			}
			else
				root = nil;
			delete_node(el);
		}
		// case 2: two child
		else if (el->right->isNil == false && el->left->isNil == false)
		{
			node * successor = el->successor();
			node * successor_copy = make_node(successor);
			subtree_delete(successor);
			successor_copy->right = el->right;
			successor_copy->left = el->left;
			successor_copy->parrent = el->parrent;
			if (parrent->isNil == false && parrent->left == el)
				parrent->left = successor_copy;
			else if (parrent->isNil == false)
				parrent->right = successor_copy;
			if (el->left->isNil == false)
				el->left->parrent = successor_copy;
			if (el->right->isNil == false)
				el->right->parrent = successor_copy;
			if (root == el)
				root = successor_copy;
			delete_node(el);
		}
		// case 3: only 1 child
		else
		{
			node *child = el->left->isNil ? el->right : el->left;
			if (el != root)
			{
				if (parrent->left == el)
					parrent->left = child;
				else
					parrent->right = child;
                child->parrent = el->parrent;
			}
			else
            {
                root = child;
                child->parrent = nil;
            }
			delete_node(el);
		}
		update_subtree_props(parrent);
	}
};



#endif // !RBTREE