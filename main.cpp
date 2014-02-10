#include <iostream>
#include "lexer.h"
#include "lexer.cpp"
#include "lookaheadStream.h"
#include "lookaheadStream.cpp"
#include <fstream>
#include <string>

using namespace std;


int main()
{

	string token_classes[30] = {"SEMI", "PLUS", "PLUSPLUS", "PLUSEQL", "MINUS", "MINUSMINUS", "MINUSEQL", "TIMES", "TIMESEQL", 
		"DIVIDES", "DIVIDESEQL", "EQL", "EQLEQL", "MOD", "MODEQL", "GR", "GE", "LS", "LE", "NE", "LP", "RP", "LPC", 
		"RPC", "LPS", "RPS", "INT", "REAL", "COMMA", "COLON", "ID", "NA", "EOI", "IF", "THEN", "WHILE", "DO", "BEGIN", "END",
		"OR", "AND", "NOT", "DQT", "SQT"};

	ifstream f("tst");
	lexer lex(f);
	cout<<"Symbol Table :\n";

	while(lex.currentToken().type != lexer::EOI)
	{
		cout<<lex.currentToken().value<<" : ";
		cout<<token_classes[lex.currentToken().type]<<"\n";
		lex.advance();
	}
	return 0;
}