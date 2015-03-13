#include <gcnode.h>

	
GCNode::GCNode( void *ptr ) {
	this->ptr = ptr;
	refCounter = 1;
};

GCNode::~GCNode() {
	delete ptr;
}

void GCNode::reference() {
	refCounter++;
}

void GCNode::destroy() {
	refCounter--;
}
	
