#include "lexer.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
using namespace std;

lexer::token::token(lexer::TokenType t, string v, int l): type(t), value(v), lineNumber(l){
}

void lexer::token::set(lexer::TokenType t, string v){
	this->type = t;
	this->value = v;
}

lexer::lexer (istream& _fs):_ls(_fs), _curToken(lexer::NA, "", 0), e(lexer::NA, "", 0), _keywords(lexer::NA){
	eof = false;
	
	_keywords.insert("auto", lexer::AUTO);
	_keywords.insert("break",lexer::BREAK);
	_keywords.insert("case",lexer::CASE);
	_keywords.insert("char",lexer::CHAR);
	_keywords.insert("const",lexer::CONST);
	_keywords.insert("continue",lexer::CONTINUE);
	_keywords.insert("default",lexer::DEFAULT);
	_keywords.insert("do", lexer::DO);
	_keywords.insert("double", lexer::DOUBLE);
	_keywords.insert("else",lexer::ELSE);
	_keywords.insert("enum",lexer::ENUM);
	_keywords.insert("extern",lexer::EXTERN);
	_keywords.insert("float",lexer::FLOAT);
	_keywords.insert("for",lexer::FOR);
	_keywords.insert("goto",lexer::GOTO);
	_keywords.insert("if", lexer::IF);
	_keywords.insert("int", lexer::NUM);
	_keywords.insert("long", lexer::LONG);
	_keywords.insert("register", lexer::REGISTER);
	_keywords.insert("return", lexer::RETURN);
	_keywords.insert("short", lexer::SHORT);
	_keywords.insert("signed", lexer::SIGNED);
	_keywords.insert("sizeof", lexer::SIZEOF);
	_keywords.insert("static", lexer::STATIC);
	_keywords.insert("struct", lexer::STRUCT);
	_keywords.insert("switch", lexer::SWITCH);
	_keywords.insert("typedef", lexer::TYPEDEF);
	_keywords.insert("union", lexer::UNION);
	_keywords.insert("unsigned", lexer::UNSIGNED);
	_keywords.insert("void", lexer::VOID);
	_keywords.insert("volatile", lexer::VOLATILE);
	_keywords.insert("while", lexer::WHILE);

	intialiseSplSet();
	advance();
}

lexer::token lexer::currentToken(){
	return _curToken;
}

bool lexer::validToken(){
	return _curToken.type != lexer::NA;
}

bool lexer::intialiseSplSet(){
	char array_spl_char [] = ";+-=;,<>?:[]{}()~!#^*|.%\'\"";
	spl_char.insert(array_spl_char,array_spl_char+strlen(array_spl_char));
}

//returns true if c is a special character or space chararcters 
bool lexer::validTokenEnd(char c){
	if (spl_char.find(c)!=spl_char.end() || isspace(c) || c==EOF)
		return true;
	else
		return false;
}

void lexer::nextValidTokenBegin(){

		char c=(char)_ls.peek();
		while(!validTokenEnd(c)){
			
			_ls.next();
			c = (char)_ls.peek();
		}	
}
bool lexer::matches(lexer::TokenType t){
	if (t == _curToken.type){
		e = _curToken;
		advance();
		return true;
	}
	return false;
}

