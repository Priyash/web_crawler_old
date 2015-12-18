#include<iostream>
#include"Crawler.h"

using namespace std;


int main()
{

	Crawler* crawler = new Crawler();
	crawler->InitURL();
	//crawler->downloader();
	crawler->parseLink();
        //HOW TO CALL HTML_Text MODULE
        /*
        
        string file = "Search.html";
	HTML_PARSER* hp = new HTML_PARSER(file.c_str());
	hp->loadData();
	hp->parseText();
        
        */
        
        /* usage XmlWriter
        Node* root = new Node("Index");
	root->addAttributesToStartTag();
	

	Node* wordNode1 = new Node("word");
	wordNode1->setAttributes("id", "1");
	wordNode1->setAttributes("url", "www.google.com");
	wordNode1->addAttributesToStartTag();

	Node* wordNode2 = new Node("word");
	wordNode2->setAttributes("id", "2");
	wordNode2->setAttributes("url", "www.facebook.com");
	wordNode2->addAttributesToStartTag();

	Node* wordNode3 = new Node("word");
	wordNode3->setAttributes("id", "3");
	wordNode3->setAttributes("url", "www.cnet.com");
	wordNode3->addAttributesToStartTag();

	Node* wordNode4 = new Node("word");
	wordNode4->setAttributes("id", "4");
	wordNode4->setAttributes("url", "www.wired.com");
	wordNode4->addAttributesToStartTag();

	Node* wordNode5 = new Node("word");
	wordNode5->setAttributes("id", "5");
	wordNode5->setAttributes("url", "www.news.com");
	wordNode5->addAttributesToStartTag();

	Node* wordSubNode1 = new Node("sub-word");
	wordSubNode1->setAttributes("id", "1");
	wordSubNode1->setAttributes("url", "www.speakingtree.com");
	wordSubNode1->addAttributesToStartTag();

	wordNode5->addChild(wordSubNode1);


	root->addChild(wordNode1);
	root->addChild(wordNode2);
	root->addChild(wordNode3);
	root->addChild(wordNode4);
	root->addChild(wordNode5);

	XmlWriter* xw = new XmlWriter("data.xml");
	xw->dump(root);
        
        */

	return 0;
}
