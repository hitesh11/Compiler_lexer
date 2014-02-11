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

	string token_classes[100] = {"SEMI", "PLUS", "PLUSPLUS", "PLUSEQL", "MINUS", "MINUSMINUS", "MINUSEQL", "TIMES", "TIMESEQL", 
		"DIVIDES", "DIVIDESEQL", "EQL", "EQLEQL", "MOD", "MODEQL", "GR", "GE", "LS", "LE", "NE", "LP", "RP", "LPC", 
		"RPC", "LPS", "RPS", "NUM", "REAL", "COMMA", "COLON", "ID", "NA", "EOI", "OR", "AND", "NOT", "AUTO", "BREAK", "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELSE", "ENUM", "EXTERN",
		"FLOAT", "FOR", "GOTO", "IF", "INT", "LONG", "REGISTER", "RETURN", "SHORT", "SIGNED", "SIZEOF", "STATIC", 
		"STRUCT", "SWITCH", "TYPEDEF", "UNION", "UNSIGNED", "VOID", "VOLATILE", "WHILE", "CHARCNST", "STRCNST"};

	ifstream f("tst2");
	lexer lex(f);
	cout<<"Symbol Table :\n";
	

	while(lex.currentToken().type != lexer::EOI)
	{
		cout<<lex.currentToken().value<<" : ";
		cout<<token_classes[lex.currentToken().type]<<" \n ";
				
		lex.advance();
	}
	cout << "\n Done !\n" ;

	return 0;
}