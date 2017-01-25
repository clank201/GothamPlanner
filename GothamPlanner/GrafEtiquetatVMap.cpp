#include "GrafEtiquetatVMap.h"
#include <string>
#include <iostream>

// Pre: cert
// Post: diu si hi ha aresta de v1 a v2
bool GrafEtiquetatVMap::ExisteixAresta(int v1, int v2) const {
	if (!esValid(v1) || !esValid(v2)) return false;
	else return (_arestes[v1].count(v2) == 1);
}
// Pre: v1 i v2 son vertexs del graf
// Post: afegeix l'aresta (v1,v2) si no existia
void GrafEtiquetatVMap::AfegirAresta(int v1, int v2, etiqueta e) {
	if (!esValid(v1) || !esValid(v2)) throw "Vertexs no valids";
	else if (!ExisteixAresta(v1, v2)) {
		_arestes[v1][v2] = e; _nArestes++;
		if (!_dirigit) _arestes[v2][v1] = e;
	}
}
// Pre: existeix aresta (v1,v2)
// Post: retorna etiqueta de l’aresta (v1,v2)
etiqueta GrafEtiquetatVMap::EtiquetaAresta(int v1, int v2) {
	if (!ExisteixAresta(v1, v2)) throw "No existeix aresta";
	else return _arestes[v1][v2];
}

int GrafEtiquetatVMap::getNumeroVertex(string s) {
	for (map<int, string>::const_iterator it = _vertexs.begin(); it != _vertexs.end(); ++it) {
		if (it->second == s) return it->first;
	}
	return -1;
}

string GrafEtiquetatVMap::getNomVertex(int n)
{
	for (map<int, string>::const_iterator it = _vertexs.begin(); it != _vertexs.end(); ++it) {
		if (it->first == n) return it->second;
	}
	return "";
}

GrafEtiquetatVMap::GrafEtiquetatVMap(int nVertexs, bool dirigit) {
	_dirigit = false;
	_nVertexs = 0;
	_nArestes = 0;
}

GrafEtiquetatVMap::GrafEtiquetatVMap(const char* nomFitxerTGF, bool dirigit) {
	_dirigit = dirigit;
	_nVertexs = 0;
	_nArestes = 0;
	ifstream entrada;
	entrada.open(nomFitxerTGF);
	if (entrada.fail()) throw "Error al obrir l'arxiu d'entrada";
	else {
		string c1, c2;
		entrada >> c1 >> c2;
		while (c1 != "#") {
			_nVertexs++;
			_arestes.resize(_nVertexs + 1);
			_vertexs.insert(pair<int, string>(stoi(c1), c2));
			entrada >> c1;
			if (c1 != "#") entrada >> c2;
		}
		string c3, c4;
		entrada >> c1 >> c2 >> c3 >> c4;
		while (!entrada.eof()) {
			etiqueta temp;
			temp.dist = stoi(c4);
			temp.perill = stof(c3);
			AfegirAresta(stoi(c1), stoi(c2), temp);
			entrada >> c1 >> c2 >> c3 >> c4;
		}
		etiqueta temp;
		temp.dist = stoi(c4);
		temp.perill = stof(c3);
		AfegirAresta(stoi(c1), stoi(c2), temp);
	}
	entrada.close();
}

int GrafEtiquetatVMap::nVertexs() const {
	return _nVertexs - 1;
}

int GrafEtiquetatVMap::nArestes() const {
	return _nArestes;
}

bool GrafEtiquetatVMap::esDirigit() const {
	return _dirigit;
}

void GrafEtiquetatVMap::EsborrarAresta(int v1, int v2) {
	_arestes[v1].erase(v2);
	if (!_dirigit) _arestes[v2].erase(v1);
}

bool GrafEtiquetatVMap::esValid(int v) const {
	return v >= 1 && v <= _nVertexs;
}