//-----------------------------------------------------------------------------
// Dictionary.h
// Header file for the Dictionary ADT
//-----------------------------------------------------------------------------
#include "List.cpp"
#include <string>
#include <vector>

#ifndef _DICTIONARY_H_INCLUDE_
#define _DICTIONARY_H_INCLUDE_
class Dictionary{
private:
	int size;
	List** table;

	class Entry{
		friend class Dictionary;

		std::string key;
		//std::string value;
		List* value;

		Entry(std::string key, List* value);

		static void free_entry(Entry* entry);
	};

public:
	int tablesize;

	// Dictionary Constructor
	Dictionary(int tablesize);

	// Frees memory allocated to a Dictionary
	static void free_dictionary(Dictionary* dictionary);

	// Returns wether the dictionary is empty or not
	bool isEmpty();

	// Returns the size of the dictionary
	int getSize();

	// Returns the value v such that (k, v) is in D or will
	// return NULL if there is no such pair
	List* lookup(std::string k);

	// Inserts a new key value pair
	// pre: lookup(D, k)== NULL
	void insert(std::string k, List* v);

	// Removes a key value pair
	// pre: lookup(D, k) != NULL
	void remove(std::string k);

	// Removes all key-value pairs and resets the dictionary
	void makeEmpty();

	std::vector<std::string> getKeys();

	// Prints the dictionary out to a specified file
	void printDictionary(FILE* out);
};

#endif