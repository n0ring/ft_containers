#ifndef BINARY_TREE
#define BINARY_TREE

#include "pair.hpp"


template<typename Key, typename Value>
struct node
{
		typedef Key								key_type;
		typedef Value							mapped_type;
		typedef	node<key_type, mapped_type>		node_type;
		typedef ft::Pair<key_type, mapped_type> pair_type;		
		typedef pair_type&						reference_type;		
		typedef pair_type*						pointer;		
		
		// key_type	key;
		// mapped_type	value;
		node_type	*left;
		node_type	*right;
		node_type	*parrent;
		pair_type	pair;
		bool		isNil;
	
	// node(node *nil) :  left(nil), right(nil), parrent(nil), pair(), isNil(false)
	// {
	// }

	node(node const *other) :  left(other->left), right(other->right),
		parrent(other->right), pair(other->pair), isNil(false)
	{
	}

	node(pair_type const &p, node *nil) :  left(nil), right(nil),
		parrent(nil), pair(p), isNil(false)
	{
	}
	
	node(void) :  left(NULL), right(NULL), parrent(NULL), pair(), isNil(true)
	{
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

	node *precessor()
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
		return (a->pair.first == b->pair.first);
	}

	template<typename Key, typename Value>
	bool operator<(node<Key, Value> &a, node<Key, Value> &b)
	{
		return (a.pair.first < b.pair.first);
	}

template<typename T, typename M>
class Btree
{
public:
		typedef node<T, M>					node;
		typedef typename node::key_type		key_type;
		typedef typename node::mapped_type	mapped_type;
		typedef ft::Pair<const key_type, mapped_type> pair_type;		

		node *root;
		node *nil;

public:

	Btree(void)
	{
		nil = new node();
		nil->left = nil;
		nil->right = nil;
		nil->parrent = nil;
		root = nil;
	}

	~Btree()
	{
		delete_tree(root);
		delete nil;
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
			prec = subtree->precessor();
			prec->right = new_el;
			new_el = prec;
		}
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
			delete el;
		}
		// case 2: two child
		else if (el->right->isNil == false && el->left->isNil == false)
		{
			node * successor = el->successor();
			node * successor_copy = new node(successor);
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
			delete el;
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
			delete el;
		}
	}
};



#endif // !RBTREE