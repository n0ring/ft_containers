#ifndef BINARY_TREE
#define BINARY_TREE

#include "pair.hpp"

#define BLACK			0
#define RED				1
#define DOUBLE_BLACK	2

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
		char		color;
	
	node(node const *other) : left(other->left), right(other->right),
		parrent(other->right), pair(other->pair), isNil(false), height(other->height), color(other->color)
	{
	}

	node(pair_type const &p, node *nil) : left(nil), right(nil),
		parrent(nil), pair(p), isNil(false), height(0), color(BLACK)
	{
	}
	
	node(void) : left(NULL), right(NULL), parrent(NULL), pair(), isNil(true), height(0), color(BLACK)
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
	bool isOnLeft(void) { return this == parrent->left; }

	node *uncle(void)
	{
	if (parrent->isNil ||  parrent->parrent->isNil)
		return parrent->isNil ;
	if (parrent->isOnLeft())
		return parrent->parrent->right;
	else
		return parrent->parrent->left;
	}

	node *sibling(void)
	{
		if (parrent->isNil)
			return parrent;
		if (isOnLeft())
			return parrent->right;
		else
			return parrent->left;
	}

	void moveDown(node *nParent)
	{
		if (parrent->isNil == false)
		{
			if (isOnLeft())
				parrent->left = nParent;
			else
				parrent->right = nParent;
		}
		nParent->parrent = parrent;
		parrent = nParent;
	}

	bool hasRedChild() { return (left->color == RED || right->color == RED); }

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

template<typename T, typename M, typename Compare = std::less<T> >
class Tree
{
public:
		typedef node<T, M>								node;
		typedef typename node::key_type					key_type;
		typedef typename node::mapped_type				mapped_type;
		typedef ft::Pair<const key_type, mapped_type>	value_type;		
		typedef size_t									size_type;
		typedef	Compare									key_compare;

		node		*root;
		node		*nil;
		key_compare	_comp;
		size_type	_size;

public:

	Tree(const key_compare& comp = key_compare(), size_type size = 0) : _comp(comp), _size(size)
	{
		nil = make_node();
		nil->left = nil;
		nil->right = nil;
		nil->parrent = nil;
		root = nil;
	}

	~Tree()
	{
		delete_tree(root);
		delete nil;
	}

	Tree(Tree const & other)
	{
		root = nil;
		root = other.clone_tree(other.root, root, nil);
		_size = other._size;
		_comp = other._comp;
	}

	Tree &operator=(Tree &other)
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

	node *make_node(const node node_type = node()) 
	{
		return new node(node_type);
	}

	node *make_node(value_type const &p)
	{
		return new node(p, nil);
	}

	void delete_tree(node *root)
	{
		if (root == nil)
			return ;
		delete_tree(root->left);
		delete_tree(root->right);
		delete root;
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
		return insert_element(ft::make_pair(k, mapped_type()));
	}

	node *insert_element(const value_type& val) // insert pair
	{
		node *new_node;
		node *subtree 	= find(val.first);

		if (subtree->isNil == false && subtree->pair.first == val.first)
			return subtree;
		new_node = make_node(val);
		new_node->color = RED;	
		_size++;
		if (subtree == nil)
			root = new_node;
		else if (_comp(new_node->pair.first, subtree->pair.first))
			subtree_insert_before(subtree, new_node);
		else
			subtree_insert_after(subtree, new_node);
		maintain_balance(new_node);
		return new_node;
	}

	void maintain_balance(node *x)
	{
		node *parrent		= x->parrent;
		node *grand_parrent	= parrent->parrent;
		node *uncle;

		if (grand_parrent->left == parrent)
			uncle = grand_parrent->right;
		else
			uncle = grand_parrent->left;

		if (x == root)
			x->color = BLACK;
		if (parrent->color != BLACK && x != root)
		{
			if (uncle->color == RED)
			{
				parrent->color = BLACK;
				uncle->color = BLACK;
				if (grand_parrent->isNil == false)
					grand_parrent->color = RED;
				maintain_balance(grand_parrent);
			}
			else if (uncle->color == BLACK)
				rotate(parrent);
		}
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
		// update_subtree_props(x);
	}


