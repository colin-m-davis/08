# Trie

Implementation of a [trie](https://en.wikipedia.org/wiki/Trie) in C++.

## Structure

The trie supports strings consisting of elements of 8-bit set of ASCII characters (0<=value<=255).
Each node in the data structure contains a vector of node pointers that we resize only as needed.
We know a word exists in the trie if we can follow a path of node pointers as vector indices corresponding to each characters's ASCII value,
eventually landing at index 0 in the last node's next vector (representing '\0').
