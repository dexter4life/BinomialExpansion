
#include "Combination.h"
#include "ComponentExtract.h"
#include "BinomialExpansion.h"

#include <sstream>
using std::ostringstream;

#include <iostream>
using std::cout;

#include <iomanip>
using std::setprecision;
using std::fixed;

#include <limits>

enum Control : short int { NODISPLAY, DISPLAY };

BinomialExpansion::BinomialExpansion() : componentExtract( new ComponentExtract() )
{
}

BinomialExpansion::BinomialExpansion(const std::string &bino ) 
: componentExtract( new ComponentExtract(bino) ), combination( new Combination )
{
}

BinomialExpansion::~BinomialExpansion()
{
	delete combination, componentExtract;
}

long double BinomialExpansion::calculateCoefficient( int i )
{
	double exp = (isNegative()) ? -1*componentExtract->getExponentialPart() : 
		componentExtract->getExponentialPart();

	combination->setCombination(exp, i );
	// fnpos flag is set to true if number comes first in the input
	
	if ( componentExtract->fnpos && !isFractionalExponent() )
	{
		return ( combination->getCombination() * pow( componentExtract->getNumericalComponent(), 
			componentExtract->getExponentialPart() - i )
			* pow( (componentExtract->getCharacterSign()), componentExtract->getExponentialPart()-i));
	}

	return ( combination->getCombination() * pow( componentExtract->getNumericalComponent(), i ) *
			pow( componentExtract->getCharacterSign(), i));
}
string BinomialExpansion::generate_string(int i )
{
	ostringstream output;
	
	//increase the precision of the print out
	//output << setprecision(2) << fixed;

	double c = this->calculateCoefficient(i);
	double p = (isNegative()) ? -1*componentExtract->getExponentialPart() 
		: componentExtract->getExponentialPart();
	
	char e = componentExtract->getCharacterComponent();

	if ( componentExtract->fnpos )
	{
		switch(i)
		{
		case NODISPLAY:
			output << c;
			break;
		case DISPLAY:
			( c > 0 ) ? output << " +" : output << ' ';
			( c == 1 ) ? output << c : output << c << e;
			break;
		default:
			( c > 0 ) ? output << " +" : output << ' ';
			( c == 1 ) ? output << e <<'^' << i : output << c << e <<'^' << i;
		}
	}
	else
	{	
		switch( i )
		{
		case NODISPLAY:
			// int(c)>>1 is zero print e else c
			if (c==1)
			{
				output<< e << "^";
				if( (p-i)!= 1 && (p-i)!=0 ) output << (p-i);
			}
			else{
				output <<  c << e << '^';
				if( (p-i)!= 1 && (p-i)!=0 ) output  << (p-i);
			}
			break;
		case DISPLAY:
			( c > 0 ) ? output << " +" : output << ' ';
			(c==1) ? output << c : output<<c<<e;
			if ((p-i)!= 1 && (p-i)!=0 ) output << '^' << (p-i);
			break;
		default:
			( c > 0 ) ? output << " +" : output << ' ';
			if(c == 1 ) 
			{
				output << c;
				if( (p-i)!= 1 && (p-i)!=0 )
					output << '^' << (p - i);
			}
			else 
			{ 
				( c == 1 || c== -1 || i==0) ? output << c : output << c<<e;
				if( (p-i)!= 1 && (p-i)!=0 ) output << '^' << (p - i);
			}
		}
	}
	return output.str();
}
bool BinomialExpansion::isFractionalExponent() const
{
	double tmp = 0;
	double e = componentExtract->getExponentialPart();
	// is a fraction 
	return ( modf( e, &tmp ) != 0 );
}

string BinomialExpansion::print_result( int level )
{ 
	double e = componentExtract->getExponentialPart();
	ostringstream out;

	if( !isFractionalExponent() ) // has a fractional part
	{
		if ( isNegative() )
		{
			out<<"1/( ";
			for( int i =0; i < ((-1*e)+1); i++ )
				out << generate_string(i);
			out<<" )";
		}
		else
			for( int i = 0; i<e+1; i++ )
				out << generate_string(i);
	}
	else
	{
		if( isNegative() )
		{
			out<<"1/( ";
			for( int i=0; i<level; i++ )
				out << generate_string(i);
		}
		for( int i=0; i!=level; i++ )
			out << generate_string(i);
		out<<" )";
	}

	return out.str();
}
bool BinomialExpansion::isNegative() const
{
	return ( componentExtract->getExponentialPart() < 0 );
}
