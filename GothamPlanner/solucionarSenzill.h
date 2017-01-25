#pragma once
#include "solucio.h"

class solucionarSenzill 
	/** \brief Classe solucionador per al primer backtracking
	*/
{
public:
	bool solucionar(const solucio &inicial);   ///< @pre -- @post retorna si el problema te solucio
	solucio obtenirSolucio() const;	  ///< @pre -- @post retorna la solucio del problema
private:
	void trobarUnaSolucio();  ///< @pre -- @post busca una sola solucio
	// inv: no encertat o encertat ^ sol completada
	bool encertat;
	solucio sol;
};
