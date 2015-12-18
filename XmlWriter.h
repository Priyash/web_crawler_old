#ifndef XMLWRITER_H
#define XMLWRITER_H
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include<utility>



using namespace std;

class Node
{
	vector<Node*>children;
	Node* parent=NULL;
	string nodeName;
	string startTag;
	string endTag;
	map<string, string>attr;
public:
	Node(string nodeName)
	{
		this->nodeName = nodeName;
		startTag = "<" + nodeName;
		endTag = "</" + nodeName + ">";
	}

	void setAttributes(string key, string value);
	void setText(string text);


	string getStartTag(){ return startTag; }
	string getEndTag(){ return endTag; }
	void addAttributesToStartTag();
	void addChild(Node*);
	Node* getParent(){ return parent; }

	bool hasChildren(){ return children.size() > 0 ? true : false; }
	vector<Node*>getChildren(){ return children; }
};

class XmlWriter
{
	string path;
	ofstream writer;
public:
	XmlWriter(string _path)
	{
		this->path = _path;
		writer.open(path.c_str(), ios::out);
	}

	void dump(Node* root);


};



#endif
