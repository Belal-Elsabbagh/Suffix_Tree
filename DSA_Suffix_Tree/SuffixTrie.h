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
    /*----------------------------------------------------------------------
     Constructs a SuffixTrie object

     Precondition:  None.
     Postcondition: The root node has been initialized with the pointer to
     longest pointing at root.
     -----------------------------------------------------------------------*/

    SuffixTrie(const string& s);
    /*----------------------------------------------------------------------
     Constructs a SuffixTrie object from a given string

     Precondition: A string is referenced in the constructor; s is a const
     reference parameter.
     Postcondition: A SuffixTrie object has been constructed based on string s.
     -----------------------------------------------------------------------*/
 
     /***** Copy constructor *****/
    SuffixTrie(const SuffixTrie& original);
    /*----------------------------------------------------------------------
     Constructs a trie using the string obtained from another trie.

     Precondition:  A copy of original is needed; original is a const
     reference parameter.
     Postcondition: A copy of original has been constructed.
     -----------------------------------------------------------------------*/

     /***** Assignment operator *****/
    const SuffixTrie& operator=(const SuffixTrie& rightHandSide);
    /*----------------------------------------------------------------------
     Overwrite this trie using another trie's string.

     Precondition: none
     Postcondition: A copy of rightHandSide has been assigned to this
     object. A const reference to this list is returned.
     -----------------------------------------------------------------------*/

     /***** Class destructor *****/
    ~SuffixTrie();
    /*----------------------------------------------------------------------
     Destroys the root node and the longest node.

     Precondition: None.
     Postcondition: The root node and longest node have been deallocated.
     -----------------------------------------------------------------------*/

    bool empty() const;
    /*------------------------------------------------------------------------
     Check if the trie is empty.

     Precondition: None.
     Postcondition: Returns true if trie is empty and false otherwise.
     -----------------------------------------------------------------------*/
    
    void build_suffix_trie(string s);
    /*----------------------------------------------------------------------
     Builds the trie using the given string.

     Precondition: The terminal character is added to the string
     Postcondition: The string s is now stored in the trie and can be 
     operated on.
     -----------------------------------------------------------------------*/

     /***** Basic applicaitons of suffix trie *****/
    bool has_substring(const string& s) const;
    /*----------------------------------------------------------------------
     Checks if s is a substring of the longest string.

     Precondition:  A string has been passed to the function as a const
     reference parameter.
     Postcondition: Returns true if string s is a substring of the longest
     string.
     -----------------------------------------------------------------------*/
    bool has_suffix(const string& s) const;
    /*----------------------------------------------------------------------
     Checks if s is a suffix of the longest string.

     Precondition:  A string has been passed to the function as a const
     reference parameter.
     Postcondition: Returns true if string s is a suffix of the longest
     string.
     -----------------------------------------------------------------------*/

    int numberOfOccurences(string s);
    /*----------------------------------------------------------------------
     Counts the number of occurences of a string in the longest string.

     Precondition:  A string has been passed to the function as a const
     reference parameter.
     Postcondition: Returns number of occurences of string s in the longest
     string.
     -----------------------------------------------------------------------*/
    string longestRepeatedSubstring();
    /*----------------------------------------------------------------------
     Counts the number of occurences of a string in the longest string.

     Precondition:  A string has been passed to the function as a const
     reference parameter.
     Postcondition: Returns number of occurences of string s in the longest
     string.
     -----------------------------------------------------------------------*/

    /***** output *****/
    void displayTree(ostream& out) const;
    /*----------------------------------------------------------------------
     Display the suffix trie.

     Precondition:  The ostream out is open.
     Postcondition: The structure of the trie represented by the object
     has been inserted into out.
     -----------------------------------------------------------------------*/

    void displaySuffixLink(ostream& out) const;
    /*----------------------------------------------------------------------
     Display the suffixes in the trie.

     Precondition:  The ostream out is open.
     Postcondition: The suffixes of the string that constructed the trie
     has been inserted into out.
     -----------------------------------------------------------------------*/

     /***** Setters & Getters *****/
    SuffixNode* get_trie_root() { return this->root; }
    SuffixNode* get_deepest_leaf() { return this->longest; }
};

#endif