	void rotate(node *y) // parrent 
	{
		node	*x;
		node	*parrent_tmp = y->parrent;

		if (y->left->height > y->right->height)
			x = y->left;
		else
			x = y->right;
		if (x->isNil || y->isNil)
			return ;
		if (y->parrent->left == y && x == y->left)  // left left case
		{
			right_rotate(parrent_tmp);
			std::swap(parrent_tmp->color, y->color);
		}
		else if (y->parrent->left == y && x == y->right) // left right case
		{
			left_rotate(y);
			right_rotate(parrent_tmp);
			std::swap(parrent_tmp->color, y->color);
		}
		else if (y == y->parrent->right && x == y->right) // right right case
		{
			left_rotate(parrent_tmp);
			std::swap(parrent_tmp->color, y->color);
		}
		else if (y == y->parrent->right && x == y->left) // right left case
		{
			right_rotate(y);
			left_rotate(parrent_tmp);
			std::swap(parrent_tmp->color, y->color);
		}
	}

	node* subtree_insert_after(node* subtree, node *new_el)
	{
		new_el->parrent = subtree;

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
			new_el->parrent = subtree;
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

	// initialize parrent, grandparent, uncle
		node *parrent = x->parrent, *grandparent = parrent->parrent,
			*uncle = x->uncle();

		if (parrent->color != BLACK)
		{
			if (uncle->isNil == false && uncle->color == RED)
			{ // uncle red, perform recoloring and recurse
				parrent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				fixRedRed(grandparent);
			} else
			{ // Else perform LR, LL, RL, RR
				if (parrent->isOnLeft())
				{
					if (x->isOnLeft())
					{ // for left right
						swapColors(parrent, grandparent);
					}
					else
					{
						left_rotate(parrent);
						swapColors(x, grandparent);
					}
					// for left left and left right
					right_rotate(grandparent);
					} else {
				if (x->isOnLeft())
				{ // for right left
					right_rotate(parrent);
					swapColors(x, grandparent);
				}
				else
					swapColors(parrent, grandparent);
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
		node *parrent = v->parrent;

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
				parrent->left = nil;
			else
				parrent->right = nil;
			}
			delete v;
			return;
		}
		if (v->left->isNil || v->right->isNil)
		{	// v has 1 child
			if (v == root)
			{	// v is root, assign the u to root and delete v
				root = u;
				u->left = u->right = u->parrent = nil;
				delete v;
			}
			else
			{	// Detach v from tree and move u up
				if (v->isOnLeft())
					parrent->left = u;
				else
					parrent->right = u;
				delete v;
				u->parrent = parrent;
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
		node * successor_copy = make_node(u);
		successor_copy->right = v->right;
		successor_copy->left = v->left;
		successor_copy->parrent = v->parrent;
		if (v->parrent->isNil == false && v->isOnLeft())
			v->parrent->left = successor_copy;
		else if (v->parrent->isNil == false)
			v->parrent->right = successor_copy;
		if (v->left->isNil == false)
			v->left->parrent = successor_copy;
		if (v->right->isNil == false)
			v->right->parrent = successor_copy;
		if (root == v)
			root = successor_copy;
		delete v;
	}

	void fixDoubleBlack(node *x)
	{
		if (x == root) // Reached root
			return ;

		node *sibling = x->sibling(), *parrent = x->parrent;
		if (sibling->isNil)
		{ // No sibiling, double black pushed up
			fixDoubleBlack(parrent);
		}
		else
		{
			if (sibling->color == RED)
			{	// Sibling red
				parrent->color = RED;
				sibling->color = BLACK;
				if (sibling->isOnLeft()) // left case
					right_rotate(parrent);
				else	// right case
					left_rotate(parrent);
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
							sibling->color = parrent->color;
							right_rotate(parrent);
						}
						else
						{	// right left
							sibling->left->color = parrent->color;
							right_rotate(sibling);
							left_rotate(parrent);
						}
					}
					else
					{
						if (sibling->isOnLeft())
						{	// left right
							sibling->right->color = parrent->color;
							left_rotate(sibling);
							right_rotate(parrent);
						}
						else
						{	// right right
							sibling->right->color = sibling->color;
							sibling->color = parrent->color;
							left_rotate(parrent);
						}
					}
					parrent->color = BLACK;
				}
				else
				{	// 2 black children
					sibling->color = RED;
					if (parrent->color == BLACK)
						fixDoubleBlack(parrent);
					else
						parrent->color = BLACK;
				}
			}
		}
	}


};




#endif // !RBTREE