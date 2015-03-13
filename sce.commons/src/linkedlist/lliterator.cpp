#include "lliterator.h"

LLIterator::LLIterator(LinkedList *linkedList) {
	list = linkedList;
	index = 0;
	currentNode = NULL;
}

bool LLIterator::hasNext() {
	return ( index < list->getSize() -1 );
}

bool LLIterator::hasPrev() {
	return ( index > 0 );
}

Point *LLIterator::next() {
	if ( !hasNext() )
		return NULL;
	
	index++;

	if ( currentNode == NULL )
		currentNode = list->getFirstNode();
	else
		currentNode = currentNode->next;

	return currentNode->data;
}

Point *LLIterator::prev() {
	if ( !hasPrev() )
		return NULL;
	
	index--;

	if ( currentNode == NULL ) // how did this happen?
		currentNode = list->getLastNode();
	else
		currentNode = currentNode->prev;

	return currentNode->data;
}

