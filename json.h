#ifndef JSON_H
#define JSON_H

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<fstream>
using namespace std;

struct Word
{
	int id;
	string word;
	vector<int>freq;
	vector<int>docList;
};


class Json
{
	string file;
	string _path="XML_data\\";
	string path;
	string path2;
	ifstream reader;
	vector<Word>json_data;
	ofstream writer;
public:
	Json(string file)
	{
		this->file = file;
		path = _path + file;
		path2 = _path + file;
		reader.open(path.c_str(), ios::in);
	}

	void read();
	void write(vector<Word>w);
	void addWord(string w, int freq, int docID);
	vector<Word>getJsonData(){ return json_data; }

private:
	bool isExist();
};

#endif