lexer::token lexer::at(int p){

	if (p==0) return _curToken;

	int offset=0;
	token t(NA, "", _curToken.lineNumber);
	
	for (int i=0; i<p; i++){
		int c;
		
		while ((c=_ls.at(offset))!=EOF && isspace((char)c)){
			if (c=='\n') t.lineNumber++;
			offset++;
		}
		
		if (c==EOF){
			t.type = lexer::EOI;
			t.value = "";
			continue;
		}
	
		if (_ls.match(":=", offset)){
			t.type = lexer::EQL;
			t.value = ":=";
			offset += 2;
			continue;
		}
	
		if (_ls.match("+", offset)){
			t.type = lexer::PLUS;
			t.value = "+";
			offset += 1;
			continue;
		}
	
		if (_ls.match("(", offset)){
			t.type = lexer::LP;
			t.value = "(";
			offset += 1;
			continue;
		}
	
		if (_ls.match(")", offset)){
			t.type = lexer::RP;
			t.value = ")";
			offset += 1;
			continue;
		}
	
		if (_ls.match(";", offset)){
			t.type = lexer::SEMI;
			t.value = ";";
			offset += 1;
			continue;
		}
		
		if (_ls.matchAndConsume("*")){
			_curToken.set(lexer::TIMES, "*");
			continue;
		}
	
		if (_ls.matchAndConsume("/")){
			_curToken.set(lexer::DIVIDES, "/");
			continue;
		}
	
		if (_ls.matchAndConsume("<")){
			_curToken.set(lexer::LS, "<");
			continue;
		}
	
		if (_ls.matchAndConsume(">")){
			_curToken.set(lexer::GR, ">");
			continue;
		}
	
		if (_ls.matchAndConsume("=")){
			_curToken.set(lexer::EQL, "=");
			continue;
		}
		
		if (c>='0' && c<='9'){
			//number
			stringstream s;
			while ((c=_ls.at(offset))>='0' && c<='9' && c!=EOF){
				s.put((char)c);
				offset++;
			}
			t.type = lexer::NUM;
			t.value = s.str();
			continue;
		}
	
		if (isalpha(c)){
			//id or keyword
			_keywords.refresh();
		
			stringstream s;
			while ((c=_ls.at(offset))!=EOF && isalpha(c)){
				s.put(c);
				_keywords.input(c);
				offset++;
			}
		
			//if token is a valid keyword
			if (_keywords.validState()){
				t.type = _keywords.getSD();
				t.value = s.str();
				continue;
			}
		
			//token is an id
			t.type = lexer::ID;
			t.value = s.str();
			continue;
		}
	
		t.type = lexer::NA;
		t.value = "";
		
	}
	
	return t;
}

