#include "Dictionary.h"
#include "stdlib.h"
#include "stdio.h"
#include <string>
#include <vector>

using namespace std;

// Dictionary ADT
unsigned int rotate_left(unsigned int value, int shift);
unsigned int pre_hash(string input);
int dhash(Dictionary* D, string key);

// Dictionary Constructor
Dictionary::Dictionary(int tablesize)
	:size(0)
	,tablesize(tablesize)
	,table(new List*[tablesize]) //(List**)calloc(tablesize, sizeof(List))
{}

// Entry Constructor
Dictionary::Entry::Entry(string key, List* value)
	:key(key)
	,value(value)
{}

// Frees memory allocated to a Dictionary
void Dictionary::free_dictionary(Dictionary* dictionary){

	dictionary->makeEmpty();        // Remove all Entries
	delete[] dictionary->table;    // Delete the table
	delete(dictionary);           // Delete the Dictionary

	dictionary->table = NULL;   // Set pointer to table to NULL
	dictionary = NULL;             // Set Dictionary pointer to NULL
}

// Frees memory allocated to an Entry
void Dictionary::Entry::free_entry(Entry* entry){
	List::free_list(entry->value);
	delete(entry);       // Delete Entry
	entry->value = NULL; // Set value field to NULL
	(entry->key).clear();   // Set key field to NULL
}

// Returns wether the dictionary is empty or not
bool Dictionary::isEmpty(){
	if(this->size == 0){ // If the size of the Dictionary is 0, return true
		return true;
	}else{            // Else return false
		return false;
	}
}

// Returns the size of the dictionary
int Dictionary::getSize(){
	return this->size;
}

// Returns the value v such that (k, v) is in D or will
// return NULL if there is no such pair
List* Dictionary::lookup(string k){

	// Computes the hash value of the key and gets the right bucket
	int hash_code = dhash(this, k);
	List* bucket = this->table[hash_code];

	if(bucket == NULL){       // If there is no bucket, return NULL
		return NULL;
	} else{                   // Else, look inside and return the value of the key/value pair
		for(int i = 0; i < bucket->size; i++){
			if(k.compare(reinterpret_cast<Entry*>(bucket->get(i))->key) == 0){
				return reinterpret_cast<Entry*>(bucket->get(i))->value;
			}
		}
		return NULL;
	}
}

// Inserts a new key value pair
// pre: lookup(D, k)== NULL
void Dictionary::insert(string k, List* v){

	// Computes the hash value of the key and gets the right bucket
	int hash_code = dhash(this, k);
	List* bucket = this->table[hash_code];
	Entry* new_entry = new Entry(k, v);
	if(bucket == NULL){ // If there is no bucket, make a new one and put in the Entry
		bucket = new List();
		bucket->add(0, new_entry);
		this->table[hash_code] = bucket;
		this->size++;
	} else{ // Add the Entry to the existing bucket otherwise
		for(int i = 0; i < bucket->size; i++){
			if(k.compare(reinterpret_cast<Entry*>(bucket->get(i))->key) == 0){
				bucket->set(i, new_entry);
				return;
			}
		}
		bucket->add(0, new_entry);
		this->size++;
	}
}

// Removes a key value pair
// pre: lookup(D, k) != NULL
void Dictionary::remove(string k){
	
	// Computes the hash value of the key and gets the right bucket
	int hash_code = dhash(this, k);
	List* bucket = this->table[hash_code];

	if(bucket != NULL){
		for(int i = 0; i < bucket->size; i++){
			if(k.compare(reinterpret_cast<Entry*>(bucket->get(i))->key) == 0){
				//Entry::free_entry(reinterpret_cast<Entry*>(bucket->get(i)));
				bucket->remove_node(i);
				this->size--;
			}
		}
	}
}

// Removes all key-value pairs and resets the dictionary
void Dictionary::makeEmpty(){
		// Loop through the table and free any lists
	for(int i = 0; i < this->tablesize; i++){
		List* bucket = this->table[i];
		if(bucket != NULL){	
			for(int j = 0; j < bucket->size; j++){
				//Entry::free_entry(reinterpret_cast<Entry*>(bucket->get(0)));
				bucket->remove_node(0);
			}
			List::free_list(bucket);
			this->table[i] = NULL;
		}
	}

	// Then set the size to 0
	this->size = 0;
}

vector<string> Dictionary::getKeys(){
	vector<string> keys;
	for(int i = 0; i < this->tablesize; i++){
		List* bucket = this->table[i];
		if(bucket != NULL){	
			for(int j = 0; j < bucket->size; j++){
				keys.push_back(reinterpret_cast<Entry*>(bucket->get(j))->key);
			}
		}
	}

	return keys;
}

// Prints the dictionary out to a specified file
void Dictionary::printDictionary(FILE* out){
	/*for(int i = 0; i < this->tablesize; i++){
		List* bucket = this->table[i];
		if(bucket != NULL){
			for(int j = 0; j < bucket->size; j++){
				fprintf(out, "%s %s\n", (reinterpret_cast<Entry*>(bucket->get(j))->key).c_str(), (reinterpret_cast<Entry*>(bucket->get(j))->value).c_str());
			}
		}
	}*/
}

unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);
   if ( shift == 0 ) {
      return value;
   }
   return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(string strInput) {
	char* input = (char*)strInput.c_str();
	unsigned int result = 0xBAE86554;
	while (*input) {
		result ^= *input++;
		result = rotate_left(result, 5);
	}
	return result;
}

// dhash()
// turns a string into an int in the range 0 to tablesize-1
int dhash(Dictionary* D, string key){
   return pre_hash(key) % D->tablesize;
}