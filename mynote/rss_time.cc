#include <ratio>
#include <chrono>

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
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
using std::stringstream;
using std::regex;
using std::regex_replace;


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
    void dump1(const string & filename);//输出
    void dump2(const string & filename);//输出
    void dump3(const string & filename);//输出
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
    regex htmlTag("<.*?>");
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
            string description = regex_replace(descriptionElement->GetText(), htmlTag, "");
            rssItem.description = description;
        }else{
             rssItem.description = "";
        }

        if(contentElement){
            string content = regex_replace(contentElement->GetText(), htmlTag, "");
            rssItem.content = content;
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
        ofs << "<doc>\n\t<docid>" 
            << docNumber << "</docid>\n\t<title>" 
            <<ri.title << "</title>\n\t<link>" 
            << ri.link << "</link>\n\t<description>"
            << ri.description << "</description>\n\t<content>"
            << ri.content << "</content>\n</doc>\n";

    }
    ofs.close();

}

void RssReader::dump1(const string & filename)
{
    ofstream ofs(filename);
    stringstream ss;
    int docNumber = 0;
    for(auto &ri: _rss){
        ++docNumber;
        ss << "<doc>\n\t<docid>" 
            << docNumber << "</docid>\n\t<title>" 
            <<ri.title << "</title>\n\t<link>" 
            << ri.link << "</link>\n\t<description>"
            << ri.description << "</description>\n\t<content>"
            << ri.content << "</content>\n</doc>\n";

        ofs<<ss.str();
    }
    ofs.close();

}
void RssReader::dump2(const string & filename)
{
    ofstream ofs(filename);
    string str = "";
    int docNumber = 0;
    for(auto &ri: _rss){
        ++docNumber;
        str.append("<doc>\n\t<docid>").append(std::to_string(docNumber));
        str.append("</docid>\n\t<title>").append(ri.title).
            append("</title>\n\t<link>").append(ri.link).
            append("</link>\n\t<description>").append(ri.description).
            append("</description>\n\t<content>").append(ri.content).
            append("</content>\n</doc>\n");

        ofs<<str;
    }
    ofs.close();

}
void RssReader::dump3(const string & filename)
{
    ofstream ofs(filename);
    string str = "";
    int docNumber = 0;
    for(auto &ri: _rss){
        ++docNumber;
        str.append("<doc>\n\t<docid>").append(std::to_string(docNumber)).append("</docid>\n\t<title>").append(ri.title).
            append("</title>\n\t<link>").append(ri.link).
            append("</link>\n\t<description>").append(ri.description).
            append("</description>\n\t<content>").append(ri.content).
            append("</content>\n</doc>\n");

        ofs<<str;
    }
    ofs.close();

}
int main(int argc, char **argv)
{
    RssReader RR;
    RR.parseRss();
    using namespace std::chrono;
     high_resolution_clock::time_point t1 = high_resolution_clock::now();
     std::cout << "sprint action...\n";
    RR.dump("pagelib1.txt");
     high_resolution_clock::time_point t2 = high_resolution_clock::now();
     duration<double, std::milli> time_span = t2 - t1;                                                      
     std::cout << "It took me " << time_span.count() << " milliseconds.";
     std::cout << std::endl;

     t1 = high_resolution_clock::now();
     std::cout << " append action...\n";
    RR.dump2("pagelib2.txt");
     t2 = high_resolution_clock::now();
     time_span = t2 - t1;
     std::cout << "It took me " << time_span.count() << " milliseconds.";
     std::cout << std::endl;

     t1 = high_resolution_clock::now();
     std::cout << " append action...\n";
    RR.dump1("pagelib1.txt");
     t2 = high_resolution_clock::now();
     time_span = t2 - t1;
     std::cout << "It took me " << time_span.count() << " milliseconds.";
     std::cout << std::endl;

     t1 = high_resolution_clock::now();
     std::cout << " append action...\n";
    RR.dump3("pagelib3.txt");
     t2 = high_resolution_clock::now();
     time_span = t2 - t1;
     std::cout << "It took me " << time_span.count() << " milliseconds.";
     std::cout << std::endl;

    //RR.dump("../data/pagelib.txt");
    return 0;
}

