#ifndef __GAMEBLOCKWINDOWG_H__
#define __GAMEBLOCKWINDOWG_H__

#include "SDL/SDL.h"

#include "gameresc.h"

#include "graphicdriver.h"
#include "sprite.h"
#include "block.h"
#include "map.h"
#include "gameengine.h"
#include "blockswindow.h" // to get height and such

#include "box.h"
#include "graphicobject.h"

/*
 * Gives us a surface picturing the next block arriving.
 *
 */

class NextBlockWindow : public GraphicObject
{
	private:

		GameResc resc; // GameResources
		Box backgroundBox;
		GameEngine gameEngine_; // need to get nextBlock...
		Block *nextBlock;

	public:
		NextBlockWindow(void);
		~NextBlockWindow(void);

		void setup();
		void blitTo(SDL_Surface *screen);
};


#endif
