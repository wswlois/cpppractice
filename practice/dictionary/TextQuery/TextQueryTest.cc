
#include "TextQuery.hh"
int main(int argc, char **argv)
{
    string queryWord("the");
    
    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);
    return 0;
}
