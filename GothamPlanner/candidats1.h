#pragma once
class candidats1 {
public:
	candidats1(int n = 0);
	int actual() const;
	bool esFi() const;
	void seguent();
private:
	// inv: 1≤iCan≤mida+1
	int iCan;
	int mida;
};