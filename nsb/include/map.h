#ifndef __Map_h__
#define __Map_h__

#include <stdlib.h>
#include <stdio.h>

#include "log.h"
#include "block.h"
#include "gameresc.h"

#include "point.h" // redundant, but still

class Map 
{
	public:

		static const int EMPTY = 0; // for the map: empty, in the future those 
							// ints in the map will point to a texture index, woohoo!
		static const int SQUARE0 = 1; // for the map: a used square
		static const int SQUARE1 = 2; // for the map: a used square
		static const int SQUARE2 = 3; // for the map: a used square

		static const int MAPX = GameResc::MAPX;
		static const int MAPY = GameResc::MAPY;

	private:
		bool debug_;

		static int map_[GameResc::MAPX][GameResc::MAPY]; // defines an array of squares making out a map

		static void setXY(int x, int y, int value);

	public:
		Map(void);

		void setDebug(bool);

		static int  getXY(int x, int y); // causing a lot of overhead?

		static void startNew(void);
		static void markFullRow(int row);
		static void removeRow(int row);

		static bool doesCollide(Block *block);		
		static void putBlockOnMap(Block *block, int value);
		static void removeBlockFromMap(Block *block);		
};

#endif /* __Map_h__ */
