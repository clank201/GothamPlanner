#pragma once
#include <vector>
#include <map>
#include <fstream>	

using namespace std;

struct etiqueta {
	int dist = -1;
	float perill = -1;
};

const int MIDA_DEFECTE = 1000;
class GrafEtiquetatVMap {
public:
	GrafEtiquetatVMap(int nVertexs = MIDA_DEFECTE, bool dirigit = false);
	GrafEtiquetatVMap(const char *nomFitxerTGF, bool dirigit = false);
	int nVertexs() const;
	int nArestes() const;
	bool esDirigit() const;
	void AfegirAresta(int v1, int v2, etiqueta e);
	bool ExisteixAresta(int v1, int v2) const;
	void EsborrarAresta(int v1, int v2);
	bool esValid(int v) const;
	etiqueta EtiquetaAresta(int v1, int v2);
	int getNumeroVertex(string);
	string getNomVertex(int);
private:
	int _nVertexs; // = _arestes.size()-1 (despreciem element 0)
	int _nArestes;
	bool _dirigit;
	map<int, string> _vertexs;
	vector<map<int, etiqueta> > _arestes; // veïns o successors (depenent si dirigit)
};