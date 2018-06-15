
#ifndef BINOMIAL_EXPANSION_H
#define BINOMIAL_EXPANSION_H


#include "Combination.h"
#include "ComponentExtract.h"

#include <cmath>
using std::pow;

#include <string>
using std::string;


class BinomialExpansion
{
private:
	Combination *combination;
	ComponentExtract *componentExtract;
	
public:
	BinomialExpansion();
	~BinomialExpansion();

	BinomialExpansion( const string& );

	long double calculateCoefficient( int );
	string generate_string( int );
	inline bool isFractionalExponent() const;
	bool isNegative() const;
	string print_result( int  = 0 ); // print binomial expansion

};
#endif