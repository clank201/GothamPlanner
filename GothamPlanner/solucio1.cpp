#include "solucio1.h"
#include <iostream>
#include <string>

solucio1::solucio1() {
	tamany = 0;
	distMax = 0;
	perillMax = 0;
	objectiu = 0;
	perillAcum = 0;
}

solucio1::solucio1(GrafEtiquetatVMap* graf, int d, double p, int o, int origen) {
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
solucio1::solucio1(const solucio1 &o) {
	// pre: cert (error: bad alloc)
	// pos: es fa un duplicat de l’objecte o
	copia(o);
}
solucio1::~solucio1() {
	// pre: cert
	// pos: s’allibera la memòria de l’objecte
	allibera();
}
solucio1 & solucio1::operator=(const solucio1 &o) {
	// pre: cert (error: bad alloc)
	// pos: es fa un duplicat de l’objecte o i es retorna
	if (this != &o) {
		allibera();
		copia(o);
	}
	return *this;
}
candidats1 solucio1::inicialitzarCandidats() const {
	// pre: cert
	// pos: retorna els candidats del nivell actual
	return candidats1(tamany + 1);
}
bool solucio1::acceptable(const candidats1 &iCan) const {
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
void solucio1::anotar(const candidats1 &iCan) {
	// pre: iCan és acceptable
	// pos: afegeix iCan a la solucio
	int f = iCan.actual();
	etiqueta e = g->EtiquetaAresta(recorregut.back(), f);
	distAcum += e.dist;
	if (recorregut.size()==2)perillAcum = e.perill;
	else perillAcum = 1 - ((1 - perillAcum) * (1 - e.perill));
	recorregut.push_back(f);
}
void solucio1::desanotar(const candidats1 &iCan) {
	// pre: iCan és el darrer candidat anotat
	// pos: es treu iCan de la solucio (darrer candidat anotat)
	int f = iCan.actual();
	recorregut.pop_back();
	etiqueta e = g->EtiquetaAresta(recorregut.back(), f);
	distAcum -= e.dist;
	if (recorregut.size() == 2)perillAcum = 0;
	else perillAcum = 1 - ((1 - perillAcum) / (1 - e.perill));
}
bool solucio1::completa() const {
	// pre: cert
	// pos: retorna cert si la solució ja és completa
	return recorregut.back() == objectiu;
}

void solucio1::mostrar() const {
	cout << "Cerquem un cami amb probabilitat atemptat en un tram < que cert valor" << endl << "== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == =" << endl;
	cout << "Per anar de " << g->getNomVertex(recorregut[1]) << " a " << g->getNomVertex(recorregut.back()) << " tenim el següent camí: " << endl;
	for (int i = 1; i < recorregut.size(); i++) {
		cout << g->getNomVertex(recorregut[i]);
		if (i + 1 < recorregut.size()) cout << "-";
	}
	cout << endl << "amb una probabilitat de patir un atemptat de " << perillAcum << endl;
	cout << "i amb una distància total de " << (float)distAcum / 1000 << " quilòmetres" << endl;
}

void solucio1::reserva() {
	// pre: nReines inicialitzat (error: bad alloc)
	// pos: es reserva espai per a les diferents taules
}
void solucio1::copia(const solucio1 &o) {
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
void solucio1::allibera() {
	// pre: cert
	// post: s’allibera la memòria reservada
}
