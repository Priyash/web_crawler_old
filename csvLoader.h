#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

class CSVLoader
{
	ifstream reader;
	long long counter = 0;
	long long c = 0;
	string file;
	vector<string>v;
	vector<string>label;
	string** mat;
public:
	CSVLoader(string file)
	{
		ifstream read;
		string l;
		this->file = file;
	}
	~CSVLoader()
	{
		v.clear();
		label.clear();
		mat = nullptr;
		file = nullptr;
		reader.clear();
		reader.close();

	}
	void Load();
	long long getRow(){ return counter; }
	//vector<string>getData(){ return v; }
	long long getCol(){ return c; }
	string** loadData();
	//FOR NON-HOMOGENOUS MATRIX
	vector<string>getData();
};





