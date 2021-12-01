#include <functional>
#include <iostream>
#include <vector>
using namespace std;

struct Node 
{
    string sub = "";   // a substring of the input string
    vector<int> ch;    // vector of child nodes

    Node() 
    {
        // empty
    }

    Node(const string& sub, initializer_list<int> children) : sub(sub) 
    {
        ch.insert(ch.end(), children);
    }
};

class SuffixTree 
{
public:

    vector<Node> nodes;

    SuffixTree(const string& str);

    void visualize();

private:
    void addSuffix(const string& suf);
};