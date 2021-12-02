#include <functional>
#include <iostream>
#include <vector>
using namespace std;

/*-----------------------------------------------------------------------
 Ok so what I think is going on is that 
 the SuffixTree class stores a vector of nodes,
 and each node has a vector<int> that stores the indexes of its children.
 So technically, the main nodes vector in the suffix tree class stores
 literally all the nodes with each node knowing where its children are.

 This is honestly a weird implementation as far as my knowledge goes.
 At least I've never seen something done this way before.
 ----------------------------------------------------------------------*/

struct Node 
{
    string substring = "";   // a substring of the input string
    vector<int> childrenIndexes;    // vector of indexes to child nodes

    Node() {/*empty*/}

    Node(const string& sub, initializer_list<int> newChildren) 
        : substring(sub) 
    {
        childrenIndexes.insert(childrenIndexes.end(), newChildren);
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