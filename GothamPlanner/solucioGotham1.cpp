#include "solucioGotham1.h"



solucioGotham1::solucioGotham1() {
	// pre: -
	// post: solucio buida usada com a valor per defecte
	longitudAcumulada = 0;
	longitudMaxima = 0;
	probMaxima = 0;
}
solucioGotham1::solucioGotham1(const std::vector<int> &v, double pMax, int dMax) {
	// pre: pMax>0 ^ v esta ordenat per benefici/pes (posicio 0: sentinella)
	// post: solucio preparada per poder resoldre el problema amb les dades donades
	cami = v;
	reserva();
	longitudAcumulada = 0;
	longitudMaxima = dMax;
	probMaxima = pMax;	
}
solucioGotham1::solucioGotham1(const solucioGotham1 &o) {
	// pre: cert (error: bad alloc)
	// post: es fa un duplicat de l’objecte o
	copia(o);
}
solucioGotham1::~solucioGotham1() {
	// pre: cert
	// pos: s’allibera la memòria de l’objecte
	allibera();
}
solucioGotham1 & solucioGotham1::operator=(const solucioGotham1 &o) {
	// pre: cert (error: bad alloc)
	// post: es fa un duplicat de l’objecte o i es retorna
	if (this != &o) {
		allibera();
		copia(o);
	}
	return *this;
}
candidatsGotham1 solucioGotham1::inicialitzarCandidats() const {
	// pre: cert
	// post: es retorna el cj. de candidats del nivell
	return candidatsGotham1(agafats[niv], nObjs);
}
bool solucioGotham1::acceptable(const candidatsGotham1 &iCan) const {
	// pre: cert
	// post: retorna cert si el candidat es pot afegir a la solució
	return(pes + objs[iCan.actual()].pes() <= pesMaxim);
}
void solucioGotham1::anotar(const candidatsGotham1 &iCan) {
	// pre: iCan és acceptable
	// pos: afegeix iCan a la solucio
	niv++;
	agafats[niv] = iCan.actual();
	pes = pes + objs[iCan.actual()].pes();
	benefici = benefici + objs[iCan.actual()].benefici();
}
void solucioGotham1::desanotar(const candidatsGotham1 &iCan) {
	// pre: iCan és el darrer candidat anotat
	// pos: es treu iCan de la solucio (darrer candidat anotat)
	agafats[niv] = 0;
	pes = pes - objs[iCan.actual()].pes();
	benefici = benefici - objs[iCan.actual()].benefici();
	niv--;
}
bool solucioGotham1::completa() const {
	// pre: cert
	// pos: retorna cert si la solució ja és completa
	return true; // no es fa servir
}
bool solucioGotham1::posSerMillor(const solucioGotham1 &optima,
	const candidatsGotham1 &iCan) const {
	// pre: optima és un solucio completa ^ iCan és acceptable
	// post: retorna fals si la cota màxima de solucio parcial no pot
	// millorar la òptima
	bool res;
	int j = iCan.actual();
	double aux = (pesMaxim - pes)*objs[j].benefici() / objs[j].pes();
	if (benefici + aux <= optima.benefici)
		res = false; // no és millora la solució òptima
	else {
		int k = j;
		aux = benefici; // caldria tenir-ho precalculat
		while (k <= nObjs && aux<optima.benefici) {
			aux = aux + objs[k].benefici();
			k++;
		}
		res = (aux >= optima.benefici);
	}
	return res;
}
bool solucioGotham1::esMillor(const solucioGotham1 &optima) const {
	// pre: optima és una solucio completa ^ actual també
	// post: retorna cert si és millor actual que òptima
	return benefici > optima.benefici;
}
int solucioGotham1::maxObjects() const {
	// pre: cert
	// post: retorna el n d’objectes que hi ha per posar a la motxilla
	return nObjs;
}
int solucioGotham1::darrerObjecte() const {
	// pre: cert
	// post: retorna el darrer objecte que s’ha posat a la motxilla
	return agafats[niv]; // posicio 0, sentinella
}
void solucioGotham1::reserva() {
	// pre: nObjs inicialitzat (error: bad alloc)
	// post: ha reservar espai per guardar les dades de la solucio
	agafats = new int[nObjs + 1]; // posicio 0: sentinella
}
void solucioGotham1::copia(const solucioGotham1 &o) {
	// pre: cert (error: bad alloc)
	// post: es fa un duplicat dels atributs (estàtics i dinàmics)
	// pendent d’acabar
}
void solucioGotham1::allibera() {
	// pre: cert
	// post: s’allibera la memòria reservada
	delete[] agafats;
}