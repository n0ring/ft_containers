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
		
		// key_type	key;
		// mapped_type	value;
		node_type	*left;
		node_type	*right;
		node_type	*parrent;
		pair_type	pair;
		bool		isNil;
	
	node(node *nil) :  left(nil), right(nil), parrent(nil), pair(), isNil(false)
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
		// delete nil;
	}


	


	node *get_root() { return root; }



	// node *insert_element(pair_type const &new_pair)
	// {
	// 	node	*x = new node(new_pair);
	// 	node	*tmp = root;
	// 	node	*tmp_p = NULL;

	// 	if (root == NULL)
	// 	{
	// 		root = x;
	// 		return (root);
	// 	}
	// 	while (tmp != NULL)
	// 	{
	// 		tmp_p = tmp;
	// 		if (tmp == x)
	// 		{
	// 			std::cout << "element already in tree" << std::endl;
	// 			return NULL;
	// 		}
	// 		if (*x < *tmp)
	// 			tmp = tmp->left;
	// 		else
	// 			tmp = tmp->right;
	// 	}
	// 	x->parrent = tmp_p;
	// 	if (*x < *tmp_p)
	// 		tmp_p->left = x;
	// 	else
	// 		tmp_p->right = x;
	// 	return (x);
	// }

	// void delete_element(key_type key) // instead deleted node insert closest by key
	// {
	// 	node	*tmp = root;
	// 	node	*tmp_p = NULL;
	// 	node	*left_close;
	// 	node	*right_close;


	// 	while (tmp != NULL && key != tmp->pair->first)
	// 	{
	// 		tmp_p = tmp;
	// 		if (key < tmp->pair->first)
	// 			tmp = tmp->left;
	// 		else
	// 			tmp = tmp->right;
	// 	}
	// 	if (tmp == NULL ||  tmp->pair->first != key)
	// 	{
	// 		std::cout << "element is not found" << std::endl;
	// 		return ; 
	// 	}
	// 	if (tmp == root)
	// 	{
	// 		delete tmp;
	// 		root = NULL;
	// 		return ;
	// 	}
	// 	left_close = find_left_closest_node(tmp->left);
	// 	right_close = find_right_closest_node(tmp->right);
	// 	if (right_close == NULL && left_close == NULL)
	// 	{
	// 		if (tmp->parrent->left == tmp)
	// 			tmp->parrent->left = NULL;
	// 		else
	// 			tmp->parrent->right = NULL;
	// 		delete tmp;
	// 		return ;
	// 	}
	// 	if (left_close == NULL)
	// 		return swap_delete_elements(tmp, right_close);
	// 	if (right_close == NULL)
	// 		return swap_delete_elements(tmp, left_close);	
	// 	if (tmp->pair->first - left_close->pair->first < right_close->pair->first - tmp->pair->first)
	// 		swap_delete_elements(tmp, left_close);
	// 	else
	// 		swap_delete_elements(tmp, right_close);
	// }

	// void swap_delete_elements(node *to_del, node *to_swap)
	// {
	// 	if (to_swap->parrent->right == to_swap)
	// 		to_swap->parrent->right = NULL;
	// 	else
	// 		to_swap->parrent->left = NULL;
	// 	to_swap->parrent = to_del->parrent;
	// 	if (to_del->parrent->right == to_del)
	// 		to_del->parrent->right = to_swap;
	// 	else
	// 		to_del->parrent->left = to_swap;
	// 	to_swap->right = to_del->right;
	// 	to_swap->left = to_del->left;
	// 	if (to_swap->right)
	// 		to_swap->right->parrent = to_swap;
	// 	if (to_swap->left)
	// 		to_swap->left->parrent = to_swap;
	// 	delete to_del;
	// }

	// node *find_left_closest_node(node *sub_tree)
	// {
	// 	node *tmp = sub_tree;
	// 	node *tmp_p = NULL;
	// 	while (tmp != NULL)
	// 	{
	// 		tmp_p = tmp;
	// 		tmp = tmp->right;
	// 	}
	// 	return (tmp_p);
	// }

	// node *find_right_closest_node(node *sub_tree)
	// {
	// 	node *tmp = sub_tree;
	// 	node *tmp_p = NULL;
	// 	while (tmp != NULL)
	// 	{
	// 		tmp_p = tmp;
	// 		tmp = tmp->left;
	// 	}
	// 	return (tmp_p);
	// }

	void show_tree(node *root)
	{
		if (root == NULL)
			return ;
		show_tree(root->left);
		std::cout << root->pair->first << std::endl;
		show_tree(root->right);
	}

	// node *begin()
	// {
	// 	node *tmp	= root;

	// 	while (tmp->left != NULL)
	// 		tmp = tmp->left;
	// 	return (tmp);
	// }

	// node *end()
	// {
	// 	return (subtree_last(root));
	// }


	// void iterate()
	// {
	// 	node *tmp = begin();
	// 	node *ite = end();
	// 	for (; tmp != ite; tmp = successor(tmp))
	// 		std::cout << tmp->pair->first << std::endl;
	// 	std::cout << tmp->pair->first << std::endl;
	// }

	// void reverse_iterate(void)
	// {
	// 	node *tmp = end();
	// 	node *ite = begin();
	// 	for (; tmp != ite; tmp = presicessor(tmp) )
	// 		std::cout << tmp->pair->first << std::endl;
	// 	std::cout << tmp->pair->first << std::endl;	
	// }

	// node *subtree_first(node *locale_root)
	// {
	// 	node *tmp = locale_root;
	// 	while (tmp->left != nil)
	// 		tmp = tmp->left;
	// 	return (tmp);
	// }

	// node *subtree_last(node *root)
	// {
	// 	node *tmp = root;
	// 	while (tmp->right != nil)
	// 		tmp = tmp->right;
	// 	return (tmp);
	// }
	
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

		std::cout << el->pair.first << " " << el->right->isNil << std::endl; 
		std::cout << el->successor()->pair.first << " " << el->successor()->right->isNil << std::endl;
		this->swap(el, el->successor());
		std::cout << el->pair.first << " " << el->right->isNil << std::endl; 
		std::cout << el->successor()->pair.first << " " << el->successor()->right->isNil << std::endl;
		// if (el->right == nil && el->left == nil)
		// {
		// 	if (el->parrent && el->parrent->left == el)
		// 		el->parrent->left = nil;
		// 	else if (el->parrent && el->parrent->right == el)
		// 		el->parrent->right = nil;
		// 	if (el->isNil == false)
		// 		delete el;
		// }
		// if (el->left->isNil == false)
		// {
		// 	swap(el, el->precessor());
		// 	subtree_delete(el->precessor());
		// }
		// else if (el->right->isNil == false)
		// {
		// 	swap(el, el->successor());
		// 	subtree_delete(el->successor());		
		// }
	}

	node *find(key_type n)
	{
		node *tmp = root;
		node *tmp_p = nil;
		while (tmp != nil)
		{
			tmp_p = tmp;
			if (tmp->pair.first == n)
				return (tmp);
			if (n < tmp->pair.first)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		return tmp_p;
	}


	void swap(node *a, node *b)
	{
		pair_type tmp(a->pair);
		a->pair = pair_type(b->pair.first, b->pair.second); 
		// a->pair = tmp;
		(void) tmp;
		// std::swap(a, b);
	}
	
};



#endif // !RBTREE