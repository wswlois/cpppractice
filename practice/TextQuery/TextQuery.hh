#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::set;
using std::map;
using std::ifstream;
using std::istringstream;
using std::cerr;

class TextQuery
{
public:
    TextQuery(){
        _lines.reserve(107);
    }
    //读取文件，处理内容，将需要的信息读取
    void readFile(const string filename);
    //处理一行的内容
    void dealLine(string & line);
    //查找单词
    void query(string & word);
private:
    //把每一行的原始信息储存下来
    vector<string> _lines;
    //单词和行号
    map<string,set<int>> _wordNumbers;
    //单词和词频
    map<string,int> _dict;
};
