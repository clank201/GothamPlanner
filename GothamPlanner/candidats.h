#pragma once
class candidats 
	/** \brief classe que ens generara els possibles candidats
	*/
{
public:
	candidats(int n = 0);   ///< @pre -- @post inicialitza la classe
	int actual() const;	   ///< @pre -- @post retorna el candidat actual
	bool esFi() const;	  ///< @pre -- @post retorna si som al ultim candidat
	void seguent();		 ///< @pre -- @post canvia el candidat pel seguent
private:
	// inv: 1≤iCan≤mida+1
	int iCan;
	int mida;
};