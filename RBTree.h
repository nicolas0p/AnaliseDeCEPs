/*
 * RBTree.h
 *
 *  Created on: Jun 22, 2014
 *      Author: nicolas
 */

#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>
#include <sstream>

#include <time.h>
#include <ctime>
#include <sys/time.h>

#include "CEP.h"
#include "RBTreeZuada.h"

using namespace std;

int comp(void* one, void* another) {
	if (*(CEP*) one > *(CEP*) another) {
		return 1;
	}
	if (*(CEP*) one < *(CEP*) another) {
		return -1;
	}
	return 0;
}

timeval presentTime() {
	timeval time;
	gettimeofday(&time, NULL);
	return time;
}

void writeFile(ofstream *file, const string& toWrite) {
	(*file) << toWrite << "\n";
}

long timeDifference(const timeval& begin, const timeval& end) {
	long difference, seconds, milli;

	seconds = end.tv_sec - begin.tv_sec;
	milli = end.tv_usec - begin.tv_usec;

	difference = seconds * 1000000 + milli;
	return difference;
}


class RedBlack {
public:
	RedBlack() :
			creator(), tree(creator.rbtree_create()), size_(0), file(new ofstream("rbtree.txt")), comparator(comp) {
	}

	~RedBlack() {
		file->close();
		delete file;
	}

	void insert(CEP data) {
		++size_;
		CEP *info = new CEP(data);
		timeval begin = presentTime();

		creator.rbtree_insert(tree, (void*) info, (void*) info, comparator);

		timeval end = presentTime();
		long dif = timeDifference(begin, end);
		ostringstream ss;
		ss << size_ << " " << dif;
		writeFile(file, ss.str());
	}

	void remove(CEP key) {
		--size_;
		CEP *info = new CEP(key);
		creator.rbtree_delete(tree, (void*) info, comparator);
	}

	void print() {
		creator.print_tree(tree);
	}

private:
	RBTree creator;
	rbtree tree;
	size_t size_;
	ofstream *file;
	int (*comparator)(void* one, void* another);

};

#endif /* RBTREE_H_ */
