#pragma once
class candidatsGotham1 {
public:
	candidatsGotham1(int ant, int max);
	int actual() const;
	bool esFi() const;
	void seguent();
private:
	// inv: 0<iCan≤nObjs+1
	int iCan, nObjs;
};