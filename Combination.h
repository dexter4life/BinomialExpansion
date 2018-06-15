
#ifndef COMBINATION_H
#define COMBINATION_H


/*
AUTHOR: Peter Nwansosike

This sessions finds the combination having a fraction
-----------------------------------------------------
Example -- (x+a)^0.5

*/


class Combination 
{
private:
	double c;
	double __fastcall complex_combination( double, int  );
	// using __fastcall to optimize code
public:
	Combination();
	double fact(int) const;
	void setCombination( double, int );
	double getCombination() const;
};
#endif
