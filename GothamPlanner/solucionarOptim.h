#pragma once
#include "solucio.h"

class solucionarOptim
	/** \brief classe solucionador per al segon backtracking
	*/
{
public:
	solucio solucionar(const solucio &inicial);	  ///< @pre -- @post retorna la millor solucio al problema
private:
	void trobarMillor(solucio & actual);	 ///< @pre -- @post busca una millor solucio
	// inv: no encertat o encertat ^ sol completada
	solucio sol;
	solucio optima;
};