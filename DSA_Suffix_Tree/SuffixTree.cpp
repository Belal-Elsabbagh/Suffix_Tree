#include "SuffixTree.h"

SuffixTree::SuffixTree(const string& str) 
{
    nodes.push_back(Node());
    for (size_t i = 0; i < str.length(); i++) 
    {
        addSuffix(str.substr(i)); // takes whole word till last suffix
    }
}

void SuffixTree::visualize()
{
    if (nodes.size() == 0)
    {
        cout << "<empty>\n";
        return;
    }

    function<void(int, const string&)> f;
    f = [&](int n, const string& pre)
    {
        auto children = nodes[n].childrenIndexes;
        if (children.size() == 0) 
        {
            cout << "- " << nodes[n].substring << '\n';
            return;
        }
        cout << "+ " << nodes[n].substring << '\n';

        auto it = begin(children);
        if (it != end(children)) do 
        {
            if (next(it) == end(children)) break;
            cout << pre << "+-";
            f(*it, pre + "| ");
            it = next(it);
        } while (true);

        cout << pre << "+-";
        f(children[children.size() - 1], pre + "  ");
    };

    f(0, "");
}

void SuffixTree::addSuffix(const string& suf)
{
    int n = 0;
    size_t i = 0;

    while (i < suf.length())
    {
        char b = suf[i]; // iterates through characters
        int x2 = 0; // index (idk what that is)
        int n2; // index of new node

        while (true)
        {
            vector<int> children = nodes[n].childrenIndexes; // stores an unaltered version of the current nodes

            if (x2 == children.size()) // no matching child
            {
                // remainder of suf becomes new node
                
                n2 = nodes.size(); // sets node index to current number of nodes

                nodes.push_back(Node(suf.substr(i), {})); // add node with a substring of current suffix

                nodes[n].childrenIndexes.push_back(n2); // add index of child node to the current node
                
                return; // returns to constructor to add the next suffix (if there's any)
            }

            n2 = children[x2];

            if (nodes[n2].substring[0] == b) // if the first character of the substring in the node is 
                                             // the same as the current character
            {
                break; // breaks the loop to process the new substring
            }
            x2++;
        }

        // find prefix of remaining suffix in common with child
        auto sub2 = nodes[n2].substring;
        size_t j = 0;
        while (j < sub2.size())
        {
            if (suf[i + j] != sub2[j])
            {
                // split n2
                auto n3 = n2;
                // new node for the part in common
                n2 = nodes.size();
                nodes.push_back(Node(sub2.substr(0, j), { n3 }));
                nodes[n3].substring = sub2.substr(j); // old node loses the part in common
                nodes[n].childrenIndexes[x2] = n2;
                break; // continue down the tree
            }
            j++;
        }
        i += j; // advance past part in common
        n = n2; // continue down the tree
    }
}