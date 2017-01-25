#pragma once
#include "solucio1.h"

class solucionar1 {
public:
	bool solucionar(const solucio1 &inicial);
	solucio1 obtenirSolucio() const;
private:
	void trobarUnaSolucio();
	// inv: no encertat o encertat ^ sol completada
	bool encertat;
	solucio1 sol;
};
