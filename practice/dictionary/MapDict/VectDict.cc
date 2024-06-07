#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::sort;

struct Record
{
    Record(const string &word, int frequency)
    : _word(word)
    , _frequency(frequency)
    {

    }

    string _word;
	int _frequency;
};

bool operator<(const Record &lhs, const Record &rhs)
{
    return lhs._word < rhs._word;
}
class Dictionary
{
public:
    //读文件，然后将结果存放在vector
    void read(const std::string &filename)
    {
        ifstream ifs(filename);
        /* if(!ifs.good()) */
        if(!ifs)//ifstream---->bool
        {
            cerr << "ifstream is not good" << endl;
            return;
        }

        string line;
        //对文件中的内容一行行进行处理
        while(getline(ifs, line))
        {
            
            string word;
            istringstream iss(line);
            /* while(iss >> word, !iss.eof())//cin >> word */
            while(iss >> word)//cin >> word
            {
                //hello world
                //word == hello!
                //查看word是不是合格的单词，如果不是就进行处理
                string newWord = dealWord(word);
                //将合格的单词（处理之后的单词放在vector存起来）
                insert(newWord);
            }
        }

        //将vector中的所有Record进行排序
        sort(_dict.begin(), _dict.end());

        ifs.close();
    }
    //读vector，将结果存放在另外文件中
    void store(const std::string &filename)
    {
        ofstream ofs(filename);
        if(!ofs)
        {
            cerr << "ofstream is not good" << endl;
            return;
        }

        //遍历vector，将其中内容写到文件中
        for(size_t idx = 0; idx != _dict.size(); ++idx)
        {
            ofs << _dict[idx]._word << "     "
                << _dict[idx]._frequency << endl;
        }

        ofs.close();
    }
    //如何处理单词是否合格
    string dealWord(const string &word)
    {
        for(size_t idx = 0; idx != word.size(); ++idx)
        {
            /* if(word[idx] >= 'A' && word[idx] <= 'Z') */
            //如果遍历字符串的过程中，发现字符串中有字符不是字母
            //我们就将该单词直接去掉(直接用空串进行处理)
            //hello! 
            if(!isalpha(word[idx]))
            {
                return string();
            }
        }

        return word;
    }

    void insert(const string &word)
    {
        //如果word不是合格的单词，就丢弃
        if(word == string())
        {
            return;
        }

        //将word存放到vector
        size_t idx = 0;
        for(idx = 0; idx != _dict.size(); ++idx)
        {
            if(word == _dict[idx]._word)
            {
                ++_dict[idx]._frequency;
                break;//一定要写，不写的话每次都要遍历整个vector
            }
        }

        //走到此处，就表明该单词是第一个出现
        if(idx == _dict.size())
        {
            _dict.push_back(Record(word, 1));
        }
    }
private:
	vector<Record> _dict;
};

int main(int argc, char *argv[])
{
    Dictionary dictionary;
    /* dictionary.read(argv[1]); */
    cout << "before reading..." << endl;
    time_t beg = time(NULL);
    dictionary.read("The_Holy_Bible.txt");
    time_t end = time(NULL);
    cout << "time: " << (end - beg) << "s" << endl;
    cout << "aftre reading..." << endl;
    /* dictionary.store("dictMap.dat"); */
    dictionary.store("dictVec.dat");
    return 0;
}


