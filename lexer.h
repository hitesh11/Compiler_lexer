#ifndef H_LEXER
#define H_LEXER
#include <iostream>
#include <istream>
#include <cstdio>
#include <string>
#include "lookaheadStream.h"
#include "trie.h"
using namespace std;
class lexer {

public:
	enum TokenType {
		SEMI, PLUS, PLUSPLUS, PLUSEQL, MINUS, MINUSMINUS, MINUSEQL, TIMES, TIMESEQL, 
		DIVIDES, DIVIDESEQL, EQL, EQLEQL, MOD, MODEQL, GR, GE, LS, LE, NE, LP, RP, LPC, 
		RPC, LPS, RPS, INT, REAL, COMMA, COLON, ID, NA, EOI, IF, THEN, WHILE, DO, BEGIN, END,
		OR, AND, NOT, DQT, SQT
	};
	
	typedef struct token {
		TokenType type;
		string value;
		int lineNumber;
		
		token(TokenType, string, int);
		void set(TokenType, string);
	} token;

private:
	lookaheadStream _ls;
	token _curToken;
	trie<TokenType> _keywords;
	
public:
	token e;
	token currentToken();
	void advance();
	lexer(istream& _fs);
	bool eof;
	bool validToken();
	token at(int);
	bool matches(TokenType);
};
#endif
