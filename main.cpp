/*
 * main.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: nicolas
 */

#include <fstream>
#include <stdlib.h>

#include <iostream>

#include "RBTree.h"
#include "CEP.h"

using namespace std;

CEP createCEP(const string& line) {
	int position = line.find('|');
	string streetName = line.substr(0,position);
	string stringNumber = line.substr(position+1,line.size()-position);
	stringstream ss;
	ss << stringNumber;
	int number;/* = atoi(stringNumber.c_str());*/
	ss >> number;
	return CEP(streetName, number);
}

RedBlack readFile(string fileName) {
	RedBlack tree;
	ifstream file(fileName.c_str());
	string line;
	while( getline(file, line) ){
		tree.insert(createCEP(line));
	}
	file.close();
	return tree;
}

int main() {
	RedBlack tree = readFile("df.txt");
}
