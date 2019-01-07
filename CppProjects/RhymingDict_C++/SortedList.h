//-----------------------------------------------------------------------------
// SortedList.h
// Header file for the SortedLinkedList ADT
//-----------------------------------------------------------------------------

#ifndef CMPS12B_SORTEDLIST
#define CMPS12B_SORTEDLIST

// Node object
typedef struct node_type{
	struct node_type* next;
	char* data;
} Node;

// Head of list object
typedef struct{
	Node* head;
	int size;
} List;

// Returns a new node containing the data and the next node in the list
Node* make_node(char* data, Node* next);

// Returns a new List
List* make_list();

// Frees the memory allocated for a node
void free_node(Node* node);

// Frees the memory allocated for a List
void free_list(List* list);

// Adds a new node to a List at a given index
void add(List* list, int index, char* data);

// Returns the data in a node at a given index
void* get(List* list, int index);

// Sets the data in a given node
void set(List* list, int index, char* data);

// Removes the node at a given index
void remove_node(List* list, int index);

#endif