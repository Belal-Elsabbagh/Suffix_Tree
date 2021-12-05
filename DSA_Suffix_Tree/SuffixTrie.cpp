#include "SuffixTrie.h"
#include <functional>

/*
 *  Followings are basic applicaitons of suffix trie
 */


/*
*  Ukkonen's Algorithm
*  build suffix trie of s
*  return root node, and
*  get deepest node
*/

SuffixTrie::SuffixTrie()
{
    this->root = new SuffixNode();
    this->longest = new SuffixNode(this->root);
}

SuffixTrie::SuffixTrie(string s)
{
    build_suffix_trie(s + TERMINAL);
}

SuffixTrie::SuffixTrie(const SuffixTrie& original)
{
    //this->build_suffix_trie(original.longest->get_path());
}

void SuffixTrie::DestroyRecursive(SuffixNode* node)
{
    map<string, SuffixNode*> m = node->get_children();
    if (node != nullptr)
    {
        if (m.empty())
        {
            // delete the leaf node
            delete(node);
            return;
        }
        
        std::map<string, SuffixNode*>::iterator iter;
        for (iter = m.begin(); iter != m.end(); iter++)
        {
            DestroyRecursive(iter->second);
        }
    }
}

SuffixTrie::~SuffixTrie()
{
    DestroyRecursive(root);
    delete this->longest;
}

bool SuffixTrie::empty() const
{
    return this->root->get_children().empty();
}

const SuffixTrie& SuffixTrie::operator=(const SuffixTrie& rightHandSide)
{
    /*
    if (this != &rightHandSide)
    {
        this->~SuffixTrie();

        this->root = rightHandSide.root;
        this->longest = rightHandSide.longest;
        this->build_suffix_trie(rightHandSide.longest->get_path());
    }
    */
    return *this;
}

SuffixNode* SuffixTrie::get_trie_root()
{
    return this->root;
}

SuffixNode* SuffixTrie::get_deepest_leaf()
{
    return this->longest;
}

void SuffixTrie::build_suffix_trie(string s)
{
    int len = s.length();
    
    if (len <= 1) // check validity of string
    {
        std::cout << "input string is empty\n";
        return;
    }

    this->root->add_link(s.substr(0, 1), this->longest); // add first character to root
    this->longest->set_path(s.substr(0, 1)); //set suffix of longest to the first character

    // append the rest of characters
    for (int i = 1; i < len; i++)
    {
        SuffixNode* current = this->longest;
        SuffixNode* previous = NULL;

        string currentChar = s.substr(i, 1);

        // as long as the current character does not already exist...
        while (current && !current->has_string(currentChar))
        {
            SuffixNode* new_node = new SuffixNode();
            current->add_link(currentChar, new_node);
            new_node->set_path(current->get_path() + currentChar);


            if (previous != NULL)
                previous->set_suffix_link(new_node);

            previous = new_node;
            current = current->get_suffix_link();
        }

        // Link new nodes to parents
        if (current == NULL) 
            previous->set_suffix_link(this->root); // link unique character to root node
        else
            previous->set_suffix_link(current->get_child(currentChar)); // link new suffix to repeated character

        if (currentChar != TERMINAL)
            this->longest = this->longest->get_child(currentChar); // set longest to point to the entire string (NO TERMINAL)
    }
}

bool SuffixTrie::has_substring(string s)
{
    SuffixNode* head = this->root;

    for (int i = 0; i < s.length(); i++) {
        SuffixNode* child = head->get_child(s.substr(i, 1));
        if (child)
            head = child;
        else
            return false;
    }

    return true;
}

bool SuffixTrie::has_suffix(string s)
{
    SuffixNode* head = this->root;

    for (int i = 0; i < s.length(); i++) {
        SuffixNode* child = head->get_child(s.substr(i, 1));
        if (child)
            head = child;
        else
            return false;
    }

    if (head->get_child(TERMINAL))
        return true;
    return false;
}

