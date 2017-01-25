#include <string>
#include <sstream>
#include <chrono>
#include <iostream>
#include "GrafEtiquetatVMap.h"
#include "solucionarMillor.h"
#include "solucio.h"
#include "solucionarSenzill.h"
#include "solucionarOptim.h"

using namespace std;

void mostrarHelp();

typedef std::chrono::high_resolution_clock Clock;

void opcio1(char* argv[]) /// @pre -- @post calcula el primer backtracking
{
	string origen(argv[2]), desti(argv[3]);
	double perillMax = stod(argv[4]);
	int distMax = stoi(argv[5]);
	string filename(argv[6]);
	GrafEtiquetatVMap graf(filename.c_str(), false);
	solucio sIni(&graf, distMax, graf.getNumeroVertex(desti), graf.getNumeroVertex(origen), perillMax);
	solucionarSenzill algBack;
	auto t1 = Clock::now();
	double segons;
	bool teSolucio = algBack.solucionar(sIni);
	if (teSolucio) {
		solucio sol = algBack.obtenirSolucio();
		cout << "Cerquem un cami amb probabilitat atemptat en un tram < que cert valor" << endl << "=====================================================================" << endl;
		sol.mostrar();
	}
	else {
		cout << "Cerquem un cami amb probabilitat atemptat en un tram < que cert valor" << endl << "=====================================================================" << endl;
		cout << endl << "El problema no té solució" << endl;
	}
	auto t2 = Clock::now();
	chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	segons = time_span.count();
	cout << "temps de càlcul: " << segons << endl;
}
void opcio2(char* argv[]) /// @pre -- @post calcula el segon backtracking
{
	string origen(argv[2]), desti(argv[3]);
	int distMax = stoi(argv[4]);
	string filename(argv[5]);
	GrafEtiquetatVMap graf(filename.c_str(), false);
	solucio sIni(&graf, distMax, graf.getNumeroVertex(desti), graf.getNumeroVertex(origen));
	solucionarOptim algBack;
	auto t1 = Clock::now();
	double segons;
	solucio sol = algBack.solucionar(sIni);
	if (sol.completa()) {
		cout << "Cerquem un cam´ı amb probabilitat atemptat global m´es baixa" << endl << "=====================================================================" << endl;
		sol.mostrar();
	}
	else {
		cout << "Cerquem un cam´ı amb probabilitat atemptat global m´es baixa" << endl << "=====================================================================" << endl;
		cout << endl << "El problema no té solució" << endl;
	}
	auto t2 = Clock::now();
	chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	segons = time_span.count();
	cout << "temps de càlcul: " << segons << endl;
}
void vorasProfunditat(GrafEtiquetatVMap & g, int desti, int origen)  /// @pre -- @post executa l'algoritme voraç
{
	vector<map<int, bool> > arestesVisitades;
	arestesVisitades.resize(g.nVertexs() + 1);
	vector <int> recorregut;
	int vertexActual = origen, dMinima = -1, totalDist = 0, vBest;
	double probAcum = 0, millorProb = 1;
	bool trobat = true;
	recorregut.push_back(vertexActual);
	while (vertexActual != desti && trobat) {
		millorProb = 1;
		dMinima = -1;
		for (int i = 1; i <= g.nVertexs(); i++) {
			if (g.ExisteixAresta(vertexActual, i) && arestesVisitades[vertexActual].count(i) == 0) {
				etiqueta e = g.EtiquetaAresta(vertexActual, i);
				if (e.perill < millorProb || ((dMinima == -1 || dMinima > e.dist) && (e.perill == millorProb))) {
					millorProb = e.perill;
					dMinima = e.dist;
					vBest = i;
				}
			}
		}
		if (dMinima != -1) {
			recorregut.push_back(vBest);
			arestesVisitades.reserve(arestesVisitades.size() * 2);
			arestesVisitades[vertexActual][vBest] = true;
			arestesVisitades[vBest][vertexActual] = true;
			probAcum = 1 - ((1 - probAcum) * (1 - millorProb));
			vertexActual = vBest;
			totalDist += dMinima;
		}
		else {
			trobat = false;
		}
	}
	if (trobat) {
		cout << "Per anar de " << g.getNomVertex(origen) << " a " << g.getNomVertex(desti) << " tenim el seguent camí:" << endl;
		for (int i = 0; i < recorregut.size() - 1; i++) {
			cout << (g.getNomVertex(recorregut[i]));
			if (i != recorregut.size()) {
				cout << "-";
			}
		}
		cout << endl << g.getNomVertex(recorregut[recorregut.size() - 1]) << endl;
		cout << "amb una probabilitat de patir un atemptat de " << (probAcum) << endl;
		cout << "i amb una distancia total de " << double(totalDist) / 1000 << " quilòmetres" << endl;
	}
	else {
		cout << "no hi ha solució" << endl;
	}

}
void opcio3(char* argv[])  /// @pre -- @post calcula el tercer problema
{
	string origen(argv[2]), desti(argv[3]);
	string filename(argv[4]);
	GrafEtiquetatVMap graf(filename.c_str());
	auto t1 = Clock::now();
	double segons;
	vorasProfunditat(graf, graf.getNumeroVertex(desti), graf.getNumeroVertex(origen));
	auto t2 = Clock::now();
	chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	segons = time_span.count();
	cout << "temps de càlcul: " << segons << endl;
}

int main(int argc, char* argv[]) {
	stringstream args(argv[1]);
	string opcio(argv[1]);
	if (opcio == "--help") {
		mostrarHelp();
	}
	else {
		if (opcio == "-u") {//cami threshold
			if (argc < 7) throw "Falten paràmetres";
			opcio1(argv);
		}
		else if (opcio == "-s") {//cami segur
			if (argc < 6) throw "Falten paràmetres";
			opcio2(argv);
		}
		else if (opcio == "-g") {//vorasProfunditat
			if (argc < 3) throw "Falten paràmetres";
			opcio3(argv);
		}
		else {
			throw ("Opcio desconeguda: " + opcio);
		}
	}
}

void mostrarHelp()  /// @pre -- @post mostra el missatge d'ajuda
{
	cout << "*** Obtencio de camins segurs entre dos nodes ***" << endl <<
		"Utilitzacio: . / camisegur opcio fitxer" << endl <<
		"on opcio pot ser :" << endl <<
		"-h, --help : mostra aquest missatge d’ajuda i surt" << endl <<
		"-u o d a len : cerca un camí entre o i d on tots els segments tenen" << endl <<
		"probabilitat d’atemptat <= a i longitud camí <= len" << endl <<
		"-s o d len : cerca un camí entre o i d amb una longitud <= len" << endl <<
		"que minimitzi la probabilitat de patir un atemptat." << endl <<
		"-g o d : utilitza una estrategia voraç(vorasProfunditat) per buscar" << endl <<
		"un cami entre o i d amb seguretat relativament alta.  " << endl <<
		"fitxer ha de ser un fitxer de text en el format TGF descrit" << endl;
}