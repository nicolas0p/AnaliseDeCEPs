/*
 * RBTree.h
 *
 *  Created on: Jun 17, 2014
 *      Author: nicolas
 */

#ifndef RBTREE_H_
#define RBTREE_H_

#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include <iomanip>

enum Color {
	RED, BLACK
};

template<typename T>
class RBTreeImp {

	struct Node {
		Node *left, *right, *parent;
		T data;
		Color color;

		Node(Node *left, Node *right, Node *parent, T data) :
				left(left), right(right), parent(parent), data(data), color(RED) {
		}

		Node* grandparent() {
			assert(this != 0);
			assert(this->parent != 0);
			assert(this->parent->parent != 0);

			return this->parent->parent;
		}

		Node * sibling() {
			assert(this != 0);
			assert(this->parent != 0);
			assert(this->parent->parent != 0);

			if (this == this->parent->left) {
				return this->parent->right;
			} else
				return this->parent->right;
		}

		Node * uncle() {
			assert(this != 0);
			assert(this->parent != 0);
			assert(this->parent->parent != 0);

			return this->parent->sibling();
		}

		void verifyProperty1() {
			if (this == 0)
				return;
			assert(color == RED || color == BLACK);
			left->verifyProperty1();
			right->verifyProperty1();
		}

		void verifyProperty4() {
			if (this == 0)
				return;
			if (color == RED) {
				assert(parent->color == BLACK);
				assert(left->color == BLACK);
				assert(right->color == BLACK);
			}

			left->verifyProperty4();
			right->verifyProperty4();
		}

		void verifyProperty5() {
			int blackCountPath = -1;
			property5Helper(this, 0, &blackCountPath);
		}

		Node* rotateLeft() {
			Node::swap(this, right);
			right = right->left;

			if (right->left != 0) {
				right->left->parent = this;
			}

			right->left = this;
			this->parent = right;

			return this->parent;
		}

		Node* rotateRight() {
			Node::swap(this, left);
			left = left->right;

			if (left->right != 0) {
				left->right->parent = this;
			}

			left->right = this;
			this->parent = left;

			return this->parent;
		}

		static void swap(Node *one, Node *another) {
			swap(one->left, another->left);
			swap(one->right, another->right);
			swap(one->parent, another->parent);
			swap(one->color, another->color);

			T aux = one->data;
			one->data = another->data;
			another->data = aux;
		}

		static void swap(Color& one, Color& another) {
			Color aux = one;
			one = another;
			another = aux;
		}

		void insert(Node* add) {
			if (data > add->data) {
				insertRight(add);
				return;
			} else if (data < add->data) {
				insertLeft(add);
				return;
			}

			delete add; //because it was not inserted
			throw std::out_of_range("Information already in");
		}

		void insertRight(Node *add) {
			if (left == 0) {
				left = add;
				add->parent = this;
			} else
				left->insert(add);
		}

		void insertLeft(Node *add) {
			if (left == 0) {
				left = add;
				add->parent = this;
			} else
				left->insert(add);
		}

		Node* findNode(const T& key) {
			if (key > data) {
				return right->findNode(key);
			} else if (key < data) {
				return left->findNode(key);
			}
			return this;
		}

		Node* maximumNode() {
			assert(this != 0);
			if (right != 0) {
				return right->maximumNode();
			}
			return this;
		}
	};

public:
	RBTreeImp() :
			root(0), size_(0) {
	}

	void insert(const T& toAdd) {
		Node *add = new Node(0, 0, 0, toAdd);
		if (root == 0)
			root = add;
		else
			root->insert(add);

		insertCase1(add);
		verifyProperties();
	}

	void remove(const T& key) {
		Node *del = findNode(key);
		Node *child;

		if (del == 0) {
			return;
		}

		if (del->left != 0 && del->right != 0) {
			Node* predecessor = del->left->maximumNode();
			del->data = predecessor->data;
			del = predecessor;
		}

		assert(del->left == 0 || del->right == 0);
		child = del->right == 0 ? del->left : del->right;

		if (del->color == BLACK) {
			del->color = child->color;
			deleteCase1(del);
		}

		Node::swap(del, child);
		delete del;
		verifyProperties();
	}

	void print() {
		postorder(root, 0);
		puts("");
	}

	std::size_t size() {
		return size_;
	}

private:
	Node *root;
	size_t size_;

	Node* findNode(const T& key) {
		return root->findNode(key);
	}

	void verifyProperties() {
		this->root->verifyProperty1();
		this->verifyProperty2();
		this->root->verifyProperty4();
		this->root->verifyProperty5();
	}

	void verifyProperty2() {
		assert(root->color == BLACK);
	}

