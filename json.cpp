#include"Json.h"

void jsonObject::add(string key, jsonObject* obj)
{
	objChild.insert(pair<string, jsonObject*>(key, obj));
}


void jsonObject::add(string key, string value)
{
	sChild.insert(pair<string, string>(key, value));
}

void jsonObject::add(string key, double value)
{
	dChild.insert(pair<string, double>(key, value));
}

void jsonObject::add(string key, bool value)
{
	bChild.insert(pair<string, bool>(key, value));
}


void jsonObject::add(string key, vector<jsonObject*>objArrayvalue)
{
	objArrayChild.insert(pair<string, vector<jsonObject*>>(key, objArrayvalue));
}

void jsonObject::add(string key, vector<string>strArrayvalue)
{
	strArrayChild.insert(pair<string, vector<string>>(key, strArrayvalue));
}

void jsonObject::add(string key, vector<double>dArrayvalue)
{
	dArrayChild.insert(pair<string, vector<double>>(key, dArrayvalue));
}


bool Json::isDigit(string b)
{
	b = b.substr(0, b.find_last_of(","));
	return b.find_first_not_of("0123456789.") == string::npos;
}

bool Json::isObject(char c)
{
	return c == '{';
}

bool Json::isBool(string b)
{
	b = b.substr(0, b.find_last_of(","));
	return b == "true" || b == "false";
}

bool Json::isArray(char c)
{
	return c == '[';
}

bool Json::isString(char c)
{
	return c == '"';
}

void Json::parseArray(string line)
{
	char* token = strdup(line.c_str());
	char* str = strtok(token, "[,]");
	while (str != NULL)
	{
		cout << str << endl;
		double n = atof(str);
		if (n != 0)
		{
			nData.push_back(n);
		}
		else
		{
			stringData.push_back(str);
		}
		str = strtok(NULL, "[,]");
	}
}


void Json::parseData(jsonObject* node,vector<string>data,int index)
{
	if (node == NULL)return;
	string line = data[index];
	
	string a = line.substr(line.find_first_of("\"") + 1, line.find(":") - line.find_first_of("\"") -2 );
	string b = line.substr(line.find(":") + 1, line.find_last_of("\"") - line.find(":") -1);
	if (line == "}"||line=="},")
	{
		index++;
		if (Array)
		{
			arrayOBJ.push_back(node);
			parseData(node->getParent(), data, index);
		}
		else
		{
			if (node->getParent() != NULL)
			{
				parseData(node->getParent(), data, index);
			}
		}
	}

	if (line=="]"||line=="],")
	{
		node->add(k, arrayOBJ);
		Array = false;
		k = "";
		arrayOBJ.clear();
		index++;
		parseData(node, data, index);
	}

	if (isString(b[0]))
	{
		string str = b.substr(1, b.length() - 1);
		cout << a << " " << str << endl;
		node->add(a, str);
		index++;
		parseData(node, data, index);
	}
	else if (isDigit(b))
	{
		b = b.substr(0, b.find_last_of(","));
		double d = atof(b.c_str());
		cout << a << " " << d << endl;
		node->add(a, d);
		index++;
		parseData(node, data, index);
	}
	else if (b.length() > 1&&b[0]=='[')
	{
		parseArray(b);
		index++;
		
		if (!nData.empty())
		{
			node->add(a, nData);
			nData.clear();
		}
		if (!stringData.empty())
		{
			node->add(a, stringData);
			stringData.clear();
		}
		parseData(node, data, index);
	}
	else if (isBool(b))
	{
		b = b.substr(0, b.find_last_of(","));
		bool bl = (bool)b.c_str();
		cout << a << " " << bl << endl;
		node->add(a, bl);
		parseData(node, data, index++);
	}
	else if (isObject(b[0]))
	{
		index++;
		if (!Array)
		{
			jsonObject* j = new jsonObject(node);
			node->add(a, j);
			parseData(j, data, index);
		}
		else
		{
			jsonObject* j = new jsonObject(node);
			parseData(j, data, index);
		}
	}
	else if (isArray(b[0]))
	{
		index++;
		Array = true;
		k = a;
		parseData(node, data, index);
	}
}



void Json::readJSON()
{
	string line;
	int startSecondBracket = 0;
	int endSecondBracket = 0;
	while (getline(jsonReader, line))
	{
		line.erase(remove(line.begin(), line.end(), '\t'), line.end());
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		data.push_back(line);
	}

	parseData(root, data, 1);
	int k = 0;

}



