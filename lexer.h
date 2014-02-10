#ifndef H_LEXER
#define H_LEXER
#include <iostream>
#include <istream>
#include <cstdio>
#include <string>
#include <set>
#include "lookaheadStream.h"
#include "trie.h"
using namespace std;
class lexer {

public:
	enum TokenType {
		SEMI, PLUS, PLUSPLUS, PLUSEQL, MINUS, MINUSMINUS, MINUSEQL, TIMES, TIMESEQL, 
		DIVIDES, DIVIDESEQL, EQL, EQLEQL, MOD, MODEQL, GR, GE, LS, LE, NE, LP, RP, LPC, 
		RPC, LPS, RPS, NUM, REAL, COMMA, COLON, ID, NA, EOI, OR, AND, NOT, AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE, ELSE, ENUM, EXTERN,
		FLOAT, FOR, GOTO, IF, INT, LONG, REGISTER, RETURN, SHORT, SIGNED, SIZEOF, STATIC, 
		STRUCT, SWITCH, TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE, WHILE, CHARCNST, STRCNST
	};
	
	typedef struct token {
		TokenType type;
		string value;
		int lineNumber;
		
		token(TokenType, string, int);
		void set(TokenType, string);
	} token;

	char array_spl_char [];
	set <char> spl_char;
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
	bool validTokenEnd(char c);
	bool intialiseSplSet();
};
#endif
