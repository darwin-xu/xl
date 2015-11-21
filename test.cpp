#include <stdio.h>
#include <iostream>

using namespace std;

bool debug = false;

void program();

int main(int argc, char *argv[])
{
    if (argc > 1 && string(argv[1]) == string("-d"))
    {
        debug = true;
    }

    program();

    return 0;
}
