#include "SuffixNode.h"

SuffixNode::SuffixNode(SuffixNode* n)
{
    this->suffix_link = n;
    this->path = "";
}

SuffixNode::SuffixNode(const SuffixNode* original)
{
    this->path = original->path;
    this->suffix_link = original->suffix_link;

    this->children = original->children;
    
    std::map<string, SuffixNode*>::iterator it;
    map<string, SuffixNode*> m = original->children;
    
    while (it != original->children.end())
    {
        children[it->first] = new SuffixNode(*(it->second));
        ++it;
    }
}

SuffixNode::~SuffixNode()
{
    delete suffix_link;
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
