/*

 * C++ Program to Implement Red Black Tree

 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <stdint.h>

#define INDENT_STEP  4

using namespace std;

enum color {
	RED, BLACK
};

typedef struct rbtree_node

{
	enum color color;

	void *key;

	void *value;

	rbtree_node *left, *right, *parent;

}*Node;

typedef struct rbtree_t

{

	Node root;

}*rbtree;

class RBTree

{

public:

	typedef int (*compare_func)(void* left, void* right);

	rbtree rbtree_create();

	void* rbtree_lookup(rbtree t, void*, compare_func compare);

	void rbtree_insert(rbtree t, void*, void*, compare_func compare);

	void rbtree_delete(rbtree t, void*, compare_func compare);

	Node grandparent(Node n);

	Node sibling(Node n);

	Node uncle(Node n);

	void verify_properties(rbtree t);

	void verify_property_1(Node root);

	void verify_property_2(Node root);

	color node_color(Node n);

	void verify_property_4(Node root);

	void verify_property_5(Node root);

	void verify_property_5_helper(Node n, int, int*);

	Node new_node(void* key, void*, color, Node, Node);

	Node lookup_node(rbtree t, void*, compare_func compare);

	void rotate_left(rbtree t, Node n);

	void rotate_right(rbtree t, Node n);

	void replace_node(rbtree t, Node oldn, Node newn);

	void insert_case1(rbtree t, Node n);

	void insert_case2(rbtree t, Node n);

	void insert_case3(rbtree t, Node n);

	void insert_case4(rbtree t, Node n);

	void insert_case5(rbtree t, Node n);

	Node maximum_node(Node root);

	void delete_case1(rbtree t, Node n);

	void delete_case2(rbtree t, Node n);

	void delete_case3(rbtree t, Node n);

	void delete_case4(rbtree t, Node n);

	void delete_case5(rbtree t, Node n);

	void delete_case6(rbtree t, Node n);

};

/*

 * Return Grandparent of Node

 */

Node RBTree::grandparent(Node n)

{

	assert(n != NULL);

	assert(n->parent != NULL);

	assert(n->parent->parent != NULL);

	return n->parent->parent;

}

/*

 * Return Sibling of Node

 */

Node RBTree::sibling(Node n)

{

	assert(n != NULL);

	assert(n->parent != NULL);

	if (n == n->parent->left)

		return n->parent->right;

	else

		return n->parent->left;

}

/*

 * Return Uncle of Node

 */

Node RBTree::uncle(Node n)

{

	assert(n != NULL);

	assert(n->parent != NULL);

	assert(n->parent->parent != NULL);

	return sibling(n->parent);

}

/*

 * Verifying Properties of Red black Tree

 */

void RBTree::verify_properties(rbtree t)

{

	verify_property_1(t->root);

	verify_property_2(t->root);

	verify_property_4(t->root);

	verify_property_5(t->root);

}

/*

 * Verifying Property 1

 */

void RBTree::verify_property_1(Node n)

{

	assert(node_color(n) == RED || node_color(n) == BLACK);

	if (n == NULL)

		return;

	verify_property_1(n->left);

	verify_property_1(n->right);

}

/*

 * Verifying Property 2

 */

void RBTree::verify_property_2(Node root)

{

	assert(node_color(root) == BLACK);

}

/*

 * Returns color of a node

 */

color RBTree::node_color(Node n)

{

	return n == NULL ? BLACK : n->color;

}

/*

 * Verifying Property 4

 */

void RBTree::verify_property_4(Node n)

{

	if (node_color(n) == RED)

	{

		assert(node_color(n->left) == BLACK);

		assert(node_color(n->right) == BLACK);

		assert(node_color(n->parent) == BLACK);

	}

	if (n == NULL)

		return;

	verify_property_4(n->left);

	verify_property_4(n->right);

}

/*

 * Verifying Property 5

 */

void RBTree::verify_property_5(Node root)

{

	int black_count_path = -1;

	verify_property_5_helper(root, 0, &black_count_path);

}

void RBTree::verify_property_5_helper(Node n, int black_count,
		int* path_black_count)

		{

	if (node_color(n) == BLACK)

	{

		black_count++;

	}

	if (n == NULL)

	{

		if (*path_black_count == -1)

		{

			*path_black_count = black_count;

		}

		else

		{

			assert(black_count == *path_black_count);

		}

		return;

	}

	verify_property_5_helper(n->left, black_count, path_black_count);

	verify_property_5_helper(n->right, black_count, path_black_count);

}

