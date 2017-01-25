#include "solucionarOptim.h"

solucio solucionarOptim::solucionar(const solucio &inicial) {
	// pre: cert
	// pos: retorna si ha trobat o no la solucio (i la guarda si l’ha trobada)
	optima = inicial;
	solucio actual = inicial;
	trobarMillor(actual);
	return optima;
}

void solucionarOptim::trobarMillor(solucio & actual) {
	candidats iCan = actual.inicialitzarCandidats();
	while (!iCan.esFi()) {
		if (actual.acceptable(iCan) && actual.millorQue(optima)) {
			actual.anotar(iCan);
			if (!actual.completa()) trobarMillor(actual);
			else if (actual.millorQue(optima)) optima = actual;
			actual.desanotar(iCan);
		}
		iCan.seguent();
	}
}