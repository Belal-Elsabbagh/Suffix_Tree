#include <map>
#include <string>

#ifndef SUFFIXNODE
#define SUFFIXNODE

using namespace std;

class SuffixNode
{
private:
    map<string, SuffixNode*> children;
    string path;        // substring from root to current node
    SuffixNode* suffix_link;

public:
    SuffixNode(SuffixNode* n = NULL)
    {
        this->suffix_link = n;
        this->path = "";
    }

    ~SuffixNode()
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
    void add_link(string child, SuffixNode* node)
    {
        this->children[child] = node;
    }

    // search child
    bool has_string(string child)
    {
        return this->children.find(child) != this->children.end();
    }

    // get all children nodes
    map<string, SuffixNode*> get_children()
    {
        return this->children;
    }

    // get specific child by name
    SuffixNode* get_child(string child)
    {
        if (has_string(child))
            return this->children[child];
        return NULL;
    }

    // assign suffix link
    void set_suffix_link(SuffixNode* suffix_link)
    {
        this->suffix_link = suffix_link;
    }

    // get suffix link
    SuffixNode* get_suffix_link()
    {
        return this->suffix_link;
    }

    void set_path(string path)
    {
        this->path = path;
    }

    string get_path()
    {
        return this->path;
    }
};

#endif
