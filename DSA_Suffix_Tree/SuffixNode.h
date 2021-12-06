#include <map>
#include <string>

#ifndef SUFFIXNODE
#define SUFFIXNODE

using namespace std;

class SuffixNode
{
private:
    
    /*----------------------------------------------------------------------
     The reason we use a map to store the children of a specific node.
    
    The Suffix Trie is a data structure where each node has children that
     are uniquely identified by the character in them. So instead of having
     the character as an attribute inside the SuffixNode and then store all
     the nodes in an array or a list, we map them with their unique keys
     which are the strings they store.

     This gives us the ability to easily search and retrieve Nodes using
     a certain character and store as much children as we might possibly
     need.
     ----------------------------------------------------------------------*/
    map<string, SuffixNode*> children;
    string path; // substring from root to current node
    SuffixNode* suffix_link;

public:
    SuffixNode(SuffixNode* n = NULL);
    SuffixNode(const SuffixNode* original);
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
