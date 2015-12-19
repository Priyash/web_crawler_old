#include"csvLoader.h"

void CSVLoader::Load()
{
	string line;

	if (reader.bad())
	{
		cout << "Couldn't open file" << endl;
	}
	else
	{
		reader.open(file, ios::in);
		string line;
		while (getline(reader, line))
		{
			stringstream ss(line);
			string str;
			c = 0;
			char* dup = strdup(line.c_str());
			char* token = strtok(dup, " ,");
			while (token != NULL)
			{
				v.push_back((string)token);
				c++;
				token = strtok(NULL, " ,");
			}

			v.push_back("EOL");
			counter++;
		}
		line.clear();
		reader.close();
	}
}

vector<string>CSVLoader::getData()
{
	return v;
}

string** CSVLoader::loadData()
{
	mat = new string*[getRow()];
	for (int i = 0; i < getRow(); i++)
	{
		mat[i] = new string[getCol()];
	}


	int index = 0;
	for (int i = 0; i < getRow(); i++)
	{
		for (int j = 0; j < getCol(); j++)
		{
			mat[i][j] = v[index];
			index++;
		}
	}
	index = 0;
	return mat;
}
