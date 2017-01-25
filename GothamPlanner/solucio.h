#pragma once
#include "candidats.h"
#include <vector>
#include "GrafEtiquetatVMap.h"

using namespace std;

class solucio
	/** \brief classe solucio per als backtrackings, aqui és on tindrem la majoria de dades externes
	*/
{
public:
	solucio();	 ///< @pre -- @post genera una solucio buida
	solucio(GrafEtiquetatVMap* graf, int d,int objectiu, int origen, double p = 1);	   ///< @pre -- @post genera una solucio a partir dels paràmetres entrats
	solucio(const solucio &o);	 ///< @pre -- @post genera una solucio copiant de la que li hem especificat
	~solucio();	    ///< @pre -- @post esborra la solucio
	solucio & operator=(const solucio &o);	  ///< @pre -- @post operador d'igualtat
	candidats inicialitzarCandidats() const;   ///< @pre -- @post inicialitza els candidats
	bool acceptable(const candidats &iCan) const;	  ///< @pre -- @post retorna si el candidat especificat compleix els requisits del problema
	void anotar(const candidats &iCan);	   ///< @pre -- @post anota el candidat a la solucio
	void desanotar(const candidats &iCan);	 ///< @pre -- @post treu el candidat de la solucio
	bool completa() const;	   ///< @pre -- @post ens diu si la solucio es completa
	void mostrar() const;		 ///< @pre -- @post mostra la solucio per pantalla
	bool millorQue(solucio sol);	  ///< @pre -- @post ens diu si la solucio és millor que la solucio que li hem especificat
private:
	void reserva();		  ///< @pre -- @post reserva memoria per la solucio
	void copia(const solucio &o);  ///< @pre -- @post copia la solucio
	void allibera();	  ///< @pre -- @post allibera la memoria de la solucio
	GrafEtiquetatVMap* g;
	vector<int> recorregut;
	int distAcum;
	int distMax;
	double perillMax;
	int tamany;
	int objectiu;
	double perillAcum;
};