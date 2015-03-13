#ifndef __gamegraphics_h__
#define __gamegraphics_h__

#include "SDL/SDL.h"

#include "graphicdriver.h"
#include "sprite.h"
#include "blockswindow.h"
#include "nextblockwindow.h"
#include "fps.h"
#include "gameresc.h"
#include "scorewindow.h"

#include "dialog.h"

/**
 * GameGraphics is superior to all other classes that deal with graphics
 * in the game. Note: just the game, not the menu (they have their own
 * code to deal with).
 *
 */
class GameGraphics
{
	private:
		BlocksWindow *blocksWindow;
		NextBlockWindow *nextBlockWin;
		FPS *fps;
		ScoreWindow *scoreWindow; // gives us score
		GraphicDriver *graphicDrv;
		GameResc *resc;

		SDL_Surface *background; // just for now

	public:
		GameGraphics(void);
		~GameGraphics(void);

		void setup(void);
		void refresh(void); 
		
		void endGame(int points);

};

#endif
