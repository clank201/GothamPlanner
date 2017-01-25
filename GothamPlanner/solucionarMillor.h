#pragma once
#include "solucioGotham1.h"

class solucionarMillor {
public:
	solucioGotham1 solucionar(const solucioGotham1 &inicial);
private:
	void trobarMillor(solucioGotham1 &actual);
	// inv: optima cont� la millor motxilla trobada
	solucioGotham1 optima;
};
