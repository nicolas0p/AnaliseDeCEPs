/*
 * CEP.h
 *
 *  Created on: Jun 17, 2014
 *      Author: nicolas
 */

#ifndef CEP_H_
#define CEP_H_

#include <string>

struct CEP {
	std::string logradouro;
	int cep;

	CEP(std::string logradouro, int cep) :
			logradouro(logradouro), cep(cep) {
	}
};

#endif /* CEP_H_ */