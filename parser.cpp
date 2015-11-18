#include "lex.h"
#include <stdio.h>

void expr();
void expr_prime();
void term();
void term_prime();
void factor();

void program()
{
    expr();

    if (match(SEMI))
    {
        advance();
    }
    else
    {
        fprintf(stderr, "%d: missing semicolon\n", yylineno);
    }

    if (!match(EOI))
    {
        program();
    }
}

void expr()
{
    term();
    expr_prime();
}

void expr_prime()
{
    if (match(PLUS))
    {
        advance();
        term();
        expr_prime();
    }
}

void term()
{
    factor();
    term_prime();
}

void term_prime()
{
    if (match(TIMES))
    {
        advance();
        factor();
        term_prime();
    }
}

void factor()
{
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
            fprintf(stderr, "%d: missmatched parenthesis\n", yylineno);
        }
    }
    else
    {
        fprintf(stderr, "%d number expected\n", yylineno);
    }
}
