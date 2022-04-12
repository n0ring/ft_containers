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
		node_type	*parent;
		char		color;
	
	node(void) :  left(NULL), right(NULL), parent(NULL), color(BLACK)
	{
	}
			
	node(key_type key, mapped_type value) : key(key), value(value),
		left(NULL), right(NULL), parent(NULL), color(BLACK)
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
		{
			std::cout << "right rotate error" << std::endl;
			return ;
		}
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
	}

	void insert_fixup(node *new_el)
	{
		node *y;
		while (new_el->parent && new_el->parent->color == RED)
		{
			if (new_el->parent->parent && new_el->parent == new_el->parent->parent->left)
			{
				y = new_el->parent->parent->right;
				if (y->color == RED)
				{
					new_el->parent->color = BLACK;
					y->color = BLACK;
					new_el->parent->parent->color = RED;
					new_el = new_el->parent->parent;
				}
				else if (new_el == new_el->parent->right)
				{
					new_el = new_el->parent;
					left_rotate(new_el);
				}
				new_el->parent->color = BLACK;
				new_el->parent->parent->color = RED;
				right_rotate(new_el);
			}
			else if (new_el->parent->parent)
			{
				y = new_el->parent->parent->left; // what if p-p-left == null??
				if (y->color == RED)
				{
					new_el->parent->color = BLACK;
					y->color = BLACK;
					new_el->parent->parent->color = RED;
					new_el = new_el->parent->parent;
				}
				else if (new_el == new_el->parent->left)
				{
					new_el = new_el->parent;
					right_rotate(new_el);
				}
				new_el->parent->color = BLACK;
				if (new_el->parent->parent)
					new_el->parent->parent->color = RED;
				left_rotate(new_el);
			}
		}
		root->color = BLACK;
	}

	void insert_element(node *new_el)
	{
		node *tmp_p = nil;
		node *tmp = root;
		new_el->parent = nil;

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
		new_el->parent = tmp_p;
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