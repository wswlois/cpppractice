#include "dictionary3.h"
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
        return;
    }
    string line;
    Record rd;
    _dict.reserve(1000);
    while(getline(ifs,line))
    {
        istringstream iss(line);
        //看单词是否找到
        int flag = 1;
        while(iss >> rd._word){
            //判断单词是否合法
            /* for(size_t idx = 0; idx != rd._word.size(); ++idx) */
            for(char c:rd._word)
            {
                if(!isalpha(c)){
                    goto end;
                }
            }
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
end:
            flag = 1;
        }
    }
    sort(_dict.begin(),_dict.end(),cmp);
    /* for (auto & ele:_dict){ */
    /*     ele.print(); */
    /* } */
}

void Dictionary::store(const std::string &filename)
{
    ofstream ofs(filename);
    for (auto & ele:_dict){
    ofs << ele._word << " " <<  ele._frequency << endl;
    }
    ofs.close();
}

