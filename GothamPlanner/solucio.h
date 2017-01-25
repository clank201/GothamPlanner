#pragma once
#include "candidats.h"
#include <vector>
#include "GrafEtiquetatVMap.h"

using namespace std;

class solucio {
public:
	solucio();
	solucio(GrafEtiquetatVMap* graf, int d,int objectiu, int origen, double p = 1);
	solucio(const solucio &o);
	~solucio();
	solucio & operator=(const solucio &o);
	candidats inicialitzarCandidats() const;
	bool acceptable(const candidats &iCan) const;
	void anotar(const candidats &iCan);
	void desanotar(const candidats &iCan);
	bool completa() const;
	void mostrar() const;
	bool millorQue(solucio sol);
private:
	void reserva();
	void copia(const solucio &o);
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