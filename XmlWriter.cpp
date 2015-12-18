#include"XmlWriter.h"


void Node::setAttributes(string key, string value)
{
	attr.insert(pair<string, string>(key, "\""+value+"\""));
	
}


void Node::addChild(Node* node)
{
	node->parent = this;
	children.push_back(node);
}


void Node::addAttributesToStartTag()
{
	if (!attr.empty())
	{
		for (auto i : attr)
		{
			startTag += " " +i.first + "=" + i.second;
		}
		startTag += ">";
	}
	else
	{
		startTag += ">";
	}
}

void XmlWriter::dump(Node* root)
{
	writer << root->getStartTag() << endl;

	if (root->hasChildren())
	{
		vector<Node*>children = root->getChildren();
		for (auto i : children)
		{
			if (i->hasChildren())
			{
				//writer << i->getStartTag() << endl;
				dump(i);
			}
			else
			{
				writer <<" "<<i->getStartTag()<< i->getEndTag() << endl;
			}
		}
		writer << root->getEndTag() << endl;
	}
	else
	{

		return;
	}
}
