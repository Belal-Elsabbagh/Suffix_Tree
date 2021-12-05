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
    SuffixTrie(string s);
    /***** Copy constructor *****/
    SuffixTrie(const SuffixTrie& original);
    /*----------------------------------------------------------------------
     Construct a copy of a List object.

     Precondition:  A copy of origList is needed; origList is a const
     reference parameter.
     Postcondition: A copy of origList has been constructed.
     -----------------------------------------------------------------------*/
    
    void DestroyRecursive(SuffixNode* node);
    ~SuffixTrie();

     /***** Assignment operator *****/
    const SuffixTrie& operator=(const SuffixTrie& rightHandSide);
    /*----------------------------------------------------------------------
     Assign a copy of a List object to the current object.

     Precondition: none
     Postcondition: A copy of rightHandSide has been assigned to this
     object. A const reference to this list is returned.
     -----------------------------------------------------------------------*/

    bool empty() const;
    /*------------------------------------------------------------------------
     Check if the trie is empty.
     Precondition: None
     Postcondition: Returns true if trie is empty and false otherwise.
     -----------------------------------------------------------------------*/

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

void DestroyRecursive(SuffixNode* node);
