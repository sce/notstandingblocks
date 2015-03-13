#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // for usleep(usecs);
//#include <stack>

#include "SDL/SDL.h"

#include "map.h"
#include "block.h"
#include "gameresc.h"

class GameEngine 
{
	public:
		static const int DEAD;

		GameEngine(void);
		~GameEngine(void);

		void cleanup(void);
		static void setLoglevel(LOG::LOGLEVEL loglevel);

		void startNew(void);
		// old: returns "alive": true/false
		// returns: number of rows removed this frame
		// or -1 if dead, or -2 if new block falling
		int  doOneFrame(void); 
		void actBlockFallNow(void); // Make active block fall now

		void rotateBlock(void);
		void setdx(int dx);
		void setdy(int dy);
		int  getdx(void);
		int  getdy(void);

		Block *getNextBlock(void);

		static unsigned int getScore(void);

	private:

		//  use this to force messages of 'wantloglevel' or higher through always
		static LOG::LOGLEVEL wantloglevel_; 

		Block *actBlock_; 
		Block *prevBlock_;; 
		static Block *nextBlock_; 

		int dx_; // update in movement every fallInterval_
		int dy_; 

		static unsigned int score_;

		static const unsigned int INITIALFALLINTERVAL;

		unsigned int fallInterval_; 
		unsigned int nextFallUpdate_;

		int movesSinceLastCrash_;
		
		bool deleteRow[GameResc::MAPY];

		bool wait_; // should it wait? (happens after a crash)
		unsigned int nextRowDeleteUpdate_; // when to delete the marked rows

		bool fallNow; // Make active block fall right now between pause?		
		// when to put previous block premanent on map
		unsigned int nextPrevBlockUpdate_; 

		void putBlockOnMap(Block* block, int value);

		void putActBlockOnMap(void); // use value from block (blocktype)
		void putActBlockOnMap(int value);

		void putActBlockPermOnMap(void); // rotates prev/active/next-block
		void putPrevBlockPermOnMap(void); // finally cleans up

		void removeActBlockFromMap(void);

		int  removeMarkedRows(void);
		int  markFullRows(void);

		int  removeFullRows(void);
};

#endif
