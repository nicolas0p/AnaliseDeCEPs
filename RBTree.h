/*
 * RBTree.h
 *
 *  Created on: Jun 17, 2014
 *      Author: nicolas
 */

#include <vector>


template<typename T>
class RBTree {

public:
	RBTree() : vec() {
	}

	void insert(const T& toAdd) {
		vec.push_back(toAdd);
	}
	void remove(const T& key) {
		vec.erase(key);
	}

	std::size_t size() {
		return vec.size();
	}

	std::vector<T>& vector() {
		return vec;
	}

private:
	std::vector<T> vec;
};
