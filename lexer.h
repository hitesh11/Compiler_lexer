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
		RPC, LPS, RPS, NUM, REAL, COMMA, COLON, ID, NA, EOI, OR, AND, NOT, DQT, SQT, 
		AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE, ELSE, ENUM, EXTERN,
		FLOAT, FOR, GOTO, IF, INT, LONG, REGISTER, RETURN, SHORT, SIGNED, SIZEOF, STATIC, 
		STRUCT, SWITCH, TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE, WHILE
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
