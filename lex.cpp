#include "lex.h"
#include <stdio.h>
#include <ctype.h>
#include <iostream>

using namespace std;

char *yytext;
int yyleng = 0;
int yylineno = 0;

char lex()
{
    static char input_buffer[128] = "";
    yytext = input_buffer;
    char *current;

    // current point to the \0.
    current = yytext + yyleng;

    while (1)
    {
        // loop while current point to the \0.
        while (!*current)
        {
            current = input_buffer;

            // read from stdin.
            if (!gets(input_buffer))
            {
                // if read error
                *current = '\0';
                return EOI;
            }

            // new line.
            ++yylineno;

            // skip whitespaces
            while (isspace(*current))
            {
                ++current;
            }
        }

        // iterate the string pointed by current
        for (; *current; ++current)
        {
            yytext = current;
            yyleng = 1;

            switch (*current)
            {
            case EOF:
                cout << "[lex: EOF] ";
                return EOI;

            case ';':
                cout << "[lex [SEMI] ";
                return SEMI;

            case '+':
                cout << "[lex: PLUS] ";
                return PLUS;

            case '*':
                cout << "[lex: TIMES] ";
                return TIMES;

            case '(':
                cout << "[lex: LP] ";
                return LP;

            case ')':
                cout << "[lex: RP] ";
                return RP;

            case '\n':
            case '\t':
            case ' ':
                break;

            default:
                if (!isalnum(*current))
                {
                    fprintf(stderr, "Ignoring illegal input <%c>\n", *current);
                }
                else
                {
                    while (isalnum(*current))
                    {
                        ++current;
                    }

                    // recalculate the length
                    yyleng = current - yytext;
                    string l(yytext, yyleng);
                    cout << "[lex: " << l << "] ";
                    return NUM;
                }

                break;
            }
        }
    }
}

static int lookAhead = -1;

int match(int token)
{
    if (lookAhead == -1)
    {
        lookAhead = lex();
    }

    return token == lookAhead;
}

void advance()
{
    lookAhead = lex();
}
