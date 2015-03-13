#ifndef NODE_H_
#define NODE_H_

#include "point.h"

class Node {
public:
	Node *prev;
	Node *next;
	Point *data;

	Node(Node *prev, Node *next, Point *data);
	virtual ~Node();
};

#endif /*NODE_H_*/
