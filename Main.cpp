#include<iostream>
#include"Crawler.h"

using namespace std;


int main()
{

	Crawler* crawler = new Crawler();
	crawler->InitURL();
	//crawler->downloader();
	crawler->parseLink();


	return 0;
}
