#ifndef CRAWLER_H
#define CRAWLER_H
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<fstream>
#include<Windows.h>
#include<urlmon.h>
#include<regex>


//DONT FORGET TO URLMON.LIB INTO THE LINKER SECTION OTHERWISE IT WILL GIVE UNRESOLVE EXTERNAL ERROR

using namespace std;


struct URLnode
{
	string url;
	URLnode(string url):url(url){}
};



class Crawler
{
	vector<URLnode*>InitList;
	vector<URLnode*>openList;
	vector<URLnode*>closedList;
	LPCWSTR cachePath;
	string path;
public:
	Crawler()
	{
		cachePath = L"index.html";
		path = "list.txt";
	}

	//INITIAL LIST OF URL
	void InitURL();
	void downloader();
	void parseLink();
private:
	void downloader(wstring url);
	string getURL(string line);
	bool isExist(string url);
};
	


#endif
