#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
using std::string;
using std::cout;
using std::endl;
using std::vector;
struct Record
{
	string _word;
	int _frequency;
    Record()
    :_word("")
    ,_frequency(1)
    {

    }
    void print(){
        cout << _word <<" "<<_frequency <<endl;
    }
};
class Dictionary
{
public:
    static Dictionary* createInstance();
    void read(const std::string &filename);
    void store(const std::string &filename);
private:
    vector<Record> _dict;
};
inline
bool cmp(const Record & lhs,const Record & rhs){
    return lhs._word < rhs._word;
}
#endif
