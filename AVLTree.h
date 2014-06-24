#include<iostream>

#include<cstdio>

#include<sstream>

#include<algorithm>

#define pow2(n) (1 << (n))

using namespace std;

/*
 *
 *      * Node Declaration
 *
 */

struct avlnode

{

	int data;

	struct avlnode *left;

	struct avlnode *right;

}*root;

/*
 *
 *      * Class Declaration
 *
 *           */

class AVLTree

{

public:

	int height(avlnode *);

	int diff(avlnode *);

	avlnode *rr_rotation(avlnode *);

	avlnode *ll_rotation(avlnode *);

	avlnode *lr_rotation(avlnode *);

	avlnode *rl_rotation(avlnode *);

	avlnode* balance(avlnode *);

	avlnode* insert(avlnode *, int);

	AVLTree()

	{

		root = NULL;

	}

};

/*
 *
 *      * Height of AVL Tree
 *
 *           */

int AVLTree::height(avlnode *temp)

{

	int h = 0;

	if (temp != NULL)

	{

		int l_height = height(temp->left);

		int r_height = height(temp->right);

		int max_height = max(l_height, r_height);

		h = max_height + 1;

	}

	return h;

}

/*
 *
 *      * Height Difference 
 *
 *           */

int AVLTree::diff(avlnode *temp)

{

	int l_height = height(temp->left);

	int r_height = height(temp->right);

	int b_factor = l_height - r_height;

	return b_factor;

}

/*
 *
 *      * Right- Right Rotation
 *
 *           */

avlnode *AVLTree::rr_rotation(avlnode *parent)

{

	avlnode *temp;

	temp = parent->right;

	parent->right = temp->left;

	temp->left = parent;

	return temp;

}

/*
 *
 *      * Left- Left Rotation
 *
 *           */

avlnode *AVLTree::ll_rotation(avlnode *parent)

{

	avlnode *temp;

	temp = parent->left;

	parent->left = temp->right;

	temp->right = parent;

	return temp;

}

/*
 *
 *      * Left - Right Rotation
 *
 *           */

avlnode *AVLTree::lr_rotation(avlnode *parent)

{

	avlnode *temp;

	temp = parent->left;

	parent->left = rr_rotation(temp);

	return ll_rotation(parent);

}

/*
 *
 *      * Right- Left Rotation
 *
 *           */

avlnode *AVLTree::rl_rotation(avlnode *parent)

{

	avlnode *temp;

	temp = parent->right;

	parent->right = ll_rotation(temp);

	return rr_rotation(parent);

}

/*
 *
 *      * Balancing AVL Tree
 *
 *           */

avlnode *AVLTree::balance(avlnode *temp)

{

	int bal_factor = diff(temp);

	if (bal_factor > 1)

	{

		if (diff(temp->left) > 0)

			temp = ll_rotation(temp);

		else

			temp = lr_rotation(temp);

	}

	else if (bal_factor < -1)

	{

		if (diff(temp->right) > 0)

			temp = rl_rotation(temp);

		else

			temp = rr_rotation(temp);

	}

	return temp;

}

/*
 *
 *      * Insert Element into the tree
 *
 *           */

avlnode *AVLTree::insert(avlnode *root, int value)

{

	if (root == NULL)

	{

		root = new avlnode;

		root->data = value;

		root->left = NULL;

		root->right = NULL;

		return root;

	}

	else if (value < root->data)

	{

		root->left = insert(root->left, value);

		root = balance(root);

	}

	else if (value >= root->data)

	{

		root->right = insert(root->right, value);

		root = balance(root);

	}

	return root;

}
