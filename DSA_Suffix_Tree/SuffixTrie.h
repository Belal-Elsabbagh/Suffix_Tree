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
    SuffixTrie()
    {
        this->root = new SuffixNode();
        this->longest = new SuffixNode(this->root);
    }

    ~SuffixTrie()
    {
        delete this->root;
        delete this->longest;
    }

    SuffixNode* get_trie_root()
    {
        return this->root;
    }

    SuffixNode* get_deepest_leaf()
    {
        return this->longest;
    }

    /*
     *  Ukkonen's Algorithm
     *  build suffix trie of s
     *  return root node, and
     *  get deepest node
     */
    void build_suffix_trie(string s)
    {
        int len = s.length();
        if (len <= 1)
        {
            std::cout << "input string is empty\n";
            return;
        }

        // add s[0] to root
        this->root->add_link(s.substr(0, 1), this->longest);
        this->longest->set_path(s.substr(0, 1));

        // append the rest of characters
        for (int i = 1; i < len; i++)
        {
            SuffixNode* current = this->longest;
            SuffixNode* pre = NULL;

            string currentChar = s.substr(i, 1);

            // not root and s[i] not in node's children
            while (current && !current->has_string(currentChar))
            {
                SuffixNode* new_node = new SuffixNode();
                current->add_link(currentChar, new_node);
                new_node->set_path(current->get_path() + currentChar);


                if (pre != NULL)
                    pre->set_suffix_link(new_node);

                pre = new_node;
                current = current->get_suffix_link();
            }

            // set the last suffix node link
            if (current == NULL)
                pre->set_suffix_link(this->root);
            else
                pre->set_suffix_link(current->get_child(currentChar));

            if (currentChar != TERMINAL)
                this->longest = this->longest->get_child(currentChar);
        }
    }


    /*
     *  Followings are basic applicaitons of suffix trie
     */
    bool has_substring(string s)
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

    bool has_suffix(string s)
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

    int numberOf(string s)
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

    string longest_repeat()
    {
        SuffixNode* tail = this->longest;
        while (tail) {
            if (tail->get_children().size() > 1)
                return tail->get_path();
            tail = tail->get_suffix_link();
        }
        return "";
    }

    string lexico_first_suffix()
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

            for (iter = m.begin(); iter != m.end(); iter++) {
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
};

#endif
