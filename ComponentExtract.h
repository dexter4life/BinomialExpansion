
/*
Extract terms or element of a monomial, and assign each to a variable.
Processing in the double variable data type.

(x+y)^n

double dFirstTerm = +x
		dSecondTerm = +y
		dExponent = n
*/

//---BEGIN
#ifndef COMPONENT_EXTRACT_H
#define COMPONENT_EXTRACT_H

#include <utility>
using std::pair;

#include <vector>
using std::vector;

#include <string>
using std::string;


typedef pair< double, char > __tpair;

class ComponentExtract
{

private: // private members ( redundant access specifier )
	__tpair pterm; // hold the terms ( number, character(x) )
	double exponents; //n -- exponents
	short int iSign;
public: // define and declare utility function members
	ComponentExtract();
	explicit ComponentExtract( const string& );
	//------------------ get member function--------------------------
	double getNumericalComponent() const;
	char getCharacterComponent() const;
	double getExponentialPart() const;
	double getCharacterSign() const;

	__tpair getPairs() const;
	//+--------------------------------------------------------------
	static bool fnpos;

	void setBinoElements( const string &);
	void extractTerms( const string & );
};

//----END
#endif
