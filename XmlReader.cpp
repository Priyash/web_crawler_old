
/*
Author : Priyash 
Language used : C++ 11
Completed :- 27/01/2015
Application Name :- XML_PARSER 1.0.0
Environment :- Windows 8.1
Tools used :- Visual Studio 2013
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
#include<utility>
#include<map>

using namespace std;

class Element
{
	string elem;
	vector<string>out;
private:
	void ParseElement(string line);
public:
	Element(string line)
	{
		ParseElement(line);
	}
	~Element(){}
	string getElem(){ return elem; }
	string getStartTag(){ return "<" + elem + ">"; }
	string getEndTag(){ return "</" + elem + ">"; }
};

void Element::ParseElement(string line)
{
	char *ch = _strdup(line.c_str());
	char* pch = strtok(ch, "<>/ ");
	while (pch != NULL)
	{
		out.push_back(pch);
		pch = strtok(NULL, "<>/ ");
		break;
	}
	elem = out[0];
	out.clear();
}


class Attribute
{
	map<string, string>hm;
	string line;
	bool found = false;
private:
	bool isExist(string str);
	void ParseAttribute(string str);
public:
	Attribute(string line)
	{
		this->line = line;
		ParseAttribute(line);
	}
	~Attribute(){}
	string getAttribute(string str){ return hm.find(str)->first; }
	string getAttributeValue(string str)
	{
		if (!isExist(str))
		{
			return "No Such Attribute";
		}
		return hm.find(str)->second; 
	}
	void getAllAttributeAndValue();
	map<string, string> getAllAttribute(){ return hm; }
};

bool Attribute::isExist(string str)
{
	for (map<string, string>::iterator itr = hm.begin(); itr != hm.end(); ++itr)
	{
		if (itr->first == str)return true;
	}
	return false;
}

void Attribute::getAllAttributeAndValue()
{
	if (hm.size() == 0)return;
	for (auto i : hm)
	{
		cout << i.first << " : "<< i.second << endl;
	}
}

void Attribute::ParseAttribute(string str)
{
	if (str == "")return;
	size_t l1 = str.find_first_of("<");
	size_t l2 = str.find_first_of(">");
	string res = str.substr(l1 + 1, l2 - l1 - 1);

	if (res.find_first_of(" ") != string::npos)
	{
		res = res.substr(res.find_first_of(" ") + 1);
		vector<int>inverted_comma;
		vector<int>odd_inverted_comma;
		vector<int>space;
		vector<int>equal;
		for (int i = 0; i < res.length(); ++i)
		{
			if (res[i] == '\"')
			{
				inverted_comma.push_back(i);
			}
			else if (res[i] == '=')
			{
				equal.push_back(i);
			}
		}

		for (int i = 0; i < inverted_comma.size(); ++i)
		{
			if (i % 2 != 0)
			{
				odd_inverted_comma.push_back(inverted_comma[i]);
			}
		}


		//----------------------------------------------------------------------------------//
		//attribute_name
		vector<string>el;
		vector<string>val;
		if (equal.size() == 1)
		{
			el.push_back(res.substr(0, equal[0]));
			val.push_back(res.substr(inverted_comma[0] + 1, inverted_comma[1] - inverted_comma[0] - 1));
		}
		else
		{
			el.push_back(res.substr(0, equal[0]));
			for (int i = 0; i < equal.size() - 1; ++i)
			{
				el.push_back(res.substr(odd_inverted_comma[i] + 2, equal[i + 1] - odd_inverted_comma[i] - 2));
			}

			//attribute_value

			for (int i = 0; i < inverted_comma.size(); i = i + 2)
			{
				val.push_back(res.substr(inverted_comma[i] + 1, inverted_comma[i + 1] - inverted_comma[i] - 1));
				if (i + 1 == inverted_comma.size() - 1)break;
			}
		}


		for (int i = 0; i < el.size(); ++i)
		{
			hm.insert(pair<string, string>(el[i], val[i]));
		}
	}
	else
	{
		return;
	}
}




class Text
{
	int index;
	vector<string>out;
	int finalIndex = 0;
	string t;
private:
	void extractText();
public:
	Text(int index,vector<string>out)
	{
		this->index = index;
		this->out = out;
		extractText();
	}
	int getFinalIndex(){ return finalIndex; }
	string getText(){ if (t == ""){ return "No Text"; } return t; }
};

void Text::extractText()
{
	if (index == -1)return;
	string line = out[index];
	line.erase(0, line.find_first_not_of(' '));//transfrom from "   some text" to "some text"(left trimming basically
	string res="";
	size_t f1 = line.find_first_of(">");//we want to read the data between <element>some text</element>or<element>some text....
	//if there is some element such as <element> then we have to check the text data is there or not we do 
	//this by checking the location of f1 and 1 if there is no text left then the string of loc of f1+1 will empty

	if (f1 == string::npos)
	{
		return;
	}
	//find the </element>'s / symbol 
	//if found
	size_t f2 = line.find("/");
	
	if (f2 != string::npos)
	{
		res = line.substr(f1 + 1, f2 - f1 - 2);
		t = res;
		return;
	}
	//if not found
	else
	{
		res.append(line.substr(f1 + 1));
		index++;
		string str = "";
		for (unsigned int i = index; i < out.size(); i++)
		{
			finalIndex++;
			str = out[i];
			str = str.erase(0, str.find_first_not_of(' '));
			if ((str.find("<") != string::npos || str.find(">") != string::npos || str.find("/") != string::npos) && str[0] == '<')
			{
				return;
			}
			if (str.find("</") != string::npos)
			{
				str = str.substr(0, str.find("</"));
				res.append(str.substr(0, str.find("</")));
				res.append(str);
				t = res;
				break;
			}	
		}
	}
}

//each element here is considered as a Node which has element name,attribute name and values,text
class Node
{
	Element* elem;
	Attribute* attr;
	Text* txt;
	vector<Node*>children;
	Node* parent;
	vector<string>dummy;

public:
	Node(Element *elem=NULL, Attribute* attr=NULL, Text* txt=NULL,Node* parent=NULL)
	{
		this->elem = elem;
		this->attr = attr;
		this->txt = txt;
		this->parent = parent;
	}
	//Parse element from a xml line
	Element* getNodeElement()
	{
		if (elem == NULL)return new Element("");

		return elem;
	}
	//parse attribute name and value from xml line if exist
	Attribute* getNodeAttribute()
	{
		if (attr == NULL)return new Attribute("");

		return attr;
	}
	//parse text data from an xml line if exist.
	Text* getNodeText()
	{
		if (txt == NULL)return new Text(-1, dummy);

		return txt;
	}


	//child node functionality
	void addChild(Node*);
	vector<Node*>getChildren(){ return children; }
	Node* getParent(){ return parent; }
	Node* findChild(string elem, string attr,string value);
	Node* findChild(string elem);
	Node* findChild(Node* t);
	void RemoveChild(Node*);
};

void Node::RemoveChild(Node* n)
{
	auto itr = children.erase(remove(children.begin(), children.end(), n));

}

Node* Node::findChild(Node* n)
{
	auto itr = find_if(children.begin(), children.end(), [n](Node* t)->bool{return n->getNodeElement()->getElem() == t->getNodeElement()->getElem(); });
	if (itr == children.end())
	{
		return NULL;
	}

	return *itr;
}

Node* Node::findChild(string elem,string attr_name,string value)
{
	auto itr = find_if(children.begin(), children.end(), [elem,attr_name,value](Node* n)->bool
	{
		return n->getNodeElement()->getElem() == elem &&
			n->getNodeAttribute()->getAttributeValue(attr_name) == value;

	});


	if (itr == children.end())
	{
		return NULL;
	}

	return *itr;
}

Node* Node::findChild(string elem)
{
	auto itr = find_if(children.begin(), children.end(), [elem](Node* n)->bool
	{
		return n->getNodeElement()->getElem() == elem;

	});

	if (itr == children.end())
	{
		return NULL;
	}

	return *itr;
}

void Node::addChild(Node* n)
{
	children.push_back(n);
}


//XML class
class XML
{
	string version;
	ifstream reader;
	string fileName;
	vector<string>data;
	string encodeType;
	string versionType;
	Node* root;
	vector<Node*>out;
private:
	void LoadData();
	void findRoot();
	void getXMLHeaderInfo();
	void Build(Node*,int i);
	Node* Find(Node*, string elemName, string attr_name, string value);
	void FindElement(Node*, string elemName);
	
	
public:
	XML(string fileName)
	{
		this->fileName = fileName;
		reader.open(fileName, ios::in);
		LoadData();
		findRoot();
		getXMLHeaderInfo();
	}
	~XML(){}
	string getXMLVersion()
	{ 
		if (versionType == "")
		{
			return "No info on Version ";
		}

		return versionType;
	}
	string getEncodingType()
	{ 
		if (encodeType == "")
		{
			return "No info on Encoding";
		}

		return encodeType;
	}
	Node* getRoot(){ return root; }
	void Build(){ Build(root,2); }
	void Sub_Build(Node* n, string endTag,int i);
	Node* Find(string elemName, string attr_name, string value){ return Find(root, elemName, attr_name, value); }
	void FindElement(string elemName){ FindElement(root,elemName); }
	vector<Node*>getElementNode(){ return out; };
	//debugging purpose whether to see data is properly fetched or not.
	/*void printALL()
	{
		for (int i = 0; i < data.size(); i++)
		{
			cout << "data["<<i<<"] : "<<data[i] << endl;
		}
	}*/
};

