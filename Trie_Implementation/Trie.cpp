#include "Trie.hpp"
#include <iostream>

Trie::Trie()
{
   root = new Node('\0');
}

Trie::~Trie()
{
   delete root;
   root = nullptr;
}

void Trie::insert(std::string const& word)
{
   Node* node = root; // Start the current node from the root node
   for (auto ch : word)
   {
      auto toSearch = islower(ch) ? (ch - 'a') : (ch - 'A') + 26;
      if (0 == node->children[toSearch])// If the char is not in the children list of the current node
      {
         node->children[toSearch] = new Node(ch); // Not found, so add the character
      }
      node = node->children[toSearch]; // Found, so move to the next level
   }
   node->isCompleteWord = true; // Mark the last node as complete word
}

Trie::Node* Trie::getLastNode(std::string const& word)
{
   Node* node = root; // Start the current node from the root node
   for (auto ch : word)
   {
      auto toSearch = islower(ch) ? (ch - 'a') : (ch - 'A') + 26; // Takes care of both capitals and small letters
      if (0 == node->children[toSearch])// If the char is not in the children list of the current node
      {
         return nullptr;
      }
      node = node->children[toSearch]; // Move the pointer to the next level
   }
   return node;
}

bool Trie::search(std::string const& word)
{
   Node const* temp = getLastNode(word);
   return temp != nullptr && temp->isCompleteWord; // Seach is successful if complete word is found
}

bool Trie::starts_with(std::string const& prefix)
{
   return (getLastNode(prefix) != nullptr); // Search is successful if the prefix matches any substring of already stored strings
}

//Traverse the trie recursively and print the letters
void Trie::traverse(Trie::Node const* node)
{
   static std::string out;
   if (node->isCompleteWord) // Stop when a complete word is reached
   {
      std::cout << out << std::endl;
      return;
   }
   for (Node const* n : node->children) // Traverse all the children at each level
   {
      if (n)
      {
         out += n->letter;  // Save the letter at current level
         traverse(n); // Traverse to next level of the tree
         out.pop_back(); // When recursion unwinds, delete the saved letters to avoid printing same characters multiple times
      }
   }
}

//Print a trie
void Trie::print()
{
   traverse(root);
}

// Delete a string from Trie
bool Trie::remove(std::string const& word)
{
   Node* node = getLastNode(word);
   if (nullptr == node || !node->isCompleteWord)
      return false;
   else
   {
      node->isCompleteWord = false; // Shortcut for deletion. Need to think of a better alternative.
      return true;
   }
}
