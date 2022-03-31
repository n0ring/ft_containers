#ifndef RBTREE
#define RBTREE


#define RED		1
#define BLACK	0


template<typename Key, typename Value>
class node
{
	public:
		typedef Key							key_type;
		typedef Value						mapped_type;
		typedef	node<key_type, mapped_type>	node_type;
		
		
		key_type	key;
		mapped_type	value;
		node_type	*left;
		node_type	*right;
		node_type	*parrent;
		char		color;
	
	node(void) :  left(NULL), right(NULL), parrent(NULL), color(BLACK)
	{
	}
			
	node(key_type key, mapped_type value) : key(key), value(value),
		left(NULL), right(NULL), parrent(NULL), color(BLACK)
	{
	}
	~node(void) {}

};

template<typename T, typename M>
class RBtree
{


public:
		typedef node<T, M>					node;
		typedef typename node::key_type		key_type;
		typedef typename node::mapped_type	mapped_type;

	node *root;
	node *nil;

public:

	RBtree(void)
	{
		nil = new node();
		nil->color = BLACK;
		root = nil;
	}


	~RBtree() { delete nil; };

	void left_rotate(node *x)
	{
		if (x->right == nil)
		{
			std::cout << "left rotate error" << std::endl;
			return ;
		}
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
		{
			std::cout << "right rotate error" << std::endl;
			return ;
		}
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
	}

	void insert_fixup(node *new_el)
	{
		node *y;
		while (new_el->parrent && new_el->parrent->color == RED)
		{
			if (new_el->parrent->parrent && new_el->parrent == new_el->parrent->parrent->left)
			{
				y = new_el->parrent->parrent->right;
				if (y->color == RED)
				{
					new_el->parrent->color = BLACK;
					y->color = BLACK;
					new_el->parrent->parrent->color = RED;
					new_el = new_el->parrent->parrent;
				}
				else if (new_el == new_el->parrent->right)
				{
					new_el = new_el->parrent;
					left_rotate(new_el);
				}
				new_el->parrent->color = BLACK;
				new_el->parrent->parrent->color = RED;
				right_rotate(new_el);
			}
			else if (new_el->parrent->parrent)
			{
				y = new_el->parrent->parrent->left; // what if p-p-left == null??
				if (y->color == RED)
				{
					new_el->parrent->color = BLACK;
					y->color = BLACK;
					new_el->parrent->parrent->color = RED;
					new_el = new_el->parrent->parrent;
				}
				else if (new_el == new_el->parrent->left)
				{
					new_el = new_el->parrent;
					right_rotate(new_el);
				}
				new_el->parrent->color = BLACK;
				if (new_el->parrent->parrent)
					new_el->parrent->parrent->color = RED;
				left_rotate(new_el);
			}
		}
		root->color = BLACK;
	}

	void insert_element(node *new_el)
	{
		node *tmp_p = nil;
		node *tmp = root;
		new_el->parrent = nil;

		while (tmp != nil)
		{
			if (tmp->key == new_el->key)
			{
				std::cout << "element with key " << tmp->key << " alreadyin tree" << std::endl;
				return ;
			}
			tmp_p = tmp;
			if (new_el->key < tmp->key)
				tmp = tmp->left;
			else 
				tmp = tmp->right;
		}
		new_el->parrent = tmp_p;
		if (tmp_p == nil)
		{
			root = new_el;
		}
		else if (new_el->key < tmp_p->key)
			tmp_p->left = new_el;
		else
			tmp_p->right = new_el;
		new_el->right = nil;
		new_el->left = nil;
		new_el->color = RED;
		insert_fixup(new_el);
	}

	node *get_root() { return root; }


	void show_tree(node *root, int level)
	{
		if (root == nil)
		{
			return ;
		}
		level++;
		show_tree(root->left, level);
		show_tree(root->right, level);
		std::cout << root->key << (root->color == BLACK ? " BLACK" : " RED") << " lvl " << level  << std::endl;
	}

};



#endif // !RBTREE