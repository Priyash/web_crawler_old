#ifndef HTML
#define HTML
#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<exception>
#include<regex>
#include<sstream>

using namespace std;

class HTML_PARSER
{
	string path;
	ifstream reader;
	ofstream writer;
	string file;
	string html_path;
	vector<string>html_data;
	vector<string>text;
	vector<string>words;
public:
	HTML_PARSER(string file)
	{
		path = "C:\\Users\\PRIYASH_11\\Desktop\\XML data\\";
		this->file = file;
		html_path = path + file;
		reader.open(html_path.c_str(), ios::in);
		string file2 = "out2.txt";
		writer.open(path + file2, ios::out);
	}

	~HTML_PARSER()
	{
		reader.clear();
		reader.close();
		path.clear();
		file.clear();
		html_path.clear();
	}

	void loadData();
	void parseText();
	void findTEXT(string s);
	void toWord();
private:
	bool isHTML();
	void cleanUp();
};


#endif
