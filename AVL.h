/*
 * AVL.h
 *
 *  Created on: Jun 23, 2014
 *      Author: nicolas
 */

#ifndef AVL_H_
#define AVL_H_


#include "Tree.h"

#include "AVLTree.h"

using namespace std;

class AVL : public Tree {
public:
	AVL() :
			tree(), root(0), size_(0), file(new ofstream("avltree.txt")), comparator(comp) {
	}

	~AVL() {
		file->close();
		delete file;
	}

	void insert(CEP data) {
		++size_;
		timeval begin = presentTime();

		root = tree.insert(root, data.cep);

		timeval end = presentTime();
		long dif = timeDifference(begin, end);
		ostringstream ss;
		ss << size_ << " " << dif;
		writeFile(file, ss.str());
	}

	void remove(CEP key) {
		--size_;
		//CEP *info = new CEP(key);
		//tree.delete(tree, (void*) info, comparator);
	}

private:
	AVLTree tree;
	avlnode *root;
	size_t size_;
	ofstream *file;
	int (*comparator)(void* one, void* another);

};



#endif /* AVL_H_ */
