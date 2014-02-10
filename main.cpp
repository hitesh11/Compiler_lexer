#include <iostream>
#include "lexer.h"
#include "lexer.cpp"
#include "lookaheadStream.h"
#include "lookaheadStream.cpp"
#include <fstream>

using namespace std;


int main()
{
	ifstream f("tst");
	lexer lex(f);
	cout<<"Symbol Table :\n";

	while(lex.currentToken().type != lexer::EOI)
	{
		cout<<lex.currentToken().value<<" : ";
		cout<<lex.currentToken().type<<"\n";
		lex.advance();
	}
	return 0;
}

auto break case char const continue default do double else enum extern
float for goto if int long register return short signed sizeof static
struct switch typedef union unsigned void volatile while