/*

 * Create Red Black Tree

 */

rbtree RBTree::rbtree_create()

{

	rbtree t = new rbtree_t;

	t->root = NULL;

	verify_properties(t);

	return t;

}

/*

 * Creating New Node of Reb Black Tree

 */

Node RBTree::new_node(void* k, void* v, color n_color, Node left, Node right)

{

	Node result = new rbtree_node;

	result->key = k;

	result->value = v;

	result->color = n_color;

	result->left = left;

	result->right = right;

	if (left != NULL)

		left->parent = result;

	if (right != NULL)

		right->parent = result;

	result->parent = NULL;

	return result;

}

/*

 * Look Up through Node

 */

Node RBTree::lookup_node(rbtree t, void* key, compare_func compare)

{

	Node n = t->root;

	while (n != NULL)

	{

		int comp_result = compare(key, n->key);

		if (comp_result == 0)

		{

			return n;

		}

		else if (comp_result < 0)

		{

			n = n->left;

		}

		else

		{

			assert(comp_result > 0);

			n = n->right;

		}

	}

	return n;

}

/*

 * RbTree Look Up

 */

void* RBTree::rbtree_lookup(rbtree t, void* key, compare_func compare)

{

	Node n = lookup_node(t, key, compare);

	return n == NULL ? NULL : n->value;

}

/*

 * Rotate left

 */

void RBTree::rotate_left(rbtree t, Node n)

{

	Node r = n->right;

	replace_node(t, n, r);

	n->right = r->left;

	if (r->left != NULL)

	{

		r->left->parent = n;

	}

	r->left = n;

	n->parent = r;

}

/*

 * Rotate right

 */

void RBTree::rotate_right(rbtree t, Node n)

{

	Node L = n->left;

	replace_node(t, n, L);

	n->left = L->right;

	if (L->right != NULL)

	{

		L->right->parent = n;

	}

	L->right = n;

	n->parent = L;

}

/*

 * Replace a node

 */

void RBTree::replace_node(rbtree t, Node oldn, Node newn)

{

	if (oldn->parent == NULL)

	{

		t->root = newn;

	}

	else

	{

		if (oldn == oldn->parent->left)

			oldn->parent->left = newn;

		else

			oldn->parent->right = newn;

	}

	if (newn != NULL)

	{

		newn->parent = oldn->parent;

	}

}

/*

 * Insert node into RBTree

 */

void RBTree::rbtree_insert(rbtree t, void* key, void* value,
		compare_func compare)

		{

	Node inserted_node = new_node(key, value, RED, NULL, NULL);

	if (t->root == NULL)

	{

		t->root = inserted_node;

	}

	else

	{

		Node n = t->root;

		while (1)

		{

			int comp_result = compare(key, n->key);

			if (comp_result == 0)

			{

				n->value = value;

				return;

			}

			else if (comp_result < 0)

			{

				if (n->left == NULL)

				{

					n->left = inserted_node;

					break;

				}

				else

				{

					n = n->left;

				}

			}

			else

			{

				assert(comp_result > 0);

				if (n->right == NULL)

				{

					n->right = inserted_node;

					break;

				}

				else

				{

					n = n->right;

				}

			}

		}

		inserted_node->parent = n;

	}

	insert_case1(t, inserted_node);

	verify_properties(t);

}

/*

 * Inserting Case 1

 */

void RBTree::insert_case1(rbtree t, Node n)

{

	if (n->parent == NULL)

		n->color = BLACK;

	else

		insert_case2(t, n);

}

/*

 * Inserting Case 2

 */

void RBTree::insert_case2(rbtree t, Node n)

{

	if (node_color(n->parent) == BLACK)

		return;

	else

		insert_case3(t, n);

}

/*

 * Inserting Case 3

 */

void RBTree::insert_case3(rbtree t, Node n)

{

	if (node_color(uncle(n)) == RED)

	{

		n->parent->color = BLACK;

		uncle(n)->color = BLACK;

		grandparent(n)->color = RED;

		insert_case1(t, grandparent(n));

	}

	else

	{

		insert_case4(t, n);

	}

}

/*

 * Inserting Case 4

 */

void RBTree::insert_case4(rbtree t, Node n)

{

	if (n == n->parent->right && n->parent == grandparent(n)->left)

	{

		rotate_left(t, n->parent);

		n = n->left;

	}

	else if (n == n->parent->left && n->parent == grandparent(n)->right)

	{

		rotate_right(t, n->parent);

		n = n->right;

	}

	insert_case5(t, n);

}

