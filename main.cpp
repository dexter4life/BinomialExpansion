
#include "BinomialExpansion.h"
#include "Predefined.h"
#include "Resources.h"

#include <windows.h>

inline void displayHelpInfo()
{
	cout << "This program is capable of expanding binomial, to any number of terms. "
		<< "Can also deal with negative exponential cases of binomials\n"
		<< "Distributed under the GNU Licence, source code is not included"
		<< " \nUses: " << "\n binomial -f filename.txt -n xxxxx -d (x+1)^n"
		<< "\n binomial -n xxxxx -d (x+1)^n , if n = 0.1, 0.2, etc" 
		<< "\n binomial -d (x+1)^n , if n = 1, 2, etc "
		<< " \n Parameter: \n" << " -h or /? \t Display this messege "
		<< " \n -f \t\t Output to a file"
		<< " \n -n \t\t Number of terms to produce "
		<< " \n -d \t\t Display on the screen, defaulted to -d if -f is not specified"
		<< endl;

}
void printColorLine( int len, COORD pos, WORD color )
{
	DWORD dWritten = 0;
	FillConsoleOutputCharacterA( GetStdHandle( STD_OUTPUT_HANDLE ), '-', len, pos, &dWritten );
	FillConsoleOutputAttribute( GetStdHandle(STD_OUTPUT_HANDLE), color, len, pos, &dWritten );
}
int main( int argc, char *argv[] )
{
	int l=0, f=0, d = 0, h=0;
	ofstream outfile;
	
	LoadIconW(NULL, MAKEINTRESOURCE(IDI_ICON1)); 

	for( int i=0; i<argc; i++ )
	{
		if( strcmp( argv[i], "-n" ) == 0 )
			l = i+1;
		if( strcmp( argv[i], "-f" ) == 0 )
			f = i+1;
		if( strcmp( argv[i], "-d" ) == 0 )
			d = i;
		if( strcmp( argv[i], "-h" ) == 0 )
			h = i;
		if( strcmp( argv[i], "/?" ) == 0 )
			h = i;
	}
	/**
		-n xxxx // number of terms, if comtains fractional exponents
		-f name.txt  // print to a file
		-d display
		(x+1)^0.1 // value to calculate
		bexpand -n 10 -f name.txt (x+1)^0.1
	**/

	//is help info and terminate
	if( h!=0 || (!l&&!f&&!d ) )
	{
		cout << endl << endl;
		string msg = "BINOMIAL EXPANDER v1.1 © 2014 by Peter Nwanosike";
		COORD pos = { 12, 2 };
		DWORD dWritten = 0;
		FillConsoleOutputAttribute( GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_RED+1| 0x000000007, DWORD(msg.length()), pos, &dWritten );
		WriteConsoleOutputCharacterA( GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), DWORD(msg.length()),  pos, &dWritten );
		pos.Y++;
		pos.X=0;
		printColorLine( 80, pos, FOREGROUND_BLUE+1 );

		cout<< endl << "\n\n";
		displayHelpInfo();
		cin.get();	
		return 0;
	}

	CONSOLE_CURSOR_INFO cciInfo = {0};
	cciInfo.bVisible = false;
	cciInfo.dwSize = 1;
	SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &cciInfo ); 
	int level = atoi( argv[l] );

	if( f != 0)
	{
		outfile.open( argv[f] );
		if( !outfile )
			cerr << "Error open file, please ensure that their is enough memory in \n \
					your system" << endl;
	}
	BinomialExpansion binomialExpansion( argv[argc-1] );
	if( !l )
	{
		if( !f )
			cout << binomialExpansion.print_result() << endl;
		else if ( d && f )
		{
			cout << binomialExpansion.print_result() << endl;
			cout << "outputted to a file name: " << argv[f] << endl;
			outfile << binomialExpansion.print_result() << endl;
		}
		else
		{	
			cout << "outputted to a file name: " << argv[f] << endl;
			outfile << binomialExpansion.print_result() << endl;
		}
	}
	else
	{
		BinomialExpansion binomialExpansion( argv[argc-1] );
		if( !f)
			cout << binomialExpansion.print_result(level) << endl;
		else if ( d && f )
		{
			cout << binomialExpansion.print_result(level) << endl;
			cout << "outputted to a file name: " << argv[f] << endl;
			outfile << binomialExpansion.print_result( level) << endl;
		}
		else
		{
			cout << "outputted to a file name: " << argv[f] << endl;
			outfile << binomialExpansion.print_result(level) << endl;
		}
	}
	
	cciInfo.bVisible = true;
	cciInfo.dwSize = 1;
	SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &cciInfo ); 

	cout.flush();
	cin.get();
	return 0;
}