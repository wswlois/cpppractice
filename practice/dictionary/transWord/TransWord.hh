
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

void word_transform(ifstream &map_file, ifstream &input);
unordered_map<string,string> buildMap(ifstream &map_file);
const string & transform(const string &s,const unordered_map<string,string> &m);
