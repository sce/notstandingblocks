#ifndef GCNODE_H_
#define GCNODE_H_

class GCNode
{
private:

	void *ptr;
	int  refCounter;
	
public:
	GCNode( void *ptr );
	
	void reference();
	void destroy();
	
	virtual ~GCNode();
};

#endif /*GCNODE_H_*/
