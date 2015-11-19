#include "lex.h"
#include <stdio.h>
#include <iostream>

using namespace std;

void expr();
void expr_prime();
void term();
void term_prime();
void factor();

void program()
{
    cout << __FUNCTION__ << endl;
    expr();

    if (match(SEMI))
    {
        advance();
    }
    else
    {
        fprintf(stderr, "ERROR, line %d: missing semicolon\n", yylineno);
    }

    if (!match(EOI))
    {
        program();
    }
}

void expr()
{
    cout << __FUNCTION__ << endl;
    term();
    expr_prime();
}

void expr_prime()
{
    cout << __FUNCTION__ << endl;
    if (match(PLUS))
    {
        advance();
        term();
        expr_prime();
    }
}

void term()
{
    cout << __FUNCTION__ << endl;
    factor();
    term_prime();
}

void term_prime()
{
    cout << __FUNCTION__ << endl;
    if (match(TIMES))
    {
        advance();
        factor();
        term_prime();
    }
}

void factor()
{
    cout << __FUNCTION__ << endl;
    if (match(NUM))
    {
        advance();
    }
    else if (match(LP))
    {
        advance();
        expr();

        if (match(RP))
        {
            advance();
        }
        else
        {
            fprintf(stderr, "ERROR, line %d: missmatched parenthesis\n", yylineno);
        }
    }
    else
    {
        fprintf(stderr, "ERROR, line %d number expected\n", yylineno);
    }
}
