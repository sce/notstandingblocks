#ifndef __blockswindow_h__
#define __blockswindow_h__

#include <stdlib.h>
#include <stdio.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "gameresc.h"
#include "map.h"	 // it needs to know what to draw
#include "graphicdriver.h" // it needs to know _how_ to draw ;)
#include "graphicobject.h"

/*
 * BlocksWindow handles the graphical window where the blocks are falling
 * (the game in short).
 *
 */

class BlocksWindow : protected GraphicObject
{
	private:

		SDL_Surface *background; 
		GameResc *resc; // GameResources

	public:
		static const unsigned int SQUARETILES; // # of non-empty tiles/pics
		static const unsigned int EMPTYTILES; // # of empty tiles/pics

		static const unsigned int SQWIDTH; // the width of a square in pixels
		static const unsigned int SQHEIGHT; // the height of a square in pixels

		BlocksWindow(void);
		~BlocksWindow(void);

		void setup();	
		void blitTo(SDL_Surface *screen);
};


#endif
