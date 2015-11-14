#include"Crawler.h"


//INITIAL LIST OF URL WHICH IS FETCHED BY THIS MODULE
void Crawler::InitURL()
{
	ifstream reader;
	string line;
	reader.open(path.c_str(), ios::in);
	while (getline(reader, line))
	{
		InitList.push_back(new URLnode(line.c_str()));
	}
	reader.clear();
	reader.close();
	line.clear();
}

void Crawler::downloader()
{
	for (auto i : InitList)
	{
		wstring ws(i->url.begin(), i->url.end());
		downloader(ws);
	}
}


//THIE MODULE WILL DOWNLOAD THE WEBPAGE IN THE FORM OF HTML FORMAT 
void Crawler::downloader(wstring url)
{
	CoInitialize(NULL);
	//CONVERSION OF WSTRING FORMAT TO LPCWSTR FORMAT 
	LPCWSTR _url = url.c_str();
	//FUNCTION CALL FOR DOWNLOADING THE WEBPAGE FROM THE GIVEN URL
	HRESULT result = URLDownloadToFileW(NULL, _url,cachePath, 0, NULL);
	if (SUCCEEDED(result))
	{
		cout << "FILE DOWNLOAD COMPLETE" << endl;
	}
	else
	{
		cout << "FILE DOWNLOAD ERROR" << endl;
	}
}


bool Crawler::isExist(string url)
{
	auto itr = find_if(closedList.begin(), closedList.end(), [url](URLnode* node)->bool{return url == node->url; });
	if (itr != closedList.end())
	{
		return true;
	}
	return false;
}


//THIS MODULE WILL EXTRACT THE LINK FROM THE HTML TAG AND SAVE THE STRING INTO A CONTAINER
string Crawler::getURL(string line)
{
	//FINAL REGEX FOR EXTRACTING THE URL LINK FROM THE HTML TAG
	string reg = "<a\\s[^>]*href=\"([^\"]*)\"[^>]*>";
	regex e(reg);
	smatch sm;
	string res;
	while (regex_search(line, sm, e))
	{
		int i = 0;
		for (auto s : sm)
		{
			i++;
			if (i % 2 == 0&&!isExist(s))
			{
				cout << s << endl;
				string st = s.str();
				openList.push_back(new URLnode(st));
				res = s;
			}
			else continue;
		}
		line = sm.suffix().str();
	}
	int k = 0;
	return res;
}

//THIS MODULE WILL READ THE DOWNLOADED HTML PAGE LINE BY LINE 
void Crawler::parseLink()
{
	ifstream reader;
	wstring _path = cachePath;
	string _temp_path = string(_path.begin(), _path.end());
	reader.open(_temp_path, ios::in);
	_path.clear();
	string line;
	while (getline(reader,line))
	{
		
		string url = getURL(line);

	}
	
}
