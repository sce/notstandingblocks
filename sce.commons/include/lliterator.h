#ifndef LLITERATOR_H_
#define LLITERATOR_H_

#include "linkedlist.h"
#include "node.h"
#include "point.h"

/**
 * LinkedListIterator
 */
class LLIterator
{
private:
	LinkedList *list;
	Node *currentNode;
	int index;
		
public:
	LLIterator(LinkedList *linkedList);
	virtual ~LLIterator()=0;
	
	bool hasNext();
	bool hasPrev();
	Point *next();
	Point *prev();
};

#endif /*LLITERATOR_H_*/
