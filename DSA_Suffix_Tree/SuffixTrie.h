#include "SuffixNode.h"
#include <iostream>
#include <queue>

#ifndef SUFFIXTRIE
#define SUFFIXTRIE

using namespace std;

#define TERMINAL "$"

class SuffixTrie
{
private:
    SuffixNode* root;       // root of the trie
    SuffixNode* longest;    // point to the last charater except TERMINAL

public:
    SuffixTrie();

    ~SuffixTrie();

    SuffixNode* get_trie_root();

    SuffixNode* get_deepest_leaf();

    /*
     *  Ukkonen's Algorithm
     *  build suffix trie of s
     *  return root node, and
     *  get deepest node
     */
    void build_suffix_trie(string s);


    /*
     *  Followings are basic applicaitons of suffix trie
     */
    bool has_substring(string s);

    bool has_suffix(string s);

    int numberOf(string s);

    string longest_repeat();

    string lexico_first_suffix();

    /***** output *****/
    void displayTree(ostream& out) const;
    /*----------------------------------------------------------------------
     Display the suffix trie.

     Precondition:  The ostream out is open.
     Postcondition: The structure of the trie represented by the object
     has been inserted into out.
     -----------------------------------------------------------------------*/

    void displaySuffix(ostream& out) const;
    /*----------------------------------------------------------------------
     Display the suffixes in the trie.

     Precondition:  The ostream out is open.
     Postcondition: The suffixes of the string that constructed the trie
     has been inserted into out.
     -----------------------------------------------------------------------*/
};

#endif
