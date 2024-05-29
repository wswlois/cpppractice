#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
using namespace std;

class Dictionary
{
public:
    void read(const string &filename){
        ifstream ifs(filename);    

        if(!ifs){
            cerr << "ifstream open file failed!" << endl;
            return;
        }

        string line;
        while(getline(ifs,line)){
            istringstream iss(line);
            string word;
            while(iss >> word){
                //处理单词
                string newWord = dealWord(word);

                if(newWord != string()){
                    //将处理后的单词尝试插入到map中
                    ++_dict[newWord];
                }
            }
        }

        ifs.close();
    }

    string dealWord(const string & word){
        for(size_t idx = 0; idx != word.size(); ++idx){
            if(!isalpha(word[idx])){
                return string();
            }
        }
        return word;
    }


    void store(const string &filename){
        ofstream ofs(filename);
        if(!ofs){
            cerr << "ofs open file failed" << endl;
            return;
        }
        
        map<string,int>::iterator it = _dict.begin();
        for(; it != _dict.end(); ++it){
            ofs << it->first << " " << it->second << endl;
        }
        
        ofs.close();
    }
private:
    map<string,int> _dict;
};

void test0(){
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.store("dictMap.dat");
}

int main(void){
    test0();
    return 0;
}

