#include "cstdio"
#include "cstdlib"
#include <fstream>
#include <string>
#include <iostream>
#include "Dictionary.cpp"

using namespace std;

static string* getRhymeGroup(string line);
static string* getWord(string line);
static void loadDictionary(Dictionary* rhymingDictionary);
static void storeRhyme(Dictionary* rhymingDictionary, string line);
static int* getTwoDifferentRandomIndexes(int length);
static void createRhyme(Dictionary* rhymingDictionary);
static void removeUnrhymables(Dictionary* rhymingDictionary);

// Given a pronunciation, get the rhyme group
// get the more *heavily emphasized vowel* and follwing syllables
// For "tomato", this is "-ato", and not "-omato", or "-o"
// Tomato shares a rhyming group with "potato", but not "grow"
static string* getRhymeGroup(string line){
	string* pronunciation = new string;
	int firstSpace = line.find_first_of(" ");

	*pronunciation = line.substr(firstSpace + 1);

	int stress0 = pronunciation->find("0");
	int stress1 = pronunciation->find("1");
	int stress2 = pronunciation->find("2");

	if(stress2 >= 0){
		*pronunciation = pronunciation->substr(stress2 - 2);
		return pronunciation;
	}
	if(stress1 >= 0){
		*pronunciation = pronunciation->substr(stress1 - 2);
		return pronunciation;
	}
	if(stress0 >= 0){
		*pronunciation = pronunciation->substr(stress0 - 2);
		return pronunciation;
	}

	return pronunciation;
}

static string* getWord(string line){
	string* word = new string;
	int firstSpace = line.find_first_of(" ");

	*word = line.substr(0, firstSpace);
	return word;
}

static void loadDictionary(Dictionary* rhymingDictionary){
	ifstream cmudict ("cmudict/cmudict-abridged.dict");
	string line;

	if(cmudict.is_open()){

		while(getline(cmudict, line)){
			storeRhyme(rhymingDictionary, line);
		}
		cmudict.close();
	}
}

/*

I am pretty sure this is the method that is giving me problems

*/
static void storeRhyme(Dictionary* rhymingDictionary, string line){
	string* word = new string;
	word = getWord(line);
	string* rhymeGroup = new string;
	rhymeGroup = getRhymeGroup(line);
	//printf("%s\n", rhymeGroup.c_str());
	if(rhymingDictionary->lookup(*rhymeGroup) == NULL){
		List* words = new List();
		words->add(0, (void*)word);
		rhymingDictionary->insert(*rhymeGroup, words);
	} else{
		List* rhyme = (List*)rhymingDictionary->lookup(*rhymeGroup);
		rhyme->add(rhyme->size, (void*)word);
		//((List*)rhymingDictionary->lookup(rhymeGroup))->add(0, (void*)&word);
		//List* rhyme = (List*)rhymingDictionary->lookup(rhymeGroup);
		/*for(int i = 0;i < rhyme->size; i++){
			string test = *static_cast<string*>(rhyme->get(i));
			printf("%s\n", test.c_str());
		}*/
	}
}

static int* getTwoDifferentRandomIndexes(int length){
	int index0 = rand() % length;

	int offset = rand() % (length - 1) + 1;
	int index1 = (index0 + offset) % length;

	int* indexes = (int*)malloc(sizeof(int)*2);
	indexes[0] = index0;
	indexes[1] = index1;

	return indexes; 
}

static void createRhyme(Dictionary* rhymingDict){
	vector<string> keys = rhymingDict->getKeys();
	//printf("Got keys\n");

	int* groupIndexes = getTwoDifferentRandomIndexes(keys.size());
	string group0Key = keys[groupIndexes[0]];
	string group1Key = keys[groupIndexes[1]];
	//printf("Got group keys\n");

	List* group0 = reinterpret_cast<List*>(rhymingDict->lookup(group0Key));
	List* group1 = reinterpret_cast<List*>(rhymingDict->lookup(group1Key));
	//printf("Got rhyming groups\n");

	int* group0Indexes = getTwoDifferentRandomIndexes(group0->size);
	int* group1Indexes = getTwoDifferentRandomIndexes(group1->size);
	//printf("Got words\n");

	string word0A = *static_cast<string*>(group0->get(group0Indexes[0]));
	string word0B = *static_cast<string*>(group0->get(group0Indexes[1]));
	string word1A = *static_cast<string*>(group1->get(group1Indexes[0]));
	string word1B = *static_cast<string*>(group1->get(group1Indexes[1]));
	//printf("%s\n", word0A.c_str());

	if(rand() % 4 > 2.0f){
		printf("\nRoses are %s,\nviolets are %s.\nI am %s\nand you are %s.\n", word0A.c_str(), word1A.c_str(), word0B.c_str(), word1B.c_str());
	} else{
		printf("\nIf I were %s\nthen you'd be the %s,\nAnd we'd both be %s\nand never be %s\n", word0A.c_str(), word1A.c_str(), word0B.c_str(), word1B.c_str());
	}
}

static void removeUnrhymables(Dictionary* rhymingDictionary){
	vector<string> keys = rhymingDictionary->getKeys();

	for(int i = 0; i < keys.size(); i++){
		if((rhymingDictionary->lookup(keys[i]))->size == 1){
			rhymingDictionary->remove(keys[i]);
		}
	}
}

static void printRhymes(Dictionary* rhymingDict){
	vector<string> keys = rhymingDict->getKeys();
	for(int i = 0; i < keys.size(); i++){
		//printf("%s\n", (string)keys[i]);
		List* group = (List*)rhymingDict->lookup(keys[i]);
		for(int j = 0; j < group->size; j++){
			string temp = *static_cast<string*>(group->get(j));
			printf("%s\n", temp.c_str());
		}
	}
}

int main(){
	srand(time(NULL));
	Dictionary* rhymingDict = new Dictionary(20000);
	loadDictionary(rhymingDict);
	printf("Loaded the Dictionary\n");
	removeUnrhymables(rhymingDict);
	printf("Removed unrhymable words\n");
	//printRhymes(rhymingDict);
	for(int i = 0; i < 3; i++){
		createRhyme(rhymingDict);
	}
	Dictionary::free_dictionary(rhymingDict);
	return 0;
}
