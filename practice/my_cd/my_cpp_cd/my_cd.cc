#include <iostream>
#include <stack>
#include <string>
#include <cstring>

using std::cout;
using std::endl;
using std::stack;
using std::string;

int main(int argc, char **argv)
{
    stack<string> pathStac;
    string fullPath = "/usr/include/dir1/dir2";
    size_t found = fullPath.rfind('/');

    cout << "Hello world" << endl;
    return 0;
}

