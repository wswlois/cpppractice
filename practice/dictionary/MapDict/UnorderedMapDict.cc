#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

class Dictionary
{
public:
    void read(const string &filename)
    {
        ifstream ifs(filename);    

        if(!ifs){
            cerr << "ifs open "<< filename <<" failed!" << endl;
            return;
        }

        string line;
        while(getline(ifs,line))
        {
            istringstream iss(line);
            string word;
            while(iss >> word)
            {
                //处理单词
                string newWord = dealWord(word);

                if(newWord != string())
                {
                    //将处理后的单词尝试插入到map中
                    ++_dict[newWord];
                }
            }
        }

        ifs.close();
    }


    void store(const string &filename){
        ofstream ofs(filename);
        if(!ofs){
            cerr << "ofs open file failed" << endl;
            return;
        }
        
        unordered_map<string,int>::iterator it = _dict.begin();
        for(; it != _dict.end(); ++it){
            ofs << it->first << " " << it->second << endl;
        }
        
        ofs.close();
    }
private:
    string dealWord(const string & word){
        for(size_t idx = 0; idx != word.size(); ++idx)
        {
            if(!isalpha(word[idx]))
            {
                return string();
            }
        }
        return word;
    }
private:
    unordered_map<string,int> _dict;
};

void test0(){

    cout << "before reading..." << endl;
    Dictionary dict;
    time_t beg = time(NULL);
    dict.read("The_Holy_Bible.txt");
    time_t end = time(NULL);
    cout << "time: " << (end - beg) << "s" << endl;
    cout << "aftre reading..." << endl;
    dict.store("dictUnorderedMap.dat");

}

int main(void){
    test0();
    return 0;
}

