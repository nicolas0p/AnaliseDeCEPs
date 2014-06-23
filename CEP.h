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

	CEP(const CEP& cep) : logradouro(cep.logradouro), cep(cep.cep) {}

};

bool operator>(CEP one, CEP another) {
	return one.cep > another.cep;
}

bool operator<(CEP one, CEP another) {
	return one.cep < another.cep;
}

bool operator==(CEP one, CEP another) {
	return one.cep == another.cep;
}

std::ostream& operator<<(std::ostream& os, const CEP& cep)
{
	os << cep.logradouro;
	return os;
}

#endif /* CEP_H_ */
