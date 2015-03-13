#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <stdlib.h>
#include <stdio.h>
//#include <math.h> // for rand()
#include <time.h> // for time() (use with rand())

#include "log.h"
#include "gameresc.h"
//#include "map.h"
#include "point.h"

#include <list>

class Block 
{
	public:
		static const int BLOCKTYPES; // how many blocktypes
		enum BLOCKTYPE {
			LINEBLOCK, // = 0
		 	LBLOCK,		
			TBLOCK,
			SQUAREBLOCK
		};
		static const int MAXSQUARES = 5; 

		static void setLoglevel(LOG::LOGLEVEL wantloglevel); 

		Block (void);

		void createRandomBlock(void);
		void move(int dx, int dy); // move (+dx,+dy) coordinates		
		void rotateCW(); // rotate once clockwise
		void rotateCCW(); // rotate once counter clockwise

		int getDirection(void); // returns current direction
		int getBlocktype(void);
		int getCenterX();
		int getCenterY();

		Point *getCoordinates(int index); // returnes point nr Index		
		void copyFrom(Block* block);
		
	private:
		static LOG::LOGLEVEL wantloglevel_; 

		BLOCKTYPE blocktype_;

		static int lineBlock0[];
		static int lineBlock90[];

		static int lBlock0[];
		static int lBlock90[];
		static int lBlock180[];
		static int lBlock270[];
		
		static int tBlock0[];
		static int tBlock90[];
		static int tBlock180[];
		static int tBlock270[];
		
		static int sqBlock0[];

		static int *blockValues[][4];
		//static int blockValues[][4][10];
		
		int direction_;
		int *relCoords; // Relative coords
		int centerX;
		int centerY;
		
		void startRand(void);
		void rotate(); 	// Make sure relCoords are correct
};

#endif
