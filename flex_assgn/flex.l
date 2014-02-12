	int num_lines = 1, num_chars = 0;

DIGIT [0-9]
ALPHA [a-zA-Z]
ALPHANUM [a-zA-Z0-9]
STR [%.,;*+ a-zA-Z0-9]
%%
"\n" num_lines++;
[ \t] ;

"=" {printf("= : EQL\n");}
"==" {printf("== : EQLEQL\n");}
"+" {printf("+ : PLUS\n");}
"++" {printf("++ : PLUSPLUS\n");}
"+=" {printf("+= : PLUSEQL\n");}
"-" {printf("- : MINUS\n");}
"--" {printf("-- : MINUSMINUS\n");}
"-=" {printf("-= : MINUSEQL\n");}
"(" {printf("( : LP\n");}
")" {printf(") : RP\n");}
"{" {printf("{ : LPC\n");}
"}" {printf("} : RPC\n");}
"[" {printf("[ : LPS\n");}
"]" {printf("] : LPR\n");}
";" {printf("; : SEMI\n");}
"*" {printf("* : TIMES\n");}
"*=" {printf("*= : TIMESEQL\n");}
"/" {printf("/ : DIVIDES\n");}
"/=" {printf("/= : DIVIDESEQL\n");}
"%" {printf("%% : MOD\n");}
"%=" {printf("%%= : MODEQL\n");}
"!" {printf("! : NOT\n");}
"!=" {printf("!= : NE\n");}
"||" {printf("|| : OR\n");}
"&&" {printf("&& : AND\n");}
">" {printf("> : GR\n");}
">=" {printf(">= : GE\n");}
"<" {printf("< : LS\n");}
"<=" {printf("<= : LE\n");}
"," {printf("' : COMMA\n");}
":" {printf(": : COLON\n");}

[0-9]+ {ECHO; printf(" : NUM\n");}
[0-9]*[.][0-9]* {ECHO; printf(" : REAL\n");}
[']{ALPHANUM}['] {ECHO; printf(" : CHARCNST\n");}
["]{STR}*["] {ECHO; printf(" : STRCNST\n");}

"auto"			{ ECHO; printf(" : AUTO\n"); }
"break"			{ ECHO; printf(" : BREAK\n"); }
"case"			{ ECHO; printf(" : CASE\n"); }
"char"			{ ECHO; printf(" : CHAR\n"); }
"const"			{ ECHO; printf(" : CONST\n"); }
"continue"		{ ECHO; printf(" : CONTINUE\n"); }
"default"		{ ECHO; printf(" : DEFAULT\n"); }
"do"			{ ECHO; printf(" : DO\n"); }
"double"		{ ECHO; printf(" : DOUBLE\n"); }
"else"			{ ECHO; printf(" : ELSE\n"); }
"enum"			{ ECHO; printf(" : ENUM\n"); }
"extern"		{ ECHO; printf(" : EXTERN\n"); }
"float"			{ ECHO; printf(" : FLOAT\n"); }
"for"			{ ECHO; printf(" : FOR\n"); }
"goto"			{ ECHO; printf(" : GOTO\n"); }
"if"			{ ECHO; printf(" : IF\n"); }
"int"			{ ECHO; printf(" : INT\n"); }
"long"			{ ECHO; printf(" : LONG\n"); }
"register"		{ ECHO; printf(" : REGISTER\n"); }
"return"		{ ECHO; printf(" : RETURN\n"); }
"short"			{ ECHO; printf(" : SHORT\n"); }
"signed"		{ ECHO; printf(" : SIGNED\n"); }
"sizeof"		{ ECHO; printf(" : SIZEOF\n"); }
"static"		{ ECHO; printf(" : STATIC\n"); }
"struct"		{ ECHO; printf(" : STRUCT\n"); }
"switch"		{ ECHO; printf(" : SWITCH\n"); }
"typedef"		{ ECHO; printf(" : TYPEDEF\n"); }
"union"			{ ECHO; printf(" : UNION\n"); }
"unsigned"		{ ECHO; printf(" : UNSIGNED\n"); }
"void"			{ ECHO; printf(" : VOID\n"); }
"volatile"		{ ECHO; printf(" : VOLATILE\n"); }
"while"			{ ECHO; printf(" : WHILE\n"); }
[_a-zA-Z][_a-zA-Z0-9]* { ECHO; printf(" : ID\n");}

[0-9]+[a-zA-Z]+ {fprintf(stderr, "%d: Invalid integer suffix\n", num_lines);}
[0-9]*[.][0-9]*[.a-zA-Z] {fprintf(stderr, "%d: Invalid real suffix\n", num_lines);}
['][a-zA-Z0-9][a-zA-Z0-9]+['] {fprintf(stderr, "%d: Invalid character\n", num_lines);}
["][^"]*[\n] {fprintf(stderr, "%d: Unmatched <\">\n", num_lines);}
.				{fprintf(stderr, "%d: ERROR\n", num_lines);}
%%

int main()
        {
        yylex();
        printf( "# of lines = %d\n",
                num_lines );
    }
