#include "TextQuery.hh"
void TextQuery::readFile(const string filename){
    ifstream ifs(filename);
    if(!ifs){
        cerr << "ifstream open " << filename << " failed"<< endl;
        return;
    }

    string line;
    //初始化为0，后续输出的时候＋1
    size_t lineNumber = 0;
    while(getline(ifs,line)){
        //把一行的原本信息保存到_lines中
        _lines.push_back(line);
        //对读取到的一行的内容进行处理
        dealLine(line);

        //分解成单词
        istringstream iss(line);
        string word;
        while(iss >> word){
            //统计单词和词频
            ++_dict[word];

            //记录单词和行号
            _wordNumbers[word].insert(lineNumber);
        }
        ++lineNumber;
    }
}
void TextQuery::dealLine(string & line){
    //单词和符号连接，使用空格符替换符号
    for(auto & ch : line){
        if(!isalpha(ch)){
            ch = ' ';
        }
        else if(isupper(ch)){
            ch = tolower(ch);
        }
    }
}
void TextQuery::query(string & word){
    for(auto & ch : word){
        if(!isupper(ch)){
            ch = tolower(ch);
        }
    }
    cout << "----------------------" << endl;
    int count = _dict[word];
    cout << word << " occurs " << count
        << (count > 1 ? " times":" time")
        << endl;
    auto occurLines = _wordNumbers[word];
    for(auto & num :occurLines){
        cout << "(line " << num + 1 << ") " 
            << _lines[num] << endl;
    }
    cout << "----------------------" << endl;

}

