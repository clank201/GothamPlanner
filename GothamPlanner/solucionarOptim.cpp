#include "solucionarOptim.h"

bool solucionarOptim::solucionar(const solucio &inicial) {
	// pre: cert
	// pos: retorna si ha trobat o no la solucio (i la guarda si l’ha trobada)
	encertat = false;
	buida = true;
	sol = inicial;
	trobarUnaSolucio();
	return encertat;
}
solucio solucionarOptim::obtenirSolucio() const {
	// pre: cal haver exacutat solucionar
	// pos: retorna una copia de la solucio si s’ha trobat
	if (!encertat)
		throw("No s’ha trobat la solució");
	return sol;
}
void solucionarOptim::trobarUnaSolucio() {
	// pre: no encertat ^ sol és parcial
	// pos: no encertat o encertat ^ sol és completa
	candidats iCan = sol.inicialitzarCandidats();
	while (!iCan.esFi()) {
		if (sol.acceptable(iCan)) {
			sol.anotar(iCan);
			if (!sol.completa()) {
				trobarUnaSolucio();
				if (!encertat)
					sol.desanotar(iCan);
			}
			else {
				encertat = true;
				if (buida) optima = sol;
				else if (sol.millorQue(optima))optima = sol;
			}
		}
		iCan.seguent();
	}
}