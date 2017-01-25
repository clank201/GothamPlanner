#include "candidats.h"

candidats::candidats(int n) {
	// pre: n>0
	// pos: s’ha inicialitzat el candidat
	iCan = 1;
	mida = n;
}
int candidats::actual() const {
	// pre: cert (error: no hi ha candidat)
	// post: retorna el candidat actual
	if (esFi())
		throw("No hi ha més candidats");
	return iCan;
}
bool candidats::esFi() const {
	// pre: cert
	// post: retorna cert si ja no queden candidats
	return iCan>mida;
}
void candidats::seguent() {
	// pre: cert (error: no hi ha candidat)
	// post: passa al següent candidat
	if (esFi())
		throw("No hi ha més candidats");
	iCan++;
}