#include "TransWord.hh"


void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = buildMap(map_file);//保存转换规则
  //  for(map<string,string>::iterator it = trans_map.begin();it!=trans_map.end();++it)
  //  {
  //      cout << it->first << " " << it->second <<endl;

  //  }
    string text;//保存每行
    while(getline(input,text))
    {
        istringstream iss(text); //读取每个单词
        string word;
        bool firstword = true;//控制是否打印空格
        while(iss >> word)
        {
            if(firstword)
                firstword = false;
            else
                cout << " ";//在单词间打印一个空格
            //transform返回它的第一个参数或其转换之后的形式
            cout << transform(word, trans_map);//打印输出
        }
        cout << endl;//完成一行的转换
    }

}

unordered_map<string,string> buildMap(ifstream &map_file)
{
    unordered_map<string,string> trans_map;//使用map数据结构保存
    string key;//要转换的单词
    string value;//替换后的内容
    //左边一行的第一个单词 右边储存剩下的内容
    while(map_file >> key && getline(map_file,value))
    {
        if(value.size() > 1)
            trans_map[key] = value.substr(1);//跳过前面空格？？
        else
            //仅抛出异常，一般这个這样不会输出吧
            throw runtime_error("no rule for " + key);
    }
    return trans_map;
}
const string & transform(const string &s,const unordered_map<string,string> &m)
{
    //核心转换部分
    auto map_it = m.find(s);//注意调用find读取，没有使用下标
                            //下标可能直接改插入那个短语？
    //如果单词出现在转换规则map中
    if(map_it != m.end())
    {
        return map_it->second;//使用替换短语
    }
    else
    {
        return s;
    }
}
