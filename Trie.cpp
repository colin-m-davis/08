// Student ID: 20440950
// Name: Colin Davis

#include "Trie.h"

Trie::Trie() { _root = new Node(); }

void Trie::Node::insert(std::string s)
{
    Trie::Node* curr = this;
    for (const char* str = s.c_str(); *str; str++)
    {
        char ch = *str;

        // Expand the layer as necessary
        if ((size_t)ch >= curr->next.size())
        {
            curr->next.resize(ch+1);
        }

        // If we've already been here before, leave no trace
        if (curr->next[ch] != nullptr)
        {
            curr = curr->next[ch];
        }
        // Otherwise, leave a breadcrumb in memory of our visit
        else
        {
            curr->next[ch] = new Trie::Node();
            curr = curr->next[ch];
        }
    }

    // Our last consideration for this method is the null character '\0'
    // We need to expand our array to include the 0th index if it's empty
    if  (curr->next.empty())
    {
        curr->next.resize(1);
    }

    // We need to indicate that we have the end of a string here, if we haven't already done so
    if (curr->next[0] == nullptr)
    {
        curr->next[0] = new Trie::Node();
    }
}

// Input: "shore"; Output: last->next['e'], NOT last->next['\0']
const Trie::Node* Trie::Node::traverse(std::string s) const
{
    const Trie::Node* curr = this;
    for (const char* str = s.c_str(); *str; str++)
    {
        char ch = *str;

        if ((size_t)ch >= curr->next.size())
        {
            return nullptr;
        }
        else if (curr->next[ch] != nullptr)
        {
            curr = curr->next[ch];
        }
        else
        {
            return nullptr;
        }
    }
    return curr;
}

// Return true if s\0 has been inserted into the trie
bool Trie::Node::lookup(std::string s) const
{
    const Node* end = Trie::Node::traverse(s);
    if (end == nullptr)
    {
        return false;
    }
    return (end->next[0] != nullptr); 
}

Trie::Node::~Node()
{
    static int r_depth = 0;
    std::cout << "Rdepth+ " << ++r_depth << std::endl; // delete
    for (Node* node : next)
    {
        delete node;
        node = nullptr;
    }
    std::cout << "Rdepth- " << --r_depth << std::endl; // delete
}

Trie::~Trie()
{
    delete _root;
    _root = nullptr;
}

size_t Trie::Node::get_completions(std::vector<std::string> &completions, size_t limit) const
{
    struct Continuation
    {
        const Trie::Node *node;
        std::string partial;
        Continuation(const Node* p, std::string s) : node(p), partial(s) {}
    };

    std::queue<Continuation> unprocessed_nodes;
    unprocessed_nodes.push(Continuation(this, ""));

    while (!unprocessed_nodes.empty())
    {
        // Pop the front node from the queue
        Continuation cont = unprocessed_nodes.front();
        unprocessed_nodes.pop();

        // Add all the children of the popped node to the end of the queue
        int i = 0;
        for (Node* n : cont.node->next)
        {
            if (n != nullptr)
            {
                unprocessed_nodes.push(Continuation(n, cont.partial + char(i)));
            }
            i++;
        }

        // Process the node's data element
        if ((cont.partial.length() > 0) && (cont.partial.back() == '\0'))
        {
            cont.partial.pop_back();
            completions.push_back(cont.partial);
        }

        if (completions.size() >= limit)
        {
            return completions.size();
        }
    }

    return completions.size();
}

size_t Trie::get_completions(std::string s, std::vector<std::string> &completions, size_t limit) const
{
    const Node* x = traverse(s);
    if (x == nullptr)
    {
        return 0;
    }
    return x->get_completions(completions, limit);
}

std::string Trie::to_string(size_t n) const
{
    std::string s = "# Trie contents\n";

    std::vector<std::string> comp;
    size_t x = get_completions("", comp, n);

    for (std::string c : comp)
    {
        s += c;
        s += "\n";
    }
    if (x == n)
    {
        s += "...\n";
    }

    return s;
}

size_t Trie::trie_sort(std::vector<std::string>& vec) const
{
    vec.clear();
}