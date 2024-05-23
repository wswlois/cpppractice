
#include <iostream>
#include "dictionary1.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main(int argc, char **argv)
{
    Dictionary dc1;
    dc1.read("The_Holy_Bible.txt");
    dc1.store("cout.txt");
    cout <<"end" << endl;
    return 0;
}