	static void property5Helper(Node* node, int black_count, int* pathBlackCount) {

		if (node == 0) {

			if (*pathBlackCount == -1) {
				*pathBlackCount = black_count;
			}

			else {
				assert(black_count == *pathBlackCount);
			}

			return;
		}

		if (node->color == BLACK) {
			black_count++;
		}

		property5Helper(node->left, black_count, pathBlackCount);
		property5Helper(node->right, black_count, pathBlackCount);
	}

	void insertCase1(Node *add) {
		if (add->parent == 0) {
			add->color = BLACK;
		} else {
			insertCase2(add);
		}
	}

	void insertCase2(Node *add) {
		if (add->parent->color == BLACK) {
			return;
		} else {
			insertCase3(add);
		}
	}

	void insertCase3(Node *add) {
		if (add->uncle()->color == RED) {
			add->parent->color = BLACK;
			add->uncle()->color = BLACK;
			add->grandparent()->color = RED;
			insertCase1(add->grandparent());
		} else {
			insertCase4(add);
		}
	}

	void insertCase4(Node *add) {
		if (add == add->parent->right
				&& add->parent == add->grandparent()->left) {
			add->parent->rotateLeft();
			add = add->right;
		} else if (add == add->parent->left
				&& add->parent == add->grandparent()->right) {
			add->parent->rotateRight();
			add = add->right;
		}

		insertCase5(add);
	}

	void insertCase5(Node *add) {
		add->parent->color = BLACK;
		add->grandparent()->color = RED;

		if (add == add->parent->left
				&& add->parent == add->grandparent()->left) {
			add->grandparent()->rotateRight();
		} else {
			assert(
					add == add->parent->right
							&& add->parent == add->grandparent()->right);
			add->grandparent()->rotateRight();
		}
	}

	void deleteCase1(Node* del) {
		if (del->parent == 0) {
			return;
		}

		else
			deleteCase2(del);
	}

	void deleteCase2(Node* del) {
		if (del->sibling()->color == RED) {
			del->parent->color = RED;
			del->sibling()->color = BLACK;

			if (del == del->parent->left) {
				del->parent->rotateLeft();
			}

			else
				del->parent->rotateRight();
		}

		deleteCase3(del);
	}

	void deleteCase3(Node* del) {
		if (del->parent->color == BLACK && del->sibling()->color == BLACK
				&& del->sibling()->left->color == BLACK) {
			del->sibling()->color = RED;
			deleteCase1(del->parent);
		}

		else
			deleteCase4(del);
	}

	void deleteCase4(Node* del) {
		if (del->parent->color == RED && del->sibling()->color == BLACK
				&& del->sibling()->left->color == BLACK
				&& del->sibling()->right->color == BLACK) {
			del->sibling()->color = RED;
			del->parent->color = BLACK;
		}

		else
			deleteCase5(del);
	}

	void deleteCase5(Node* del) {
		if (del == del->parent->left && del->sibling()->color == BLACK
				&& del->sibling()->left->color == RED
				&& del->sibling()->right->color == BLACK) {

			del->sibling()->color = RED;
			del->sibling()->left->color = BLACK;
			del->sibling()->rotateRight();
		}

		else if (del == del->parent->right && del->sibling()->color == BLACK
				&& del->sibling()->right->color == RED
				&& del->sibling()->left->color == BLACK) {

			del->sibling()->color = RED;
			del->sibling()->right->color = BLACK;
			del->sibling()->rotateLeft();
		}

		deleteCase6(del);
	}

	void deleteCase6(Node* del) {
		del->sibling()->color = del->parent->color;
		del->parent->color = BLACK;

		if (del == del->parent->left) {
			assert(del->sibling()->right->color == RED);
			del->sibling()->right->color = BLACK;
			del->parent->rotateLeft();
		}

		else {
			assert(del->sibling()->left->color == RED);
			del->sibling()->left->color = BLACK;
			del->parent->rotateRight();
		}
	}

	void print_tree_helper(Node* n, int indent) {
		int i;

		if (n == 0) {
			fputs("<empty tree>", stdout);
			return;
		}

		if (n->right != 0) {
			print_tree_helper(n->right, indent + 4);
		}

		for (i = 0; i < indent; i++)
			fputs(" ", stdout);

		if (n->color == BLACK)
			std::cout << n->data << std::endl;

		else
			std::cout << "<" << n->data << ">" << std::endl;

		if (n->left != 0) {
			print_tree_helper(n->left, indent + 4);
		}
	}

	void postorder(Node* print, int indent = 0) {
		if (print != NULL) {
			if (print->left)
				postorder(print->left, indent + 4);
			if (print->right)
				postorder(print->right, indent + 4);
			if (indent) {
				std::cout << std::setw(indent) << ' ';
			}
			std::cout << print->data << "\n ";
		}
	}
};

#endif /* RBTREE_H_ */
