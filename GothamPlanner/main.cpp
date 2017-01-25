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

void opcio1(char* argv[]) {
	string origen(argv[2]), desti(argv[3]);
	double perillMax = stod(argv[4]);
	int distMax = stoi(argv[5]);
	string filename(argv[6]);
	GrafEtiquetatVMap graf(filename.c_str(),false);
	solucio sIni(&graf,distMax,graf.getNumeroVertex(desti), graf.getNumeroVertex(origen), perillMax);
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
	chrono::duration<double> time_span = std::chrono::duration_cast< std::chrono::duration<double> >(t2 - t1);
	segons = time_span.count();
	cout << "temps de càlcul: " << segons << endl;
}
void opcio2(char* argv[]) {
	string origen(argv[2]), desti(argv[3]);
	int distMax = stoi(argv[4]);
	string filename(argv[5]);
	GrafEtiquetatVMap graf(filename.c_str(), false);
	solucio sIni(&graf, distMax, graf.getNumeroVertex(desti), graf.getNumeroVertex(origen));
	solucionarOptim algBack;
	auto t1 = Clock::now();
	double segons;
	bool teSolucio = algBack.solucionar(sIni);
	if (teSolucio) {
		solucio sol = algBack.obtenirSolucio();
		cout << "Cerquem un cam´ı amb probabilitat atemptat global m´es baixa" << endl << "=====================================================================" << endl;
		sol.mostrar();
	}
	else {
		cout << "Cerquem un cam´ı amb probabilitat atemptat global m´es baixa" << endl << "=====================================================================" << endl;
		cout << endl << "El problema no té solució" << endl;
	}
	auto t2 = Clock::now();
	chrono::duration<double> time_span = std::chrono::duration_cast< std::chrono::duration<double> >(t2 - t1);
	segons = time_span.count();
	cout << "temps de càlcul: " << segons << endl;
}

void opcio3(char* argv[]) {
	string origen(argv[2]), desti(argv[3]);
	string filename(argv[4]);
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
		else if (opcio == "-g") {//greedy
			if (argc < 3) throw "Falten paràmetres";
			opcio3(argv);
		}
		else {
			throw ("Opcio desconeguda: " + opcio);
		}
	}
}

void mostrarHelp() {
	cout << "*** Obtencio de camins segurs entre dos nodes ***" << endl <<
		"Utilitzacio: . / camisegur opcio fitxer" << endl <<
		"on opcio pot ser :" << endl <<
		"-h, --help : mostra aquest missatge d’ajuda i surt" << endl <<
		"-u o d a len : cerca un camí entre o i d on tots els segments tenen" << endl <<
		"probabilitat d’atemptat <= a i longitud camí <= len" << endl <<
		"-s o d len : cerca un camí entre o i d amb una longitud <= len" << endl <<
		"que minimitzi la probabilitat de patir un atemptat." << endl <<
		"-g o d : utilitza una estrategia voraç(greedy) per buscar" << endl <<
		"un cami entre o i d amb seguretat relativament alta.  " << endl <<
		"fitxer ha de ser un fitxer de text en el format TGF descrit" << endl;
}