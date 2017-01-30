#pragma once
#include <vector>
#include <map>
#include <fstream>	

using namespace std;

struct etiqueta {
	etiqueta() : dist(-1), perill(-1) {}
	int dist;
	float perill;
};

const int MIDA_DEFECTE = 1000;
class GrafEtiquetatVMap {
public:
	GrafEtiquetatVMap(int nVertexs = MIDA_DEFECTE, bool dirigit = false);	 ///< @pre -- @post genera un graf buit
	GrafEtiquetatVMap(const char *nomFitxerTGF, bool dirigit = false);	 ///< @pre nomFitxer es un nom d'arxiu tgf @post genera un graf a partir del arxiu tgf entrat
	int nVertexs() const;    ///< @pre -- @post retorna el nombre de vertexs del graf
	int nArestes() const;	 ///< @pre -- @post retorna el nombre d'arestes del graf
	bool esDirigit() const;	   ///< @pre -- @post retorna si el graf es dirigit
	void AfegirAresta(int v1, int v2, etiqueta e);  ///< @pre v1 i v2 son vertexs del graf @post afegeix l'aresta al graf
	bool ExisteixAresta(int v1, int v2) const;	 ///< @pre -- @post retorna si existeix l'aresta especificada
	void EsborrarAresta(int v1, int v2);    ///< @pre -- @post esborra l'aresta especificada
	bool esValid(int v) const;	  ///< @pre -- @post retorna si el vertexs pertany al graf
	etiqueta EtiquetaAresta(int v1, int v2);	 ///< @pre v1 i v2 son part d'una aresta @post retorna l'etiqueta especificada
	int getNumeroVertex(string);   ///< @pre -- @post retorna el codi del vertex
	string getNomVertex(int);   ///< @pre -- @post retorna el nom del vertex
private:
	int _nVertexs; // = _arestes.size()-1 (despreciem element 0)
	int _nArestes;
	bool _dirigit;
	map<int, string> _vertexs;
	vector<map<int, etiqueta> > _arestes; // veïns o successors (depenent si dirigit)
};