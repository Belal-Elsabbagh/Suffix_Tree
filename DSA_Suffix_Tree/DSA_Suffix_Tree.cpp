#include <iostream>
#include "SuffixTrie.h"
using namespace std;

void test_substring(SuffixTrie& trie, string s, string q);
void test_suffix(SuffixTrie& trie, string s, string q);
void test_occurrence(SuffixTrie& trie, string s, string q);
void test_longest_repeat(SuffixTrie& trie, string s);

int main(int argc, char* argv[])
{
    string s;
    string q;

    cout << "Enter string: "; cin >> s;
    SuffixTrie temp(s); // testing string constructor
    SuffixTrie trie = temp; // testing copy constructor & assignment operator
    cout << "\nprint trie stucture\n";
    trie.displayTree(cout); // display the table of nodes in tree
    cout << "\nprint suffix link\n";
    trie.displaySuffixLink(cout); // display the suffixes of the string

    cout << "\nEnter another string: "; cin >> q;

    // test basic applications
    test_substring(trie, s, q);
    test_suffix(trie, s, q);
    test_occurrence(trie, s, q);
    test_longest_repeat(trie, s);
}

/***** test basic applications *****/
void test_substring(SuffixTrie& trie, string s, string q)
{
    if (trie.has_substring(q))
        cout << q << " is a substring of " << s << endl;
    else
        cout << q << " is not a substring of " << s << endl;
}

void test_suffix(SuffixTrie& trie, string s, string q)
{
    if (trie.has_suffix(q))
        cout << q << " is a suffix of " << s << endl;
    else
        cout << q << " is not a suffix of " << s << endl;
}

void test_occurrence(SuffixTrie& trie, string s, string q)
{
    cout << q << " occurs " << trie.numberOfOccurences(q) << " time(s) in " << s << endl;
}

void test_longest_repeat(SuffixTrie& trie, string s)
{
    string repeat = trie.longestRepeatedSubstring();
    if (repeat == "")
        cout << "There is no repeat substring in " << s << endl;
    else
        cout << repeat << " is the longest repeat substring in " << s << endl;
}