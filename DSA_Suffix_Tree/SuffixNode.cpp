#include "SuffixNode.h"

SuffixNode::SuffixNode(SuffixNode* n)
{
    this->suffix_link = n;
    this->path = "";
}

SuffixNode::~SuffixNode()
{
    path = "";
    delete this->suffix_link;

    for (std::map<string, SuffixNode*>::iterator iter = this->children.begin(); iter != this->children.end(); ++iter)
    {
        delete iter->second;
    }
    this->children.clear();
}

// link node to SuffixNode by child

void SuffixNode::add_link(string child, SuffixNode* node)
{
    this->children[child] = node;
}

// search child

bool SuffixNode::has_string(string child)
{
    return this->children.find(child) != this->children.end();
}
