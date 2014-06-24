/*
 * main.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: nicolas
 */

#include <fstream>
#include <stdlib.h>

#include <iostream>

#include "RedBlack.h"
#include "AVL.h"
#include "CEP.h"

using namespace std;

CEP createCEP(const string& line) {
	int position = line.find('|');
	string streetName = line.substr(0, position);
	string stringNumber = line.substr(position + 1, line.size() - position);
	stringstream ss;
	ss << stringNumber;
	int number;
	ss >> number;
	return CEP(streetName, number);
}

void readFile(Tree *tree, string fileName) {
	ifstream file(fileName.c_str());
	string line;
	while (getline(file, line)) {
		tree->insert(createCEP(line));
	}
	file.close();
}

int main() {
	string input;
	int opcao;
	while (true) {
		cout << "Digite 1 para usar a arvore redblack ou 2 para usar a arvore AVL: " << endl;
		getline(cin, input);
		stringstream myStream(input);
		if (myStream >> opcao && opcao > 0 && opcao < 3)
			break;
		cout << "Numero Invalido. Insira 1 ou 2." << endl;
	}
	if (opcao == 1) {
		RedBlack *tree = new RedBlack();
		readFile(tree, "todos.txt");
		std::system("gnuplot fileRB");
	} else {
		AVL *tree = new AVL();
		readFile(tree, "todos.txt");
		std::system("gnuplot fileAVL");
	}
}
