#include"Json.h"


bool Json::isExist()
{
	if (reader.good())
	{
		return true;
	}
	reader.close();
	return false;
}

void Json::read()
{
	string line;
	string rootWord = "";
	bool found = false;
	Word w;	
	
	string prev = "";
	while (getline(reader, line))
	{
		if (line == "")continue;
		line = line.erase(0, line.find_first_not_of(' '));
		line = line.erase(0, line.find_first_not_of('\t'));
		if (line == "]")
		{
			found = false;
			continue;
		}
		if (line == "{")
		{
			found = true;
			continue;
		}
		else if ((line == "},"||line=="}")&&found)
		{
			found = false;
			json_data.push_back(w);
			w.freq.clear();
			w.docList.clear();
			continue;
		}


		size_t n = line.find(":");
		if (n != string::npos)
		{
			if (rootWord == "")
			{
				string s = line.substr(n + 1);
				if (s[0] == ' ')
				{
					s = s.substr(1);
				}

				if (s == "[")
				{
					rootWord = line.substr(1, n - 2);

				}
			}
			else
			{
				
				if (found)
				{

					int index = 0;
					if (prev == "Freq"||prev=="docList")
					{
						prev = "";
					}
					
					char* d = strdup(line.c_str());
					char* t = strtok(d, " \t:\"[],");
					while (t != NULL)
					{
						string s = (string)t;
						if (prev == "id")
						{
							w.id = atoi(t);
						}
						else if (prev == "Word")
						{
							w.word = (string)t;
						}
						else if (prev == "Freq")
						{
							w.freq.push_back(atoi(t));
							prev = "Freq";
							t = strtok(NULL, " \t:\"[],");
							continue;
						}
						else if (prev == "docList")
						{
							w.docList.push_back(atoi(t));
							prev = "docList";
							t = strtok(NULL, " \t:\"[],");
							continue;
						}

						prev = s;
						t = strtok(NULL, " \t:\"[],");
					}
				}
			}
		}
	}
}

void Json::write(vector<Word>w)
{
	writer.open(path2.c_str(), ios::out);
	string startTag = "{";
	string endTag = "}";
	string root = "\"Words\": [";
	string blockStartTag = "{";
	string blockEndTag = "}";
	string arrayEndTag = "]";

	writer << startTag << endl;
	writer <<"\t"<< root << endl;
	
	for (int i = 0; i < w.size();i++)
	{
		writer <<"\t\t"<< blockStartTag << endl;
		writer << "\t\t\t\"id\": " << w[i].id <<","<< endl;
		writer << "\t\t\t\"Word\": " <<"\""+w[i].word +"\""<< "," << endl;
		writer << "\t\t\t\"Freq\": [";
		int n1 = w[i].freq.size();
		for (int j = 0; j < n1 ;j++)
		{
			if (j == (n1 - 1))
			{
				writer << w[i].freq[j];
			}
			else
			{
				writer << w[i].freq[j] << ",";
			}
		}

		writer << "]," << endl;

		writer << "\t\t\t\"docList\": [";
		int n2 = w[i].docList.size();
		for (int j = 0; j <n2;j++)
		{
			if (j == (n2 - 1))
			{
				writer << w[i].docList[j];
			}
			else
			{
				writer << w[i].docList[j] << ",";
			}
		}

		writer << "]" << endl;
		
		if (i == (w.size() - 1))
		{
			writer <<"\t\t"<< blockEndTag<< endl;
		}
		else
		{
			writer << "\t\t" << blockEndTag << "," << endl;
		}
	}

	writer <<"\t"<< arrayEndTag << endl;
	writer << endTag << endl;
	writer.close();

}


void Json::addWord(string w, int freq, int docID)
{
	auto itr = find_if(json_data.begin(), json_data.end(), [w](Word w1)->bool{return w == w1.word; });
	if (itr != json_data.end())
	{
		(*itr).freq.push_back(freq);
		(*itr).docList.push_back(docID);
		write(json_data);
	}
	else
	{
		Word t;
		t.word = w;
		t.id = json_data[json_data.size() - 1].id + 1;
		t.freq.push_back(freq);
		t.docList.push_back(docID);
		json_data.push_back(t);
		write(json_data);
	}
}
