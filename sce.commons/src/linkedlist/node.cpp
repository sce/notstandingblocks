#include "node.h"

Node::Node(Node *prev, Node *next, Point *data) {
	this->prev = prev;
	this->next = next;
	this->data = data;
}

Node::~Node() {
	// Don't delete nodes,
	// don't delete data.
	// In fact, don't touch anything ;)
}	
