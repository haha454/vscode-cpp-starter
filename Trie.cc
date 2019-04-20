#include "trace.hh"
#include <bits/stdc++.h>

using namespace std;

#define FIRST_CHAR 'a'

struct Node
{
    bool exist = false;
    array<Node *, 26> next;
};

class Trie
{
  private:
    Node *root;

    Node *get_node(string &word)
    {
        Node *cur = root;
        for (auto const &c : word)
        {
            if (!(cur->next[c - FIRST_CHAR]))
                return nullptr;
            cur = cur->next[c - FIRST_CHAR];
        }
        return cur;
    }

  public:
    /** Initialize your data structure here. */
    Trie()
    {
        root = new Node();
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        Node *cur = root;
        for (auto const &c : word)
        {
            if (!(cur->next[c - FIRST_CHAR]))
            {
                cur->next[c - FIRST_CHAR] = new Node();
            }
            cur = cur->next[c - FIRST_CHAR];
        }
        cur->exist = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        auto node = get_node(word);
        if (!node)
            return false;
        return node->exist;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        auto node = get_node(prefix);
        return node;
    }
};

int main()
{
    auto trie = new Trie();
    trie->insert("apple");
    PRINT(trie->search("apple"));   // returns true
    PRINT(trie->search("app"));     // returns false
    PRINT(trie->startsWith("app")); // returns true
    trie->insert("app");
    PRINT(trie->search("app")); // returns true
    delete trie;
    return 0;
}