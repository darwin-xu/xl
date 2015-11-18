#define EOI   0
#define SEMI  1
#define PLUS  2
#define TIMES 3
#define LP    4
#define RP    5
#define NUM   6

extern char *yytext;
extern int yyleng;
extern int yylineno;

char lex();
int match(int token);
void advance();
