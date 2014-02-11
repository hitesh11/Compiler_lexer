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
	int line_num = 0;
	int prev_line_num=0;

	while(lex.currentToken().type != lexer::EOI)
	{
		//Printing tokens line by line (ignoring blanck lines in between)
		line_num=lex.currentToken().lineNumber;
		if (line_num!=prev_line_num)
			cout <<"\n";
		prev_line_num= line_num;
		cout<<"< "<<lex.currentToken().value<<", ";
		cout<<token_classes[lex.currentToken().type]<<" > | ";
			
		
		lex.advance();
	}
	cout << "\n Done !\n" ;

	return 0;
}