int SuffixTrie::numberOf(string s)
{
    SuffixNode* head = this->root;

    for (int i = 0; i < s.length(); i++) {
        SuffixNode* child = head->get_child(s.substr(i, 1));
        if (child)
            head = child;
        else
            return 0;
    }

    int count = 0;
    // count number of leaves, use BFS algorithm
    queue<SuffixNode*> q;
    q.push(head);
    while (!q.empty()) {
        SuffixNode* node = q.front();
        q.pop();

        map<string, SuffixNode*> m = node->get_children();
        if (m.size() == 0) {
            count++;
            continue;
        }

        std::map<string, SuffixNode*>::iterator iter;
        for (iter = m.begin(); iter != m.end(); iter++) {
            q.push(iter->second);
        }
    }
    return count;
}

string SuffixTrie::longest_repeat()
{
    SuffixNode* tail = this->longest;
    while (tail) {
        if (tail->get_children().size() > 1)
            return tail->get_path();
        tail = tail->get_suffix_link();
    }
    return "";
}

string SuffixTrie::lexico_first_suffix()
{
    SuffixNode* head = this->root;
    string lexico_1 = "";

    while (head) {
        // only find the prefix of the first suffix
        if (lexico_1 != "" && head->has_string(TERMINAL))
            break;

        string min = "";
        std::map<string, SuffixNode*>::iterator iter;
        map<string, SuffixNode*> m = head->get_children();

        for (iter = m.begin(); iter != m.end(); iter++) 
        {
            string child_edge = iter->first;
            if (child_edge != TERMINAL &&
                (min == "" || child_edge.compare(min) < 0))
                min = child_edge;
        }

        lexico_1 += min;
        head = head->get_child(min);
    }

    return lexico_1;
}

void SuffixTrie::displayTree(ostream& out) const
{
    /*----------------------------------------------------------------------
     Given that the process of displaying a tree is a recursive one, it has
     to be done using a recursive function. The main display function can't
     and should NOT be used recursively. 
     The display function should call the function that defines the process 
     of outputting the tree and it will automatically output it.
     This will result in another issue where the output stream is not the
     same as the one given by the display function.

     Hence the use of this method. We define a functional object inside of
     the display function so that it would be able to use the parameters of
     the display function and perform its recursive operation as flawlessly.
     -----------------------------------------------------------------------*/

    function<void(SuffixNode* n, string last)> visualize;
    visualize = [&](SuffixNode* n, string last)
    {
        map<string, SuffixNode*> childrenMap = n->get_children();
        string children = "";

        if (children.empty())
        {
            out << "- " << n->get_path() << '\n';
            return;
        }
        out << "+ " << n->get_path() << '\n';

    };

    //definition of output process
    function<void(SuffixNode* n, string last)> tableOutput;
    tableOutput = [&](SuffixNode* n, string last)
    {
        map<string, SuffixNode*> childrenMap = n->get_children();
        string children = "";

        for (map<string, SuffixNode*>::iterator iter = childrenMap.begin(); iter != childrenMap.end(); ++iter)
        {
            string s = iter->first;
            children += s + " ";
        }

        string parent = n->get_suffix_link() ? last : "root";
        out << parent << " in " << n->get_path()
            << "\thas child: " << children
            << "\tsuffix link: ";
        if (parent != "root")
            out << n->get_suffix_link()->get_path() << endl;
        else
            out << "NONE\n";

        for (map<string, SuffixNode*>::iterator iter = childrenMap.begin(); iter != childrenMap.end(); ++iter)
        {
            string s = iter->first;
            SuffixNode* sn = iter->second;
            tableOutput(sn, s);
        }
    }; // end of definition of output process

    tableOutput(root, "");
    out << endl;
    visualize(root, "");
}

void SuffixTrie::displaySuffix(ostream& out) const
{
    SuffixNode* suffixPtr = longest;
    while (suffixPtr)
    {
        cout << suffixPtr->get_path() << endl;
        suffixPtr = suffixPtr->get_suffix_link();
    }
}