/*

 * Inserting Case 5

 */

void RBTree::insert_case5(rbtree t, Node n)

{

	n->parent->color = BLACK;

	grandparent(n)->color = RED;

	if (n == n->parent->left && n->parent == grandparent(n)->left)

	{

		rotate_right(t, grandparent(n));

	}

	else

	{

		assert(n == n->parent->right && n->parent == grandparent(n)->right);

		rotate_left(t, grandparent(n));

	}

}

/*

 * Delete Node from RBTree

 */

void RBTree::rbtree_delete(rbtree t, void* key, compare_func compare)

{

	Node child;

	Node n = lookup_node(t, key, compare);

	if (n == NULL)

		return;

	if (n->left != NULL && n->right != NULL)

	{

		Node pred = maximum_node(n->left);

		n->key = pred->key;

		n->value = pred->value;

		n = pred;

	}

	assert(n->left == NULL || n->right == NULL);

	child = n->right == NULL ? n->left : n->right;

	if (node_color(n) == BLACK)

	{

		n->color = node_color(child);

		delete_case1(t, n);

	}

	replace_node(t, n, child);

	free(n);

	verify_properties(t);

}

/*

 * Returns Maximum node

 */

Node RBTree::maximum_node(Node n)

{

	assert(n != NULL);

	while (n->right != NULL)

	{

		n = n->right;

	}

	return n;

}

/*

 * Deleting Case 1

 */

void RBTree::delete_case1(rbtree t, Node n)

{

	if (n->parent == NULL)

		return;

	else

		delete_case2(t, n);

}

/*

 * Deleting Case 2

 */

void RBTree::delete_case2(rbtree t, Node n)

{

	if (node_color(sibling(n)) == RED)

	{

		n->parent->color = RED;

		sibling(n)->color = BLACK;

		if (n == n->parent->left)

			rotate_left(t, n->parent);

		else

			rotate_right(t, n->parent);

	}

	delete_case3(t, n);

}

/*

 * Deleting Case 3

 */

void RBTree::delete_case3(rbtree t, Node n)

{

	if (node_color(n->parent) == BLACK && node_color(sibling(n)) == BLACK &&

	node_color(sibling(n)->left) == BLACK
			&& node_color(sibling(n)->right) == BLACK)

			{

		sibling(n)->color = RED;

		delete_case1(t, n->parent);

	}

	else

		delete_case4(t, n);

}

/*

 * Deleting Case 4

 */

void RBTree::delete_case4(rbtree t, Node n)

{

	if (node_color(n->parent) == RED && node_color(sibling(n)) == BLACK &&

	node_color(sibling(n)->left) == BLACK
			&& node_color(sibling(n)->right) == BLACK)

			{

		sibling(n)->color = RED;

		n->parent->color = BLACK;

	}

	else

		delete_case5(t, n);

}

/*

 * Deleting Case 5

 */

void RBTree::delete_case5(rbtree t, Node n)

{

	if (n == n->parent->left && node_color(sibling(n)) == BLACK &&

	node_color(sibling(n)->left) == RED
			&& node_color(sibling(n)->right) == BLACK)

			{

		sibling(n)->color = RED;

		sibling(n)->left->color = BLACK;

		rotate_right(t, sibling(n));

	}

	else if (n == n->parent->right && node_color(sibling(n)) == BLACK &&

	node_color(sibling(n)->right) == RED
			&& node_color(sibling(n)->left) == BLACK)

			{

		sibling(n)->color = RED;

		sibling(n)->right->color = BLACK;

		rotate_left(t, sibling(n));

	}

	delete_case6(t, n);

}

/*

 * Deleting Case 6

 */

void RBTree::delete_case6(rbtree t, Node n)

{

	sibling(n)->color = node_color(n->parent);

	n->parent->color = BLACK;

	if (n == n->parent->left)

	{

		assert(node_color(sibling(n)->right) == RED);

		sibling(n)->right->color = BLACK;

		rotate_left(t, n->parent);

	}

	else

	{

		assert(node_color(sibling(n)->left) == RED);

		sibling(n)->left->color = BLACK;

		rotate_right(t, n->parent);

	}

}

/*

 * Compare two nodes

 */

int compare_int(void* leftp, void* rightp)

{

	int left = (intptr_t) leftp;

	int right = (intptr_t) rightp;

	if (left < right)

		return -1;

	else if (left > right)

		return 1;

	else

	{

		assert(left == right);

		return 0;

	}

}
