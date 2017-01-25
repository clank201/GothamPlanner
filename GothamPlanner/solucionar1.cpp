#include "solucionar1.h"

bool solucionar1::solucionar(const solucio1 &inicial) {
	// pre: cert
	// pos: retorna si ha trobat o no la solucio (i la guarda si l’ha trobada)
	encertat = false;
	sol = inicial;
	trobarUnaSolucio();
	return encertat;
}
solucio1 solucionar1::obtenirSolucio() const {
	// pre: cal haver exacutat solucionar
	// pos: retorna una copia de la solucio si s’ha trobat
	if (!encertat)
		throw("No s’ha trobat la solució");
	return sol;
}
void solucionar1::trobarUnaSolucio() {
	// pre: no encertat ^ sol és parcial
	// pos: no encertat o encertat ^ sol és completa
	candidats1 iCan = sol.inicialitzarCandidats();
	while (!iCan.esFi() && !encertat) {
		if (sol.acceptable(iCan)) {
			sol.anotar(iCan);
			if (!sol.completa()) {
				trobarUnaSolucio();
				if (!encertat)
					sol.desanotar(iCan);
			}
			else encertat = true;
		}
		iCan.seguent();
	}
}