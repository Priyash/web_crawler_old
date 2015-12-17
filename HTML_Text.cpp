#include"HTML.h"

//CHECKING WHETHER THE FILE IS HTML OR NOT
bool HTML_PARSER::isHTML()
{
	string s = html_path;
	s = s.substr(s.find_last_of(".") + 1);
	if (s == "html" || s == "HTML")
	{
		s = "html";
		return true;
	}
	return false;
}


//THIS MODULE WILL LOAD ALL THE DATA OF AN HTML AND CLEAN IT I.E REMOVE SPACES IF ANY
void HTML_PARSER::loadData()
{
	try
	{
		if (!isHTML())throw false ;
		string line;
		bool found = false;
		while (getline(reader, line))
		{
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

			//REMOVING COMMENTS WHICH WOULD BE GET FETCHED INCLUDING WHATS INSIDE <SCRIPT> IN BETWEEN </SCRIPT>
			if (line[0] == '<'&&line[1] == '!'&&line[2]=='-')
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
	catch (bool v)
	{
		cerr << "Not an HTML FILE" << endl;
	}
}

//USING THE REGULAR EXPRESSION TO READ IN BETWEEEN TWO TAGS
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

//CLEANING THE UNCESSESARY SYMBOLS 
void HTML_PARSER::cleanUp()
{
	for (int i = 0; i < text.size();++i)
	{   
		string s = text[i];
		if (s.find("\\n") != string::npos || (s[0]==':'&&s.size()==1)||s.find("\\t") != string::npos||s.find("&nbsp") != string::npos || (s[0]==' '&&s.size()==1) || s.find("function") != string::npos || s.find("=") != string::npos || (s[0] == '#') || s[0] == '<' || s[0] == '>' || (s[0] == '.'&&s.length()==1) || s.find("<style ") != string::npos)
		{
			text.erase(remove(text.begin(), text.end(), s), text.end());
			i--;
		}
	}

	for (auto i : text)
	{
		writer << i << endl;
	}

}

//THIS MODULE IS USED TO CONVERT THE LINE INTO SET OF WORDS
//THIS PART HAS TO BE WRITTTEN GLOBALLY
void HTML_PARSER::toWord()
{
	ifstream r;
	string _path = "C:\\Users\\PRIYASH_11\\Desktop\\XML data\\";
	string path2 = path + file2;
	r.open(path2.c_str(), ios::in);
	string line2 = "";
	char* token;
	
	while (getline(r, line2))
	{
		line2.erase(remove_if(line2.begin(), line2.end(), [](char s)->bool{return s == '.'; }));

		char* dup = strdup(line2.c_str());
		token = strtok(dup, " ,-:&#;|?/()<>*@0123456789%\"\'\t\n\r_{}[]");
		while (token!=NULL)
		{
			//words.push_back((string)token);
			if (strlen(token) > 2)
			{
				dict[(string)token]++;
			}
			token = strtok(NULL, " ,-:&#;|?/()<>*@0123456789%\"\'\t\n\r_{}[]");
		}
		
		free(dup);
	}

	ofstream w;
	string path3 = _path + "Word.txt";
	w.open(path3.c_str(), ios::out);

	for (auto i : dict)
	{
		w << i.first<<","<<i.second<< endl;
	}
	//FREE UP RESOURCES
	r.clear();
	r.close();
	file.clear();
	_path.clear();
	path.clear();
	line2.clear();
	w.close();

}
