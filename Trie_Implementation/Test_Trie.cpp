#include <iostream>
#include "Trie.hpp"

int main()
{
   Trie* storage = new Trie();
   std::vector<std::string> strings{ "Cat", "cape", "cats", "call" };
   for (auto const& s : strings)
   {
      storage->insert(s);
   }
   storage->remove("Cats");
   storage->print();

   std::string input;
   std::cout << " Please enter the string to search for: " << std::endl;
   std::cin >> input;
   if (storage->search(input))
      std::cout << "Found!" << std::endl;
   else
      std::cout << "Not Found!" << std::endl;

   std::cout << " Please enter the prefix to search for: " << std::endl;
   std::cin >> input;
   if (storage->starts_with(input))
      std::cout << "Found!" << std::endl;
   else
      std::cout << "Not Found!" << std::endl;

   delete storage;
   storage = nullptr;
}
