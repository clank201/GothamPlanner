#include "solucionarMillor.h"
#include "solucioGotham1.h"
#include "candidatsGotham1.h"

solucioGotham1 solucionarMillor::solucionar(const solucioGotham1 &inicial) {
	// pre: motxilla amb uns objectes possibles i un pes màxim
	// post: retorna la millor motxilla trobada que no supera el pes s’agafen els objectes de la motxilla inicial
	solucioGotham1 actual = inicial;
	optima = inicial;
	trobarMillor(actual);
	return optima;
}

void solucionarMillor::trobarMillor(solucioGotham1 &actual) {
	// pre: actual conté la motxilla que s’esta omplint
	// post: s’acaba d’omplir la motxilla de totes les maneres
	// i es guarda la millor opcio
	candidatsGotham1 iCan = actual.inicialitzarCandidats();
	while (!iCan.esFi()) {
		if (actual.acceptable(iCan) && actual.potSerMillor(optima, iCan)) {
			actual.anotar(iCan);
			if (!iCan.esFi())
				trobarMillor(actual);
			if (actual.esMillor(optima))
				optima = actual; // operador d’assignacio
			actual.desanotar(iCan);
		}
		iCan.seguent();
	}
}