void lexer::advance(){
	int c;
	while ((c=_ls.peek())!=EOF && isspace((char)c)){
		if (c=='\n') _curToken.lineNumber++;
		_ls.next();
	}
	
	//TODO: integrate symbols into trie based matching
	
	if (c==EOF){
		eof = true;
		_curToken.type = lexer::EOI;
		_curToken.value = "";
		return;
	}
	
	if (_ls.matchAndConsume("=")){
		if(_ls.matchAndConsume("="))
			_curToken.set(lexer::EQLEQL, "==");
		else
			_curToken.set(lexer::EQL, "=");
		return;
	}

	if (_ls.matchAndConsume("+")){
			if(_ls.matchAndConsume("+")){
				_curToken.type = lexer::PLUSPLUS;
				_curToken.value = "++";
			}
			else if(_ls.matchAndConsume("=")){
				_curToken.type = lexer::PLUSEQL;
				_curToken.value = "+=";
			}
			else{
				_curToken.type = lexer::PLUS;
				_curToken.value = "+";				
			}
		return;
	}
	
	if (_ls.matchAndConsume("-")){
			if(_ls.matchAndConsume("-")){
				_curToken.type = lexer::MINUSMINUS;
				_curToken.value = "--";
			}
			else if(_ls.matchAndConsume("=")){
				_curToken.type = lexer::MINUSEQL;
				_curToken.value = "-=";
			}
			else{
				_curToken.type = lexer::MINUS;
				_curToken.value = "-";				
			}
		return;
	}


	if (_ls.matchAndConsume("(")){
		_curToken.type = lexer::LP;
		_curToken.value = "(";
		return;
	}
	
	if (_ls.matchAndConsume(")")){
		_curToken.type = lexer::RP;
		_curToken.value = ")";
		return;
	}
	
	if (_ls.matchAndConsume("{")){
		_curToken.type = lexer::LPC;
		_curToken.value = "{";
		return;
	}	
	
	if (_ls.matchAndConsume("}")){
		_curToken.type = lexer::RPC;
		_curToken.value = "}";
		return;
	}

	if (_ls.matchAndConsume("[")){
		_curToken.type = lexer::LPS;
		_curToken.value = "[";
		return;
	}

	if (_ls.matchAndConsume("]")){
		_curToken.type = lexer::RPS;
		_curToken.value = "]";
		return;
	}

	if (_ls.matchAndConsume(";")){
		_curToken.type = lexer::SEMI;
		_curToken.value = ";";
		return;
	}
	
	if (_ls.matchAndConsume("*")){
		if(_ls.matchAndConsume("="))
			_curToken.set(lexer::TIMESEQL, "*=");
		else
			_curToken.set(lexer::TIMES, "*");
		return;
	}
	
	if (_ls.matchAndConsume("/")){
		if(_ls.matchAndConsume("="))
			_curToken.set(lexer::DIVIDESEQL, "/=");
		else
			_curToken.set(lexer::DIVIDES, "/");
		return;
	}

	if (_ls.matchAndConsume("%")){
		if(_ls.matchAndConsume("="))
			_curToken.set(lexer::MODEQL, "%=");
		else
			_curToken.set(lexer::MOD, "%");
		return;
	}

	if(_ls.matchAndConsume("!")){
		if(_ls.matchAndConsume("="))
			_curToken.set(lexer::NOT, "!=");
		else
			_curToken.set(lexer::NE, "!");
		return;
	}

	if(_ls.matchAndConsume("||")){
		_curToken.set(lexer::OR, "||");
		return;
	}

	if(_ls.matchAndConsume("&&")){
		_curToken.set(lexer::AND, "&&");
		return;
	}

	if (_ls.matchAndConsume("<")){
		if(_ls.matchAndConsume("="))
			_curToken.set(lexer::LE, "<=");
		else
			_curToken.set(lexer::LS, "<");
		return;
	}
	
	if (_ls.matchAndConsume(">")){
		if(_ls.matchAndConsume("="))
			_curToken.set(lexer::GE, ">=");
		else
			_curToken.set(lexer::GR, ">");
		return;
	}

	if(_ls.matchAndConsume(",")){
		_curToken.set(lexer::COMMA, ",");
		return;
	}

	if(_ls.matchAndConsume(":")){
		_curToken.set(lexer::COLON, ":");
		return;
	}
	
	if ((c>='0' && c<='9') || c == '.'){
		//integer or real
		bool real = false;
		stringstream s;

		if(c != '.'){
			while ((c=_ls.peek())>='0' && c<='9' && c!=EOF){
				s.put((char)c);
				_ls.next();
			}
		}
		if(c == '.'){
			real = true;
			s.put('.');
			_ls.next();
			while ((c=_ls.peek())>='0' && c<='9' && c!=EOF){
			s.put((char)c);
			_ls.next();
			}
		}
		if(real)
			_curToken.type = lexer::REAL;
		else
			_curToken.type = lexer::NUM;
		_curToken.value = s.str();

		if(c == '.')
			fprintf(stderr, "%d: Unexpected floating point\n", _curToken.lineNumber);
		else if (!validTokenEnd((char) c)){
				fprintf(stderr, "%d: Invalid ending of a number constant -> %s followed by %c\n", _curToken.lineNumber, _curToken.value.c_str(), (char) c);
				nextValidTokenBegin();
				}	
		return;
	}

	if(c == '\''){
		//character constant
		_ls.next();
		c = _ls.peek();
		stringstream s;
		if(!isalnum(c))
			fprintf(stderr, "%d: Invalid character\n", _curToken.lineNumber);
		s.put(c);
		_ls.next();
		c = _ls.peek();
		if(c!='\'')
			fprintf(stderr, "%d: Expected <'>\n", _curToken.lineNumber);
		_curToken.type = lexer::CHARCNST;
		_curToken.value = s.str();
		_ls.next();
		return;
	}

	if(c == '"'){
		//string constant
		stringstream s;
		_ls.next();
		while((c=_ls.peek())!='\"' && c!=EOF){
			
			s.put(c);
			_ls.next();
			
			if ((c=='\\') && (_ls.peek()=='\"')){
				s.put(_ls.peek());
				_ls.next();
			}
			
			
		}
		if(c==EOF)
			fprintf(stderr, "%d: Unmatched <\">\n", _curToken.lineNumber);
		_curToken.type = lexer::STRCNST;
		_curToken.value = s.str();
		_ls.next();
		return;
	}

	
	if (isalpha(c)){
		//id or keyword
		_keywords.refresh();
		stringstream s;
		char nextc;
		while ((c=_ls.peek())!=EOF && isalnum(c)){
			s.put(c);
			_keywords.input(c);
			_ls.next();
		}
		
		//if token is a valid keyword
		if (_keywords.validState()){
			_curToken.type = _keywords.getSD();
			_curToken.value = s.str();
			nextc = (char) _ls.peek();
			if (!validTokenEnd(nextc)){
				cout << "next : "<<nextc <<endl;
				fprintf(stderr, "%d: Keyword followed by invalid characters\n", _curToken.lineNumber);
			}
			return;
		}
		
		//token is an id
		_curToken.type = lexer::ID;
		_curToken.value = s.str();
		nextc = (char) _ls.peek();
			if (!validTokenEnd(nextc)){
				cout << "next : "<<nextc <<endl;
				fprintf(stderr, "%d: Identifier followed by invalid characters\n", _curToken.lineNumber);
			}	
		return;
	}
	
	_curToken.type = lexer::NA;
	_curToken.value = "";
}
