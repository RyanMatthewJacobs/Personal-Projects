#include "cstdio"
#include "cstdlib"
#include "Dictionary.cpp"
#include <string>
#include <vector>

using namespace std;

int main(){
	Dictionary* dict = new Dictionary(1000);
	vector<string> vect;
	string key1 = "Hello";
	string value1 = "World";

	string key2 = "Bye";
	string value2 = "Moon";

	dict->insert(key1, value1);
	dict->insert(key2, value2);

	printf("%s\n", (dict->lookup(key1)).c_str());	
	printf("%s\n", (dict->lookup(key2)).c_str());

	vect = dict->getKeys();
	for(auto i = vect.begin(); i != vect.end(); ++i){
		printf("%s\n", i->c_str());
	}

	dict->remove(key1);

	printf("%s\n", (dict->lookup(key1)).c_str());
	Dictionary::free_dictionary(dict);

}