#ifndef BINARY_TREE
#define BINARY_TREE

#include "pair.hpp"

#define BLACK			0
#define RED				1
#define DOUBLE_BLACK	2



template<typename value_type>
struct node
{	

		typedef 	value_type& 			reference_type;
		typedef		value_type*				pointer;

		node		*left;
		node		*right;
		node		*parent;
		value_type	value;
		bool		isNil;
		int			height;
		char		color;
	
	node(node const *other) : left(other->left), right(other->right),
		parent(other->right), value(other->value), isNil(false), height(other->height), color(other->color)
	{
	}




	node(value_type const &p, node *nil) : left(nil), right(nil),
		parent(nil), value(p), isNil(false), height(0), color(BLACK)
	{
	}
	
	// for nil el
	node(void) : left(NULL), right(NULL), parent(NULL), value(), isNil(true), height(0), color(BLACK)
	{
		left = this;
		right = this;
		parent = this;
	}

	node &operator=(node const &other)
	{
		if (this != &other)
		{
			left = other.left;
			right = other.right;
			parent = other.parent;
			value = other->value;
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
		node	*parent	= tmp->parent;

		if (tmp->right->isNil == false)
			return (subtree_first(tmp->right));
		while (parent->isNil == false && parent->right == tmp)
		{
			tmp = parent;
			parent = parent->parent;
		}
		return (parent);
	}

	node *predecessor()
	{
		node *tmp		= this;
		node *parent	= tmp->parent;

		if (tmp->left->isNil == false)
			return (subtree_last(tmp->left));
		if (tmp->parent->right == tmp)
			return (tmp->parent);
		
		while (parent->isNil == false && parent->right != tmp)
		{
			tmp = parent;
			parent = parent->parent;
		}
		return (tmp->parent);
	}
	bool isOnLeft(void) { return this == parent->left; }

	node *uncle(void)
	{
	if (parent->isNil ||  parent->parent->isNil)
		return parent->isNil ;
	if (parent->isOnLeft())
		return parent->parent->right;
	else
		return parent->parent->left;
	}

	node *sibling(void)
	{
		if (parent->isNil)
			return parent;
		if (isOnLeft())
			return parent->right;
		else
			return parent->left;
	}

	void moveDown(node *nParent)
	{
		if (parent->isNil == false)
		{
			if (isOnLeft())
				parent->left = nParent;
			else
				parent->right = nParent;
		}
		nParent->parent = parent;
		parent = nParent;
	}

	bool hasRedChild() { return (left->color == RED || right->color == RED); }

};
	template<typename value_type>
	bool operator==(node<value_type> &a, node<value_type> &b)
	{
		return (a->value == b->value);
	}

	template<typename value_type>
	bool operator!=(node<value_type> &a, node<value_type> &b)
	{
		return !(a == b);
	}

	template<typename value_type>
	bool operator<(node<value_type> &a, node<value_type> &b)
	{
		if (a.value < b.value)
			return true;
		if (a.value == b.value && a.value->second < b.value.second)
			return true;
		return false;
	}

	template<typename value_type>
	bool operator<=(node<value_type> &a, node<value_type> &b)
	{
		return (a < b || a == b);
	}

	template<typename value_type>
	bool operator>(node<value_type> &a, node<value_type> &b)
	{
		return (b < a);
	}

	template<typename value_type>
	bool operator>=(node<value_type> &a, node<value_type> &b)
	{
		return (b < a || b == a);
	}

template<typename value_type, typename Compare, typename Alloc>
class Tree
{
public:
		typedef node<value_type>								node;	
		typedef size_t											size_type;
		typedef	Compare											key_compare;
		typedef typename Alloc::template rebind<node>::other	alloc;
		
		node		*nil;
		node		*root;
		size_type	_size;
		key_compare	_comp;
		alloc		_alloc;

public:




	void delete_node(node *n)
	{
		_alloc.deallocate(n, sizeof(node));
	}

	Tree(const key_compare& comp = key_compare(), size_type size = 0) : _size(size), _comp(comp)
	{
		nil = _alloc.allocate(1);
		_alloc.construct(nil, node());
		nil->left = nil;
		nil->right = nil;
		nil->parent = nil;
		root = nil;
	}

	~Tree()
	{
		delete_tree(root);
		delete nil;
	}

	Tree(Tree const & other) : nil(new node()), root(nil),
		_size(other._size), _comp(other._comp)
	{
		root = other.clone_tree(other.root, root, nil);
	}

