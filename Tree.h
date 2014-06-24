/*
 * Tree.h
 *
 *  Created on: Jun 23, 2014
 *      Author: nicolas
 */

#ifndef TREE_H_
#define TREE_H_

#include <sstream>
#include <time.h>
#include <ctime>
#include <sys/time.h>

#include "CEP.h"

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

class Tree {
public:

	virtual ~Tree() = 0;

	virtual void insert(CEP data) = 0;

	virtual void remove(CEP key) = 0;

};

#endif /* TREE_H_ */
