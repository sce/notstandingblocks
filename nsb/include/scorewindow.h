#ifndef __SCOREWINDOW_H__
#define __SCOREWINDOW_H__

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "graphicdriver.h"
#include "dialog.h"
#include "gameengine.h" // needs to get the score..

#include "graphicobject.h"
#include "gameresc.h"

/** 
 * Creates a surface with the current score written on it.
 */
class ScoreWindow : public GraphicObject
{
	private:

		Dialog dialogBox;
		GameResc resc;

		char text_[16]; // holds the text for the score
		int score; // holds the current score
		
		void refresh(void);
		void forceRefresh(void);
		
	public:
		ScoreWindow(void);
		~ScoreWindow(void);

		void setup();		
		void blitTo(SDL_Surface *screen);
};

#endif
