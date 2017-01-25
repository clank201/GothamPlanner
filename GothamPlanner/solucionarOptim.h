#pragma once
#include "solucio.h"

class solucionarOptim {
public:
	bool solucionar(const solucio &inicial);
	solucio obtenirSolucio() const;
private:
	void trobarUnaSolucio();
	// inv: no encertat o encertat ^ sol completada
	bool encertat;
	solucio sol;
	solucio optima;
	bool buida;
};