//fetch the element tag and corresponding info and grouped into a container.
void XML::FindElement(Node*n,string elemName)
{
	vector<Node*>children = n->getChildren();
	for (auto i : children)
	{
		if (i->getNodeElement()->getElem() == elemName)
		{
			out.push_back(i);
		}
		else
		{
			FindElement(i, elemName);
		}
	}
	return;
}

//suppose there is a multiple identical tag , to identify a specific tag among them we use this module
Node* XML::Find(Node* n,string elemName, string attr_name, string value)
{
	vector<Node*>f = n->getChildren();
	for (auto i : f)
	{
		if (i->getNodeElement()->getElem() == elemName)
		{
			if (i->getNodeAttribute()->getAttributeValue(attr_name) == value)
			{
				return i;
			}
		}
		else
		{
			vector<Node*>child = i->getChildren();
			for (auto j : child)
			{
				if (j->getNodeElement()->getElem() == elemName)
				{
					if (j->getNodeAttribute()->getAttributeValue(attr_name) == value)
					{
						return j;
					}
				}
			}
		}
	}

	return NULL;
}

//This function is doing the heavy lifting 
//Mechanism :- Its pulling the root tag and corresponding sub-root tag and its children and mapped
//into a n-ary tree structure ,from there we can simple find the tag and info we want to query
void XML::Build(Node* n,int i)
{
	if (i == data.size() - 1)return;
	string line = data[i];
	line.erase(0, line.find_first_not_of(' '));
	if (line.find("/") == string::npos)
	{
		Node* temp = new Node(new Element(line), new Attribute(line), NULL, n);
		string endTg = temp->getNodeElement()->getEndTag();
		i++;
		n->addChild(temp);
		Sub_Build(temp, endTg, i);
	}
	else
	{
		Build(n->getParent(),++i);
	}
}

