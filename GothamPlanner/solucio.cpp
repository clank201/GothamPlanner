#include "solucio.h"
#include <iostream>
#include <string>

solucio::solucio() {
	tamany = 0;
	distMax = 0;
	perillMax = 0;
	objectiu = 0;
	perillAcum = 0;
}

solucio::solucio(GrafEtiquetatVMap* graf, int d, int o, int origen,double p) {
	// pre: n>0
	// pos: solucio preparada per resoldre un problema de mida n
	tamany = graf->nVertexs();
	g = graf;
	reserva(); // bad_alloc, n+1
	distMax = d;
	perillMax = p;
	distAcum = 0;
	objectiu = o;
	perillAcum = 0;
	recorregut.push_back(0);
	recorregut.push_back(origen);
}
solucio::solucio(const solucio &o) {
	// pre: cert (error: bad alloc)
	// pos: es fa un duplicat de l’objecte o
	copia(o);
}
solucio::~solucio() {
	// pre: cert
	// pos: s’allibera la memòria de l’objecte
	allibera();
}
solucio & solucio::operator=(const solucio &o) {
	// pre: cert (error: bad alloc)
	// pos: es fa un duplicat de l’objecte o i es retorna
	if (this != &o) {
		allibera();
		copia(o);
	}
	return *this;
}
candidats solucio::inicialitzarCandidats() const {
	// pre: cert
	// pos: retorna els candidats del nivell actual
	return candidats(tamany + 1);
}
bool solucio::acceptable(const candidats &iCan) const {
	// pre: cert
	// pos: retorna cert si el candidat es pot afegir a la solució
	int f = iCan.actual();
	if (g->ExisteixAresta(recorregut.back(), f)) {
		if (std::find(recorregut.begin(), recorregut.end(), f) == recorregut.end()) {
			etiqueta t = g->EtiquetaAresta(recorregut.back(), f);
			if (t.perill <= perillMax && (t.dist + distAcum) < distMax) {
				return true;
			}
		}
	}
	return false;
}
void solucio::anotar(const candidats &iCan) {
	// pre: iCan és acceptable
	// pos: afegeix iCan a la solucio
	int f = iCan.actual();
	etiqueta e = g->EtiquetaAresta(recorregut.back(), f);
	distAcum += e.dist;
	if (recorregut.size()==2)perillAcum = e.perill;
	else perillAcum = 1 - ((1 - perillAcum) * (1 - e.perill));
	recorregut.push_back(f);
}
void solucio::desanotar(const candidats &iCan) {
	// pre: iCan és el darrer candidat anotat
	// pos: es treu iCan de la solucio (darrer candidat anotat)
	int f = iCan.actual();
	recorregut.pop_back();
	etiqueta e = g->EtiquetaAresta(recorregut.back(), f);
	distAcum -= e.dist;
	if (recorregut.size() == 2)perillAcum = 0;
	else perillAcum = 1 - ((1 - perillAcum) / (1 - e.perill));
}
bool solucio::completa() const {
	// pre: cert
	// pos: retorna cert si la solució ja és completa
	return recorregut.back() == objectiu;
}

void solucio::mostrar() const {
cout << "Per anar de " << g->getNomVertex(recorregut[1]) << " a " <<g->getNomVertex(objectiu) << " tenim el següent camí: " << endl;
	for (int i = 1; i < recorregut.size(); i++) {
		cout << g->getNomVertex(recorregut[i]);
		if (i + 1 < recorregut.size()) cout << "-";
	}
	cout << endl << "amb una probabilitat de patir un atemptat de " << perillAcum << endl;
	cout << "i amb una distància total de " << (float)distAcum / 1000 << " quilòmetres" << endl;
}

bool solucio::millorQue(solucio sol){
	return perillAcum < sol.perillAcum;
}

void solucio::reserva() {
	// pre: nReines inicialitzat (error: bad alloc)
	// pos: es reserva espai per a les diferents taules
}
void solucio::copia(const solucio &o) {
	// pre: cert (error: bad alloc)
	// post: es fa un duplicat dels atributs (estàtics i dinàmics)
	recorregut = o.recorregut;
	distAcum = o.distAcum;
	distMax = o.distMax;
	perillMax = o.perillMax;
	tamany = o.tamany;
	perillAcum = o.perillAcum;
	objectiu = o.objectiu;
	g = o.g;
}
void solucio::allibera() {
	// pre: cert
	// post: s’allibera la memòria reservada
}
