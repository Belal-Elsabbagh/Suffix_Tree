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
    SuffixNode(SuffixNode* n = NULL);

    ~SuffixNode();

    // link node to SuffixNode by child
    void add_link(string child, SuffixNode* node);

    // search child
    bool has_string(string child);

    /***** Setters & Getters *****/
    map<string, SuffixNode*> get_children() { return this->children; }
    void set_suffix_link(SuffixNode* suffix_link) { this->suffix_link = suffix_link; }
    SuffixNode* get_suffix_link() { return this->suffix_link; }
    void set_path(string path) { this->path = path; }
    string get_path() { return this->path; }
    
    // get specific child by name
    SuffixNode* get_child(string child)
    {
        if (has_string(child))
            return this->children[child];
        return NULL;
    }
};

#endif