	Tree &operator=(Tree const &other)
	{
		if (this != &other)
		{
			delete_tree(root);
			root = nil;
			root = other.clone_tree(other.root, root, nil);
			_size = other._size;
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

	node *find(const value_type& value) const
	{
		node *tmp = root;
		node *tmp_p = nil;

		while (tmp != nil)
		{
			if (tmp->value == value)
				return tmp;
			tmp_p = tmp;
			if (_comp(value, tmp->value))
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		return (tmp_p);
	}

	node *get_root() { return root; }

	void delete_tree(node *root)
	{
		if (root == nil)
			return ;
		delete_tree(root->left);
		delete_tree(root->right);
		delete root;
	}

	node *make_node(const node node_type = node())
	{
		node * new_node = _alloc.allocate(1);
		_alloc.construct(new_node, node_type);
		return (new_node);
	}

	node *make_node(void)
	{
		node * new_node = _alloc.allocate(1);
		_alloc.construct(new_node, node());
		return (new_node);
	}

	node *make_node(value_type const &p)
	{
		node *new_node = _alloc.allocate(1);
		_alloc.construct(new_node, node(p, nil));
		return (new_node);
	}

 	node *clone_tree(node const *root, node *parent, node *nil) const
	{	
		if (root->isNil)
			return (nil);
		node *new_el = new node(*root);
		// node *new_el = make_node(*root);

		new_el->parent = parent;
		new_el->left = clone_tree(root->left, new_el, nil);
		new_el->right = clone_tree(root->right, new_el, nil);
		return new_el;
	}

	node *insert_element(const value_type& val, node *sub = NULL) // insert value
	{
		node *new_node;
		node *subtree;
		
		if (sub == NULL)
			subtree 	= find(val);
		else
			subtree = sub;
	
		if (subtree->isNil == false && subtree->value == val)
			return subtree;
		new_node = make_node(val);
		new_node->color = RED;	
		_size++;
		if (subtree == nil)
			root = new_node;
		else if (_comp(new_node->value, subtree->value))
			subtree_insert_before(subtree, new_node);
		else
			subtree_insert_after(subtree, new_node);
		maintain_balance(new_node);
		return new_node;
	}

	void maintain_balance(node *x)
	{
		node *parent		= x->parent;
		node *grand_parrent	= parent->parent;
		node *uncle;

		if (grand_parrent->left == parent)
			uncle = grand_parrent->right;
		else
			uncle = grand_parrent->left;

		if (x == root)
			x->color = BLACK;
		if (parent->color != BLACK && x != root)
		{
			if (uncle->color == RED)
			{
				parent->color = BLACK;
				uncle->color = BLACK;
				if (grand_parrent->isNil == false)
					grand_parrent->color = RED;
				maintain_balance(grand_parrent);
			}
			else if (uncle->color == BLACK)
				rotate(parent);
		}
	}

	void left_rotate(node *x)
	{
		if (x->right == nil)
			return ;
		node *y = x->right;
		x->right = y->left;

		if (y->left != nil)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == nil)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void right_rotate(node *x)
	{
		if (x->left == nil)
			return ;
		node *y = x->left;
		x->left = y->right;

		if (y->right != nil)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == nil)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->right = x;
		x->parent = y;
		// update_subtree_props(x);
	}


	void rotate(node *y) // parent 
	{
		node	*x;
		node	*parrent_tmp = y->parent;

		if (y->left->height > y->right->height)
			x = y->left;
		else
			x = y->right;
		if (x->isNil || y->isNil)
			return ;
		if (y->parent->left == y && x == y->left)  // left left case
		{
			right_rotate(parrent_tmp);
			std::swap(parrent_tmp->color, y->color);
		}
		else if (y->parent->left == y && x == y->right) // left right case
		{
			left_rotate(y);
			right_rotate(parrent_tmp);
			std::swap(parrent_tmp->color, y->color);
		}
		else if (y == y->parent->right && x == y->right) // right right case
		{
			left_rotate(parrent_tmp);
			std::swap(parrent_tmp->color, y->color);
		}
		else if (y == y->parent->right && x == y->left) // right left case
		{
			right_rotate(y);
			left_rotate(parrent_tmp);
			std::swap(parrent_tmp->color, y->color);
		}
	}

	node* subtree_insert_after(node* subtree, node *new_el)
	{
		new_el->parent = subtree;

		if (subtree->right == nil)
			subtree->right = new_el;
		else
			subtree->successor()->left = new_el;
		return new_el;
	}

	node *subtree_insert_before(node *subtree, node *new_el)
	{
		node *prec;
		if (subtree->left == nil)
		{
			subtree->left = new_el;
			new_el->parent = subtree;
		}
		else
		{
			prec = subtree->predecessor();
			prec->right = new_el;
			new_el = prec;
		}
		return new_el;
	}

	void swapColors(node *x1, node *x2) { std::swap(x1->color, x2->color); }


	void fixRedRed(node *x)
	{
	// if x is root color it black and return
		if (x == root)
		{
			x->color = BLACK;
			return ;
		}

	// initialize parent, grandparent, uncle
		node *parent = x->parent, *grandparent = parent->parent,
			*uncle = x->uncle();

		if (parent->color != BLACK)
		{
			if (uncle->isNil == false && uncle->color == RED)
			{ // uncle red, perform recoloring and recurse
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				fixRedRed(grandparent);
			} else
			{ // Else perform LR, LL, RL, RR
				if (parent->isOnLeft())
				{
					if (x->isOnLeft())
					{ // for left right
						swapColors(parent, grandparent);
					}
					else
					{
						left_rotate(parent);
						swapColors(x, grandparent);
					}
					// for left left and left right
					right_rotate(grandparent);
					} else {
				if (x->isOnLeft())
				{ // for right left
					right_rotate(parent);
					swapColors(x, grandparent);
				}
				else
					swapColors(parent, grandparent);
				leftRotate(grandparent); // for right right and right left
				}
			}
		}
	}

	node *BSTreplace(node *x)
	{
	// when node have 2 children
		if (x->left->isNil == false && x->right->isNil == false)
			return x->successor();
	// when leaf
		if (x->left->isNil && x->right->isNil)
			return x->left;
	// when single child
		if (x->left->isNil == false)
			return x->left;
		else
			return x->right;
	}

	void subtree_delete(node *v)
	{
		node *u = BSTreplace(v);
		// True when u and v are both black
		bool uvBlack = ((u->isNil || u->color == BLACK) && (v->color == BLACK));
		node *parent = v->parent;

		if (u->isNil)
		{
			// u is NULL therefore v is leaf
			if (v == root) { root = nil; }
			else
			{
			if (uvBlack)
			{
			// u and v both black
			// v is leaf, fix double black at v
			fixDoubleBlack(v);
			}
			else
			{	// u or v is red
				if (v->sibling()->isNil == false) // sibling is not null, make it red"
					v->sibling()->color = RED;
			}
			// delete v from the tree
			if (v->isOnLeft())
				parent->left = nil;
			else
				parent->right = nil;
			}
			delete v;
			return;
		}
		if (v->left->isNil || v->right->isNil)
		{	// v has 1 child
			if (v == root)
			{	// v is root, assign the u to root and delete v
				root = u;
				u->left = u->right = u->parent = nil;
				delete v;
			}
			else
			{	// Detach v from tree and move u up
				if (v->isOnLeft())
					parent->left = u;
				else
					parent->right = u;
				delete v;
				u->parent = parent;
				if (uvBlack)
				{	// u and v both black, fix double black at u
					fixDoubleBlack(u);
				}
				else
				{	// u or v red, color u black
					u->color = BLACK;
				}
			}
			return;
		}
		// v has 2 children, swap values with successor and recurse
		swapValues(u, v);
		subtree_delete(u);
	}

	void swapValues(node *u, node *v)
	{
		node * successor_copy = make_node(*u);
		successor_copy->right = v->right;
		successor_copy->left = v->left;
		successor_copy->parent = v->parent;
		if (v->parent->isNil == false && v->isOnLeft())
			v->parent->left = successor_copy;
		else if (v->parent->isNil == false)
			v->parent->right = successor_copy;
		if (v->left->isNil == false)
			v->left->parent = successor_copy;
		if (v->right->isNil == false)
			v->right->parent = successor_copy;
		if (root == v)
			root = successor_copy;
		delete v;
	}

	void fixDoubleBlack(node *x)
	{
		if (x == root) // Reached root
			return ;

		node *sibling = x->sibling(), *parent = x->parent;
		if (sibling->isNil)
		{ // No sibiling, double black pushed up
			fixDoubleBlack(parent);
		}
		else
		{
			if (sibling->color == RED)
			{	// Sibling red
				parent->color = RED;
				sibling->color = BLACK;
				if (sibling->isOnLeft()) // left case
					right_rotate(parent);
				else	// right case
					left_rotate(parent);
				fixDoubleBlack(x);
			}
			else
			{	// Sibling black
				if (sibling->hasRedChild())
				{	// at least 1 red children
					if (sibling->left != NULL && sibling->left->color == RED)
					{
						if (sibling->isOnLeft())
						{	// left left
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							right_rotate(parent);
						}
						else
						{	// right left
							sibling->left->color = parent->color;
							right_rotate(sibling);
							left_rotate(parent);
						}
					}
					else
					{
						if (sibling->isOnLeft())
						{	// left right
							sibling->right->color = parent->color;
							left_rotate(sibling);
							right_rotate(parent);
						}
						else
						{	// right right
							sibling->right->color = sibling->color;
							sibling->color = parent->color;
							left_rotate(parent);
						}
					}
					parent->color = BLACK;
				}
				else
				{	// 2 black children
					sibling->color = RED;
					if (parent->color == BLACK)
						fixDoubleBlack(parent);
					else
						parent->color = BLACK;
				}
			}
		}
	}
};




#endif // !RBTREE