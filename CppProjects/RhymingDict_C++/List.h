//-----------------------------------------------------------------------------
// List.h
// Header file for the LinkedList ADT
//-----------------------------------------------------------------------------

#ifndef CMPS12B_LIST
#define CMPS12B_LIST

class List{

protected:
	//template<class type1>
	class Node{

	public:

		// Data Fields
		Node* next;
		void* data;
		friend class List;

		// Node Constructor
		Node(void* data, Node* next);

		// Frees the memory allocated for a node
		static void free_node(Node* node);
	};

public:

	// Data Fields
	Node* head;
	int size;

	// List Constructor
	List();

	// Frees the memory allocated for a List
	static void free_list(List* list);

	// Adds a new node to a List at a given index
	void add(int index, void* data);

	// Returns the data in a node at a given index
	void* get(int index);

	// Sets the data in a given node
	void set(int index, void* data);

	// Removes the node at a given index
	void remove_node(int index);
};
#endif