#include "lex.h"
#include <stdio.h>
#include <iostream>

using namespace std;

const char *expr();
// void expr_prime();
const char *term();
// void term_prime();
const char *factor();

const char *names[] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"};
const char **namep = names;

const char *newname()
{
    if (namep >= &names[sizeof(names) / sizeof(*names)])
    {
        fprintf(stderr, "INTERNAL ERROR, %d: expression to complex\n", yylineno);
        exit(1);
    }

    return (*namep++);
}

void freename(const char *s)
{
    if (namep > names)
    {
        *--namep = s;
    }
    else
    {
        fprintf(stderr, "INTERNAL ERROR, %d, name stack underflow\n", yylineno);
        exit(1);
    }
}

void program()
{
    cout << __FUNCTION__ << endl;

    const char *temp;

    while (!match(EOI))
    {
        temp = expr();

        if (match(SEMI))
        {
            advance();
        }
        else
        {
            fprintf(stderr, "ERROR, line %d: missing semicolon\n", yylineno);
        }

        freename(temp);
    }
}

const char *expr()
{
    cout << __FUNCTION__ << endl;

    const char *temp = term();

    while (match(PLUS))
    {
        advance();
        const char *temp1 = term();
        printf(" + %s %s %s\n", temp, temp1, temp);
        freename(temp1);
    }

    return temp;
}

// void expr_prime()
// {
//     cout << __FUNCTION__ << endl;
//     if (match(PLUS))
//     {
//         advance();
//         term();
//         expr_prime();
//     }
// }

const char *term()
{
    cout << __FUNCTION__ << endl;

    const char *temp = factor();

    while (match(TIMES))
    {
        advance();
        const char *temp1 = factor();
        printf(" * %s %s %s ", temp, temp1, temp);
        freename(temp1);
    }

    return temp;
}

// void term_prime()
// {
//     cout << __FUNCTION__ << endl;
//     if (match(TIMES))
//     {
//         advance();
//         factor();
//         term_prime();
//     }
// }

const char *factor()
{
    cout << __FUNCTION__ << endl;

    const char *temp;

    if (match(NUM))
    {
        string l(yytext, yyleng);
        printf(":= %s %s\n", l.c_str(), temp = newname());
        advance();
    }
    else if (match(LP))
    {
        advance();
        temp = expr();

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

    return temp;
}
