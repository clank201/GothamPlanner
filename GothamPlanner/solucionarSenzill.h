#pragma once
#include "solucio.h"

class solucionarSenzill {
public:
	bool solucionar(const solucio &inicial);
	solucio obtenirSolucio() const;
private:
	void trobarUnaSolucio();
	// inv: no encertat o encertat ^ sol completada
	bool encertat;
	solucio sol;
};
