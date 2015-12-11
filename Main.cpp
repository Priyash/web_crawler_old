#include<iostream>
#include"Crawler.h"

using namespace std;


int main()
{

	Crawler* crawler = new Crawler();
	crawler->InitURL();
	//crawler->downloader();
	crawler->parseLink();
        //HOW TO CALL HTML_Text MODULE
        /*
        
        string file = "Search.html";
	HTML_PARSER* hp = new HTML_PARSER(file.c_str());
	hp->loadData();
	hp->parseText();
        
        */

	return 0;
}
