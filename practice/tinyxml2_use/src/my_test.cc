#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>
#include <fstream>
#include <regex>
#include "../include/tinyxml2.h"

using namespace tinyxml2;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::cerr;
using std::ofstream;
using std::regex;


struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader();
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
 };   

RssReader::RssReader()
{

    _rss.reserve(100);

}
void RssReader::parseRss()
{
    XMLDocument doc;
    //regex r();
    RssItem rssItem;
    doc.LoadFile( "../data/coolshell.xml" );
    XMLElement* itemNode = doc.FirstChildElement( "rss" )
                            ->FirstChildElement( "channel" )
                            ->FirstChildElement( "item" );
    while(itemNode){
        XMLElement* titleElement = itemNode->FirstChildElement( "title" );
        XMLElement* linkElement = itemNode->FirstChildElement( "link" );
        XMLElement* descriptionElement = itemNode->FirstChildElement( "description" );
        XMLElement* contentElement = itemNode->FirstChildElement( "content:encoded" );
        if(titleElement){
            rssItem.title = titleElement->GetText();
        }else{
             rssItem.title = "";
        }

        if(linkElement){
            rssItem.link = linkElement->GetText();
        }else{
             rssItem.link = "";
        }

        if(descriptionElement){
            rssItem.description = descriptionElement->GetText();
        }else{
             rssItem.description = "";
        }

        if(contentElement){
            rssItem.content = contentElement->GetText();
        }else{
            continue;
        }
        _rss.push_back(rssItem);
        itemNode = itemNode->NextSiblingElement("item");

    }

    return;
}
void RssReader::dump(const string & filename)
{
    ofstream ofs(filename);
    int docNumber = 0;
    for(auto &ri: _rss){
        ++docNumber;
        ofs << "<doc>\n\t<docid>" << docNumber << "</docid>\n\t<title>" <<ri.title
            << "</title>\n\t<link>" << ri.link << "</link>\n\t<description>"
            << ri.description << "</description>\n\t<content>"
            << ri.content << "</content>\n</doc>\n";

    }
    ofs.close();

}

int main(int argc, char **argv)
{
    RssReader RR;
    RR.parseRss();
    RR.dump("../data/out/pagelib.txt");
    return 0;
}

