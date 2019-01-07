#include "stdlib.h"
#include "List.cpp"
#include "stdio.h"
#include "string"

class SortedList : public List{
public:

	// SortedList Constructor
	SortedList()
	:head(NULL)
	,size(0)
	{}

	// Adds a new node to the list
	void add(char* data){
		Node* new_node = make_node(data, NULL);

		if(list->head == NULL){
			list->head = new_node;
		} else{

			Node* curr = head;
			Node* prev = NULL;
			char* currData;

			while(curr != NULL){
				currData = curr->data;
				if(currData.compare(data) < 0){
					prev = curr;
					curr = curr->next;
				} else{
					break;
				}
			}

			if(prev == NULL){
				new_node->next = head;
				list->head = new_node;
			} else if(prev->next == NULL){
				prev->next = new_node;
			} else{
				new_node->next = prev->next;
				prev->next = new_node;
			}
		}
		list->size++;
	}


};
