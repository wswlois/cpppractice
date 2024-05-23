#include "dictionary1.h"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;
using std::cerr;

void Dictionary::read(const std::string &filename)
{
    ifstream ifs;
    ifs.open(filename);
    if(!ifs)
    {
        cerr << "open" << filename << "fail" <<endl;
    }
    string line;
    Record rd;
    _dict.reserve(100);
    while(getline(ifs,line))
    {
        istringstream iss(line);
        int flag = 1;
        while(iss >> rd._word){
            for (auto & ele: _dict){
                if(ele._word == rd._word)
                {
                    ++ele._frequency;
                    flag = 0;
                }
            }
            if(flag == 1){
                _dict.push_back(rd);
            }
            flag = 1;
        }
    }
    sort(_dict.begin(),_dict.end(),cmp);
    for (auto & ele:_dict){
        ele.print();
    }
}

void Dictionary::store(const std::string &filename)
{
    ofstream ofs(filename);
    ostringstream oss;
    for (auto & ele:_dict){
        oss << ele._word << " " <<  ele._frequency << endl;
    }
    ofs << oss;
    ofs.close();
}

