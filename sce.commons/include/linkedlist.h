#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdlib.h>
#include <stdio.h>

#include "point.h"
#include "node.h"

class LinkedList
{
private:
	//class Node; // Have no idea if this is working
	Node *head;
	Node *tail;
	int size;
	
public:
	LinkedList();
	virtual ~LinkedList();
	
	int getSize();	

	// Bruker point som dummyklasse før vi innfører templates
	int   add(Point *point); // returnerer index (..), -1 hvis no good..

	Point *get(int index);
	Point *getFirst();
	Point *getLast();

	Point *remove(Point *point); // null hvis ikke funnet
	Point *removeFirst();
	Point *removeLast();

	Node  *getFirstNode();
	Node  *getLastNode();
};


#endif /*LINKEDLIST_H_*/
