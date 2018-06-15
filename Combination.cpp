
#include "Combination.h"

Combination::Combination() : c(0)
{
	//do - nothing
}

double __fastcall Combination::complex_combination(double n, int r)
{
	if( r == 0 ) // nC0 case
		return 1;

	double tmp, f, p, result=n;
	tmp = n-r;
	f = fact(r);
	
	for( int i=1; i!=r; i++ ){
		p = (n-i);
		if( p == tmp )
		break;
		else
		result *= p;
	}
	return ( result/f);
}

void Combination::setCombination( double n, int r )
{
	c = complex_combination(n,r);
}

double Combination::getCombination() const
{
	return c;
}
double Combination::fact( int n ) const
{
	// for non-fractional cases
	if( n == 1 || n == 0 )
		return n;
	else
		return n * fact( n-1);
}