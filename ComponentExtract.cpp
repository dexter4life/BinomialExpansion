
#include "ComponentExtract.h"

#include<string>
using std::string;

#include <iostream>

bool ComponentExtract::fnpos;

// default constructor
ComponentExtract::ComponentExtract() : iSign(0)
{
// nothing yet
}
//conversion constructor
ComponentExtract::ComponentExtract(const std::string &binomial ) : iSign(0)
{
	extractTerms(binomial);
}
/*Extract the terms from the binomials*/
void ComponentExtract::extractTerms(const std::string &term )
{
	// compute lowlevel AI on string **(x+5)^2** to extract components
	std::string::size_type _spos = term.find( "(");  
	if ( _spos != string::npos )
		if ( !isalpha(term.c_str()[_spos+1 ]) ){
			fnpos = true; // flag is set false if character comes first
			pterm.first = atof(term.c_str()+_spos+1);
		}
		else
			pterm.first = atof( term.c_str()+ term.find_first_of("+-"));
	for( string::const_iterator it=term.begin(); it < term.end(); it++ )
		if ( isalpha( *it ) )
			pterm.second = *it;
	
	_spos = term.find( "^" );
	if (  _spos != string::npos )
		exponents = atof( (term.c_str()+_spos+1));
	
	
	string::size_type cpos = term.find("-");
	if( ( cpos != string::npos) && isalpha(term[cpos+1]))
		iSign = -1;
	else
		iSign = +1;
}

char ComponentExtract::getCharacterComponent() const
{
	return this->pterm.second;
}

double ComponentExtract::getNumericalComponent() const
{
	return this->pterm.first;
}

double ComponentExtract::getExponentialPart() const
{
	return this->exponents;
}

__tpair ComponentExtract::getPairs() const
{
	return this->pterm;
}

double ComponentExtract::getCharacterSign() const
{
	return iSign;
}