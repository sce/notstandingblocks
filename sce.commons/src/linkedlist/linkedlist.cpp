#include "linkedlist.h"

LinkedList::LinkedList()
{
	head = new Node(NULL, NULL, NULL);
	tail = new Node(head, NULL, NULL);
	head->next = tail;
	// Please don't touch these nodes :)
	size = 0;
}

LinkedList::~LinkedList()
{
	// Destroy the nodes.
	// Don't destroy the data, not our job.
	Node *nextNode;
	nextNode = head->next;
	while ( nextNode != NULL ) {
		delete head;
		head = nextNode;
		nextNode = head->next;
	}
	
	if ( head != tail )
		printf("~LinkedList() screwed up :(\n");
	else	
		printf("~LinkedList() did it's job right :)");
		
	delete head;
}

int LinkedList::add(Point *point) {
	Node *newNode = new Node(tail->prev, tail, point);
	tail->prev->next = newNode;
	tail->prev = newNode;
	return ++size;
}

Point *LinkedList::get(int index) {
	if ( index > size -1 ) 
		return NULL;
		
	Node *curNode = head->next; // currentNode
	for ( int i=0; i<index; i++ )
		curNode = curNode->next;

	return curNode->data;
}

Point *LinkedList::getFirst() {
	return head->next->data; // This works even with an empty list
}

Point *LinkedList::getLast() {
	return tail->prev->data; // Works with empty list
}

Point *LinkedList::remove(Point *point) {
	Node *curNode = head->next; // currentNode
	for ( int i=0; i<size; i++ ) {
		if ( curNode->data == point ) {
			curNode->next->prev = curNode->prev;
			curNode->prev->next = curNode->next;
			delete curNode;
			size--;
			return point;
		}
		curNode = curNode->next;
	}
	return NULL;
}

Point *LinkedList::removeFirst() {
	return remove(head->next->data); // This will remove the first node
}

Point *LinkedList::removeLast() {
	return remove(tail->prev->data); // Removes the last node
}

int LinkedList::getSize() {
	return size;
}

Node *LinkedList::getFirstNode() {
	return head->next;
}

Node *LinkedList::getLastNode() {
	return tail->prev;
}


