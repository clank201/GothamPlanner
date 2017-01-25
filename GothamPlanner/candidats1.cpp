#include "candidats1.h"

candidats1::candidats1(int n) {
	// pre: n>0
	// pos: s’ha inicialitzat el candidat
	iCan = 1;
	mida = n;
}
int candidats1::actual() const {
	// pre: cert (error: no hi ha candidat)
	// post: retorna el candidat actual
	if (esFi())
		throw("No hi ha més candidats");
	return iCan;
}
bool candidats1::esFi() const {
	// pre: cert
	// post: retorna cert si ja no queden candidats
	return iCan>mida;
}
void candidats1::seguent() {
	// pre: cert (error: no hi ha candidat)
	// post: passa al següent candidat
	if (esFi())
		throw("No hi ha més candidats");
	iCan++;
}