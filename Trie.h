// Student ID: 20440950
// Name: Colin Davis

#ifndef TRIE
#define TRIE

#include <vector>
#include <cstdlib>
#include <iostream>
#include <queue>

class Trie
{
public:
    struct Node
    {
        std::vector<Trie::Node*> next;

        ~Node();

        void insert(std::string s);
        const Node* traverse(std::string s) const;
        bool lookup(std::string s) const;
        size_t get_completions(std::vector<std::string>& completions, size_t limit) const;
    };

    Node* _root;

    const Trie::Node *traverse(std::string s) const { return _root->traverse(s); }

public:
    Trie();
    ~Trie();

    void insert(std::string s) { _root->insert(s); }
    bool lookup(std::string s) const { return _root->lookup(s); }
    size_t get_completions(std::string s, std::vector<std::string>& completions, size_t limit) const;
    size_t trie_sort(std::vector<std::string>& vec) const;

    std::string to_string(size_t n) const;
    std::ostream& operator<<(std::ostream& os) { return os << to_string(100); }
};

#endif