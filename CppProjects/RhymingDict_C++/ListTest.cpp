#include "cstdio"
#include "cstdlib"
#include "List.cpp"

int main(){
	List* test = new List();

	for(int i = 0; i < 3; i++){
		int* num = (int*)malloc(sizeof(int));
		*num = i;
		test->add(test->size, num);
	}


	for(int i = 0; i < test->size; i++){
		int* pointer = (int*)test->get(i);
		printf("%d\n", *pointer);
	}

	test->remove_node(0);

	for(int i = 0; i < test->size; i++){
		int* pointer = (int*)test->get(i);
		printf("%d\n", *pointer);
	}

	List::free_list(test);
	/*
	SortedList* sorted = new SortedList();
	std::string str1 = "Hello";
	std::string str2 = "World";

	sorted->add(str1);
	sorted->add(str2);

	for(int i = 0; i < sorted->size; i++){
		std::string word = sorted->get(i);
		printf("%s\n", word);
	}\*/
}