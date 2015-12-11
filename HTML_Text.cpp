#include"HTML.h"

bool HTML_PARSER::isHTML()
{
	string s = html_path;
	s = s.substr(s.find_last_of(".") + 1);
	if (s == "html" || s == "HTML")return true;

	return false;
}


//THIS MODULE WILL LOAD ALL THE DATA OF AN HTML AND CLEAN IT I.E REMOVE SPACES IF ANY
void HTML_PARSER::loadData()
{
	try
	{
		if (!isHTML())throw;
		string line;
		while (getline(reader, line))
		{
			if (line == "")continue;
			if (line[0] == '\t')
			{
				line = line.erase(line.find_last_not_of(" \t\f\v\n\r") + 1);
			}
			else if (line[0] == ' ')
			{
				size_t n = line.find_first_of("<");
				if (n == string::npos)continue;
				line = line.substr(n);

			}

			//COMMENTS WOULD BE GET FETCHED INCLUDING WHATS INSIDE <SCRIPT> IN BETWEEN </SCRIPT>
			if (line[0] == '<'&&line[1] == '!')
			{
				continue;
			}
			if (line.find("<script>") != string::npos)
			{
				continue;
			}

			html_data.push_back(line);
		}

		int k = 0;
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}
}


void HTML_PARSER::findTEXT(string s)
{
	smatch sm;
	string exp = ">([^<]*.?)<";
	regex e(exp);
	int index = 1;
	while (regex_search(s, sm, e))
	{

		for (auto x : sm)
		{
			if (index % 2 == 0 && x.length() != 0)
			{
				//cout << x << endl;
				text.push_back(x.str());
			}
			index++;
		}
		s = sm.suffix().str();
	}
}

//THIS MODULE WILL PARSE ALL THE WORDS FROM THE HTML FILE
void HTML_PARSER::parseText()
{
	for (auto i : html_data)
	{
		findTEXT(i);
	}
	cleanUp();
}

void HTML_PARSER::cleanUp()
{
	for (int i = 0; i < text.size();++i)
	{   
		string s = text[i];
		if (s[0]==' '||s[0]=='*'||s[0]=='&')
		text.erase(remove(text.begin(), text.end(), s), text.end());
	}

	for (auto i : text)
	{
		writer << i << endl;
	}


	int k = 0;
}
