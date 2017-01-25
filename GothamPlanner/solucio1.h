#pragma once
#include "candidats1.h"
#include <vector>
#include "GrafEtiquetatVMap.h"

using namespace std;

class solucio1 {
public:
	solucio1();
	solucio1(GrafEtiquetatVMap* graf, int d, double p,int objectiu, int origen);
	solucio1(const solucio1 &o);
	~solucio1();
	solucio1 & operator=(const solucio1 &o);
	candidats1 inicialitzarCandidats() const;
	bool acceptable(const candidats1 &iCan) const;
	void anotar(const candidats1 &iCan);
	void desanotar(const candidats1 &iCan);
	bool completa() const;
	void mostrar() const;
private:
	void reserva();
	void copia(const solucio1 &o);
	void allibera();
	GrafEtiquetatVMap* g;
	vector<int> recorregut;
	int distAcum;
	int distMax;
	double perillMax;
	int tamany;
	int objectiu;
	double perillAcum;
};