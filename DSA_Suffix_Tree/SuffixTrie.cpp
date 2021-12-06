#include "SuffixTrie.h"
#include <functional>
#include <iomanip>

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

SuffixTrie::SuffixTrie(const string& s)
{
    this->root = new SuffixNode();
    this->longest = new SuffixNode(this->root);
    build_suffix_trie(s);
}

SuffixTrie::SuffixTrie(const SuffixTrie& original)
{
    this->root = new SuffixNode();
    this->longest = new SuffixNode(this->root);
    build_suffix_trie(original.longest->get_path());
}

const SuffixTrie& SuffixTrie::operator=(const SuffixTrie& rightHandSide)
{
    build_suffix_trie(rightHandSide.longest->get_path());

    return *this;
}

SuffixTrie::~SuffixTrie()
{
    delete root;
    delete longest;
}

bool SuffixTrie::empty() const
{
    return this->root->get_children().empty();
}

void SuffixTrie::build_suffix_trie(string s)
{
    s += TERMINAL;
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

bool SuffixTrie::has_substring(const string& s) const
{
    SuffixNode* head = this->root; // points to the root of the tree

    for (int i = 0; i < s.length(); i++) // iterates through the char of the substring
    {
        SuffixNode* child = head->get_child(s.substr(i, 1)); // points to the child node with the char of the substring
        if (child) // if child != NULL
            head = child; // point the head to this child - move to the next char (this child)
        else
            return false; // couldn't find a child, which means that this next letter does not exist
                          // which means that string s is DEFINITELY NOT a substring of the original string
    }
    
    // after passing the validation loop...
    return true;
} 

bool SuffixTrie::has_suffix(const string& s) const
{
    SuffixNode* head = this->root; // points to the root of the tree

    for (int i = 0; i < s.length(); i++) // iterates through the char of the substring
    {
        SuffixNode* child = head->get_child(s.substr(i, 1)); // points to the child node with the char of the suffix
        if (child) // if child != NULL
            head = child; // point the head to this child - move to the next char (this child)
        
        else              // couldn't find a child, which means that this next letter does not exist
            return false; // which means that string s is DEFINITELY NOT a suffix of the original string
    }
    

    if (head->get_child(TERMINAL)) // if the head has reached the parent of TERMINAL
        return true;
    return false;
}

int SuffixTrie::numberOfOccurences(string s)
{
    SuffixNode* head = this->root; // points to the root of the tree

    for (int i = 0; i < s.length(); i++) // iterates through the char of the substring
    {
        SuffixNode* child = head->get_child(s.substr(i, 1)); // points to the child node with the char of the substring
        if (child) // if child != NULL
            head = child; // point the head to this child - move to the next char (this child)
        else
            return 0;
    }

    int count = 0;
    
    // count number of leaves, use BFS algorithm
    queue<SuffixNode*> q;
    q.push(head);
    while (!q.empty()) 
    {
        SuffixNode* node = q.front();
        q.pop(); // empties the queue (there was only 1 element anyway)

        map<string, SuffixNode*> nodeChildren = node->get_children();
        
        if (nodeChildren.size() == 0) 
        {
            count++;
            continue;
        }

        map<string, SuffixNode*>::iterator iter;
        for (iter = nodeChildren.begin(); iter != nodeChildren.end(); iter++) 
        {
            q.push(iter->second);
        }
    }
    return count;
}

string SuffixTrie::longestRepeatedSubstring()
{
    // We will move up the longest path towards the root node.
    SuffixNode* tail = this->longest;

    while (tail) // as long as the tail is not null
    {
        if (tail->get_children().size() > 1) // if the node has more than 1 child
            return tail->get_path(); // this means that this node has the longest repeated substring.
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
        out << parent << " \tin " << n->get_path()
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
