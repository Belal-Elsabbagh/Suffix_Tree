#include <iostream>
#include "SuffixTrie.h"
using namespace std;

void test_substring(SuffixTrie& trie, string s, string q);
void test_suffix(SuffixTrie& trie, string s, string q);
void test_occurrence(SuffixTrie& trie, string s, string q);
void test_longest_repeat(SuffixTrie& trie, string s);
void test_lexico_first_suffix(SuffixTrie& trie, string s);

int main(int argc, char* argv[])
{
    string s;
    string q;

    cout << "Enter string: "; cin >> s;
    SuffixTrie trie(s);

    cout << "\nprint trie stucture\n";
    trie.displayTree(cout);
    cout << "\nprint suffix link\n";
    trie.displaySuffix(cout);

    cout << "\nEnter another string: "; cin >> q;

    // test basic applications
    test_substring(trie, s, q);
    test_suffix(trie, s, q);
    test_occurrence(trie, s, q);
    test_longest_repeat(trie, s);
    test_lexico_first_suffix(trie, s);
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
    cout << q << " occurs " << trie.numberOf(q) << " time(s) in " << s << endl;
}

void test_longest_repeat(SuffixTrie& trie, string s)
{
    string repeat = trie.longest_repeat();
    if (repeat == "")
        cout << "There is no repeat substring in " << s << endl;
    else
        cout << repeat << " is the longest repeat substring in " << s << endl;
}

void test_lexico_first_suffix(SuffixTrie& trie, string s)
{
    string lexico_1 = trie.lexico_first_suffix();
    cout << lexico_1 << " is the first suffix of " << s << " by alphabetical order\n";
}