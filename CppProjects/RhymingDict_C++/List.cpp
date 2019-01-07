#include "stdlib.h"
#include "List.h"
#include "stdio.h"

// List Constructor
List::List() 
	:head(NULL)
	,size(0)
{}

// Node Constructor
List::Node::Node(void* data, List::Node* next)
	:data(data)
	,next(next)
{}

// Free up the memory allocated for the list
void List::free_list(List* list){
	Node* curr = list->head;       // set the current node to the head of the list

	while(curr != NULL){          // keep freeing nodes until ther are none left
		Node* next = curr->next;   // set the next node, so we don't loose the 
		                          // rest of the list

		Node::free_node(curr);         // free the node
		curr = next;              // move to the next node
	}
	delete(list);                 // free the rest of the allocated memory
}

// Free up the memory allocated for the node
void List::Node::free_node(List::Node* node){
	if(node != NULL){    // if there is data in the node
		free(node->data); // free the data
	}
	delete(node);        // free the space for the node
}

// Adds a new node to the list
void List::add(int index, void* data){
	Node* curr = this->head;               // set the current node to the head of the list
	this->size++;                                // increment the size

	if(index == 0){                              // if you want to put the new node in the front
		this->head = new Node(data, curr);       // simply make the new node the head of the list
	} else{

		while(index > 1){                        // iterate to the index for the new node
			index--;                             // by decrementing the index until you have reach 0
			curr = curr->next;                   // move to the next node
		}
		curr->next = new Node(data, curr->next); // place the new node in between the current node and the next
	}
}

// Gets the data at a specified index
void* List::get(int index){
	if(index >= this->size){
		printf("out of bounds\n");
		return NULL;
	}
	Node* curr = this->head; // set the current node to the head

	while(index != 0){      // iterate through the list until you get to the desired location
		index--;            // by decrementing the index
		curr = curr->next;   // and moving to the next node
		//printf("Looking for Node\n");
	}
	return curr->data;       // return the data stored in the current node	
}

// Replace the given data with new data
void List::set(int index, void* data){
	Node* curr = this->head; // set the current node to the head

	while(index != 0){      // iterate through the list until index reached
		index--;            // decrement the index
		curr = curr->next;   // move to the next node
	}
	curr->data = data;       // replace the data
}

// removes a node at a specified location
void List::remove_node(int index){
	if (index == 0){                 // if removing the head
		Node* to_remove = this->head; // set the node to remove to the head
		this->head = this->head->next;  // set head to the next node
		Node::free_node(to_remove);        // free the memory allocated to the node
	}
	else {
		Node* curr = this->head;      // set the current node to the head
		
		while (index > 1){           // iterate the list to right beforethe index
			curr = curr->next;        // move to the next node
			index--;                 // and decrement the index
		}

		Node* to_remove = curr->next; // the node you want to remove is curr->next
		curr->next = curr->next->next;  // the next node should be the node after the one to delete
		Node::free_node(to_remove);        // free the memoru allocated to the node
	}
	this->size--;                     // decrement the size

}