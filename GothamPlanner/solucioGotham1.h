#pragma once
#include "candidatsGotham1.h"
#include <vector>

using namespace std;

class solucioGotham1 {
public:
	solucioGotham1();
	solucioGotham1(const std::vector<int> &v, double pMax, int dMax);
	solucioGotham1(const solucioGotham1 &s);
	~solucioGotham1();
	solucioGotham1 & operator=(const solucioGotham1 &s);
	candidatsGotham1 inicialitzarCandidats() const;
	bool acceptable(const candidatsGotham1 &ican) const;
	void anotar(const candidatsGotham1 &ican);
	void desanotar(const candidatsGotham1 &ican);
	bool completa() const;
	bool potSerMillor(const solucioGotham1&, const candidatsGotham1&) const;
	bool esMillor(const solucioGotham1 &opt) const;
	int maxObjectes() const;
	int darrerObjecte() const;
private:
	void reserva();
	void copia(const solucioGotham1 &s);
	void allibera();
	// inv: 0≤pes≤pesMaxim ^ 0≤niv≤objs.size() ^
	// agafats[1..nObjs] ∈ {0.. objs.size()} ^ agafats està ordenat
	vector<int> cami;//int * agafats; // index dels objectes agafats
	//int nObjs; // n.agafats
	int longitudAcumulada;
	int longitudMaxima;
	double probMaxima;
	/*int niv;
	double pesMaxim;
	double pes;
	double benefici;*/
};
