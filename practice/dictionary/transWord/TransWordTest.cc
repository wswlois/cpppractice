#include <iostream>
#include "TransWord.hh"

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    ifstream input("file.txt");
    ifstream map_file("map.txt");
     word_transform(map_file, input);

    return 0;
}

