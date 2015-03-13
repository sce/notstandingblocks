#include "block.h"

// initialize static members:
LOG::LOGLEVEL Block::wantloglevel_ = LOG::DEFAULTLL;
const int Block::BLOCKTYPES = 4;

int Block::lineBlock0  [] = { -2, 0,  -1, 0,  0,0,  1,0,  2,0 };
int Block::lineBlock90 [] = {  0,-2,   0,-1,  0,0,  0,1,  0,2 };

int Block::lBlock0   [] = { -2, 0,  -1, 0,  0,0,   1, 0,   1, 1 };
int Block::lBlock90  [] = {  0,-2,   0,-1,  0,0,   0, 1,  -1, 1 };
int Block::lBlock180 [] = {  2, 0,   1, 0,  0,0,  -1, 0,  -1,-1 };
int Block::lBlock270 [] = {  0, 2,   0, 1,  0,0,   0,-1,   1,-1 };

int Block::tBlock0   [] = { -1, 0,  -1, 0,  0,0,  0,1,  1, 0 };
int Block::tBlock90  [] = {  0,-1,   0,-1,  0,0,  0,1,  1, 0 };
int Block::tBlock180 [] = { -1, 0,  -1, 0,  0,0,  1,0,  0,-1 };
int Block::tBlock270 [] = { -1, 0,  -1, 0,  0,0,  0,1,  0,-1 };

int Block::sqBlock0 [] = { 0,0, 0,0, 0,1, 1,0, 1,1 };

// ---
#define LINEBlock0	{ -2, 0,  -1, 0,  0,0,  1,0,  2,0 }
#define LINEBlock90	{  0,-2,   0,-1,  0,0,  0,1,  0,2 }

#define LBlock0		 {-2, 0,  -1, 0,  0,0,   1, 0,   1, 1 }
#define LBlock90	 { 0,-2,   0,-1,  0,0,   0, 1,  -1, 1 }
#define LBlock180	 { 2, 0,   1, 0,  0,0,  -1, 0,  -1,-1 }
#define LBlock270	 { 0, 2,   0, 1,  0,0,   0,-1,   1,-1 }

#define TBlock0		{ -1, 0,  -1, 0,  0,0,  0,1,  1, 0 }
#define TBlock90	{  0,-1,   0,-1,  0,0,  0,1,  1, 0 }
#define TBlock180	{ -1, 0,  -1, 0,  0,0,  1,0,  0,-1 }
#define TBlock270	{ -1, 0,  -1, 0,  0,0,  0,1,  0,-1 }

#define SQBlock0 	0,0, 0,0, 0,1, 1,0, 1,1
/*
int Block::blockValues [][4][10] = { 
	{ LINEBlock0, LINEBlock90, LINEBlock0, LINEBlock90 },
	{ LBlock0, LBlock90, LBlock180, LBlock270 },
	{ TBlock0, TBlock90, TBlock180, TBlock270 },
	{ SQBlock0, SQBlock0, SQBlock0, SQBlock0 } 
};
*/
// ---

int *Block::blockValues [][4] = { 
	{ lineBlock0, lineBlock90, lineBlock0, lineBlock90 },
	{ lBlock0, lBlock90, lBlock180, lBlock270 },
	{ tBlock0, tBlock90, tBlock180, tBlock270 },
	{ sqBlock0, sqBlock0, sqBlock0, sqBlock0 } 
};


Block::Block(void)
{
	startRand();
	relCoords = lineBlock0;
	centerX = 0;
	centerY = 0;
	direction_ = 0;
	createRandomBlock();
}

void Block::createRandomBlock(void)
{
	// This one gives a random number between 1 and 10:
	//blocktype_ = BLOCKTYPE(1+(int) (10.0*rand()/(RAND_MAX+1.0)) );
	
	blocktype_ = BLOCKTYPE(0+(int) (4.0*rand()/(RAND_MAX+0.0)) );
	direction_ = 0; // default, standard, yeah
	rotate(); // Make sure relCoords is OK

	centerX = GameResc::MAPX/2;
	centerY = 0;
}

void Block::copyFrom(Block* block)
{
	direction_ = block->getDirection();
	blocktype_ = BLOCKTYPE(block->getBlocktype());
	centerX = block->getCenterX();
	centerY = block->getCenterY();
	rotate(); // Make sure relCoords is OK
}

void Block::move(int dx, int dy) {
	centerX +=dx;
	centerY +=dy;
}

void Block::rotateCW() {
	if ( ++direction_ > 3 )
		direction_ = 0;
		
	rotate();
}

void Block::rotateCCW() {
	if (--direction_ < 0 )
		direction_ = 3;
		
	rotate();
}

void Block::rotate()  {
	relCoords = blockValues[blocktype_][direction_];
	//relCoords = lineBlock0;
}

void Block::startRand(void) {
	srand(time(NULL)); 
}

Point *Block::getCoordinates(int index) {
	Point *point = new Point();
	point->x = *(relCoords+index*2)+centerX;
	point->y = *(relCoords+index*2+1)+centerY;
	//point->x = relCoords[index*2]+centerX;
	//point->y = relCoords[index*2+1]+centerY;
	return point;
}

int Block::getBlocktype(void) {
	return blocktype_;
}

int Block::getDirection(void) {
	return direction_;
}

int Block::getCenterX() {
	return centerX;
}

int Block::getCenterY() {
	return centerY;
}

void Block::setLoglevel(LOG::LOGLEVEL wantloglevel) {
	wantloglevel_ = wantloglevel;
}

