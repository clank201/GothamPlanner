#include "candidatsGotham1.h"

candidatsGotham1::candidatsGotham1(int ant, int max) {
	// pre: ant≥0 ^ max>0
	// post: s’ha inicialitzat el candidat
	iCan = ant + 1;
	nObjs = max;
}
int candidatsGotham1::actual() const {
	// pre: cert (error: no hi ha candidat)
	// post: retorna el candidat actual
	if (esFi())
		throw("No hi ha més candidats"); // excepcio
	return iCan;
}
bool candidatsGotham1::esFi() const {
	// pre: cert
	// post: retorna cert si ja no queden candidats
	return iCan>nObjs;
}
void candidatsGotham1::seguent() {
	// pre: cert (error: no hi ha candidat)
	// post: passa al següent candidat
	if (esFi())
		throw("No hi ha més candidats"); // excepcio
	iCan++;
}