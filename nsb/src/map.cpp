
#include "map.h"

// initialize static members:
int Map::map_[GameResc::MAPX][GameResc::MAPY]; // don't give it values
// --

Map::Map(void)
{
	startNew();
}

void Map::startNew(void)
{
	// clear map
	for (int x=0; x<MAPX; x++)
		for (int y=0; y<MAPY; y++)
			map_[x][y] = EMPTY;

	// DEBUG: Hack map to contain square
	map_[MAPX/2-1][MAPY-1] = SQUARE0;
}

bool Map::doesCollide(Block *block) {
	int x = 0, y = 0;
	
	for ( int coord=0; coord<Block::MAXSQUARES; coord++)
	{
		Point *point = block->getCoordinates(coord);
		x = point->x;
		y = point->y;
		delete point;

		if ( x < 0 || y < 0 ) // It's hitting the wall
			return true;
			
		if ( x > MAPX-1 || y > MAPY-1 ) // the other wall ;)
			return true;
			
		if ( getXY(x,y) != Map::EMPTY ) {
			return true;
		}
	}
	return false;
}

void Map::markFullRow(int row) {
	for (int x=0; x<MAPX; x++)
		setXY( x, row, -1 );
}

void Map::putBlockOnMap(Block* block, int value) {
	for (int sq=0; sq<Block::MAXSQUARES; sq++) {// sq = square
		Point *point = block->getCoordinates(sq);
		setXY( point->x, point->y, value );
		delete point;
	}
}

void Map::removeBlockFromMap(Block* block) {
	for (int pos=0; pos<Block::MAXSQUARES; pos++) {
		Point *point = block->getCoordinates(pos);
		setXY( point->x, point->y, EMPTY );
		delete point;
	}
}

void Map::removeRow(int row) {
	for (int x=0; x<MAPX; x++)
		setXY( x, row, EMPTY ); // Remove it

	// move every row to higher level (0 is top, so higher is bottom)
	for (int copyingY=row; copyingY>0; copyingY--)
	{
		for (int copyingX=0; copyingX<MAPX; copyingX++)
			setXY( copyingX, copyingY, getXY(copyingX, copyingY-1) );
	}
}

void Map::setXY(int x, int y, int value)
{
	// check that it's not out of bounds
	// ** Block::Move HAS TO DO THIS, NOT INCLUDING REDUNDANT CODE HERE **
	// ** WHOOOPPS, turns out we need to exclude those pesky (-1,-1) **
	if ( x < 0 || y < 0 )
	{
		char *string = new char[256];
		snprintf(string, 256, "* Map::setXY(%i,%i) is out of bounds!", x, y);
		LOG::Log(string, LOG::WARNING, LOG::NONE);
		delete string; // above: not error, just warning: expected behavior
		return;
	}

	map_[x][y] = value; // no errorchecking on the value here
}

int Map::getXY(int x, int y)
{
	if ( x < 0 || x > MAPX-1
	||   y < 0 || y > MAPY-1 )
		return !EMPTY; // heh

	return map_[x][y];
}

void Map::setDebug(bool debug) {
	debug_ = debug;
}


