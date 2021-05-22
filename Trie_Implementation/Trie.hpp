#pragma once

#include <string>
#include <vector>
static constexpr size_t SIZE = 52;

class Trie
{
   struct Node
   {
      char letter;
      bool isCompleteWord;
      std::vector<Node*> children;

      Node() : letter('\0'),isCompleteWord(false),children(SIZE) {}
      Node(char const& c) : letter(c), isCompleteWord(false), children(SIZE){}
      Node(Node const& c)
      {
         this->letter = c.letter;
         this->isCompleteWord = c.isCompleteWord;
         this->children = c.children;
      }
      Node& operator=(Node temp)
      {
         std::swap(letter, temp.letter);
         std::swap(isCompleteWord, temp.isCompleteWord);
         std::swap(children, temp.children);
         return *this;
      }
      int countChildren()
      {
         int count = 0;
         for (auto const& x : children)
         {
            if (nullptr != x)
               count++;
         }
         return count;
      }

      ~Node()
      {
         children.clear();
      }
   };

   Node* root;
   Node* getLastNode(std::string const& word);
   void traverse(Trie::Node const* node);

public:
   Trie();
   ~Trie();

   void insert(std::string const& word); // Insert a word in trie
   bool search(std::string const& word); // Search for a word in trie
   bool starts_with(std::string const& prefix); //Checks if there is any word that starts with the given string
   bool remove(std::string const& word); // Delete a word from the trie
   void print();
};