//core_mechanism
void XML::Sub_Build(Node* temp,string endTag, int i)
{
	int pos = 0;
	bool hasChild = false;
	for (unsigned int j = i; j < data.size()-1;)
	{
		string ln = data[j];
		string _next = data[j + 1];
		ln.erase(0, ln.find_first_not_of(' '));
		_next.erase(0, _next.find_first_not_of(' '));
		if (ln == endTag)
		{
			Build(temp->getParent(), ++j);
			break;
		}
		if (ln.find_last_of("/") == string::npos)
		{
			if (_next.find_first_of("<") != string::npos&&_next[0]=='<')
			{
				hasChild = true;
			}
		}
		Text* txt = new Text(j, data);
		pos = txt->getFinalIndex() + 1;
		j = j + pos;
		Node* node = new Node(new Element(ln), new Attribute(ln), txt, temp);
		if (node->getNodeElement()->getEndTag() == ln)
		{
			temp = temp->getParent();
			hasChild = false;
			continue;
		}
		temp->addChild(node);
		if (hasChild)
		{
			Sub_Build(node, node->getParent()->getNodeElement()->getEndTag(), --j);
			break;
		}
		
	}
}

//information about xml version and encoding type
void XML::getXMLHeaderInfo()
{
	string line = data[0];
	vector<int>occurence;
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] == '"')
		{
			occurence.push_back(i);
		}
	}

	if (occurence.size() == 0)
	{
		versionType == "";
	}
	else
	{
		versionType = line.substr(occurence[0] + 1, occurence[1] - occurence[0] - 1);
	}

	if (occurence.size()==2)
	{
		encodeType = "";
	}
	else
	{
		encodeType = line.substr(occurence[2] + 1, occurence[3] - occurence[2] - 1);
	}
}
//finds the root tag
void XML::findRoot()
{
	root = new Node(new Element(data[1]),new Attribute(data[1]));
}  
//loading the entire data into memory from memory we parse the data and tags
void XML::LoadData()
{
	string line;
	while (getline(reader, line))
	{
		data.push_back(line);
	}
}


int main()
{
	XML* xml = new XML("F:\\xml\\book.xml");
	xml->Build();
	xml->FindElement("genre");
	vector<Node*>v = xml->getElementNode();
	for (auto i : v)
	{
		cout<<i->getNodeText()->getText()<< endl;
		//cout << i->getNodeAttribute()->getAttributeValue("id") << endl;
	}

	return 0;

}
