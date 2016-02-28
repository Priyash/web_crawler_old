#ifndef JSON_H
#define JSON_H
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<utility>
#include<fstream>

using namespace std;


class jsonObject
{
	jsonObject* parent;
	unordered_multimap<string, jsonObject*>objChild;
	unordered_multimap<string, string>sChild;
	unordered_multimap<string, double>dChild;
	unordered_multimap<string, bool>bChild;
	//ARRAY OF JSON CAN CONSIST OBJECT OR BOOLEAN OR NUMBER OR STRING
	unordered_multimap<string, vector<jsonObject*>>objArrayChild;
	unordered_multimap<string, vector<string>>strArrayChild;
	unordered_multimap<string, vector<double>>dArrayChild;
	//unordered_map<string, vector<bool>>boolArrayChild;

public:
	jsonObject(jsonObject* node)
	{
		parent = node;
	}
	~jsonObject()
	{

	}

	void add(string, jsonObject*);
	void add(string, string);
	void add(string, double);
	void add(string, bool);
	void add(string, vector<jsonObject*>);
	void add(string, vector<string>);
	void add(string, vector<double>);
	//void add(string, vector<bool>);
	jsonObject* getParent(){ return parent; }

	
    
};




class Json
{
	jsonObject* root;
	string filePath;
	string file;
	string path;
	ifstream jsonReader;
	vector<string>data;
	bool Array;
	vector<jsonObject*>arrayOBJ;
	string k;
	vector<double>nData;
	vector<string>stringData;
public:
	Json(string file)
	{
		filePath = "C:\\Users\\PRIYASH\\Documents\\Visual Studio 2013\\Projects\\JsonParser\\Data\\";
		path = filePath + file;
		jsonReader.open(path.c_str(), ios::in);
		root = new jsonObject(nullptr);
		Array = false;
	}

	void readJSON();

	~Json(){}

private:
	bool isDigit(string b);
	bool isBool(string );
	bool isObject(char c);
	bool isArray(char);
	bool isString(char c);
	void parseArray(string b);
	void parseData(jsonObject* node,vector<string>data,int index);

};


#endif
