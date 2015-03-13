#ifndef __game_h__
#define __game_h__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // for usleep(usecs);

#include "SDL/SDL.h"

#include "log.h"
#include "input.h"
#include "gameengine.h"
#include "gamegraphics.h"
#include "gameaudio.h"
#include "dialog.h"
#include "gameresc.h"
#include "graphicdriver.h"

class Game
{
	public:
		enum USERACTION {
			NOTHING,
			SHUTDOWN,		// shutdown: user is killing the application
			EXITSTATE,		// exitstate: user is hitting escape, wants to get
			PAUSE,				// out of current state (pause/running maybe)

			MUSICON,
			MUSICOFF,
			SOUNDON,
			SOUNDOFF,

			GOLEFT,
			GORIGHT,
			ROTATEBLOCK
		};

		Game(void);
		virtual ~Game(void);
		
		int run(void); // just do it. returns collected score

	private:
		GameGraphics *gameGraphics; // the screen
		GameAudio *gameAudio; // the sound
		GameEngine *gameEngine; // Game Engine
		//GameResc resc;
		//GraphicDriver graphicDrv;
		
		LOG::LOGLEVEL wantloglevel_;

		bool playGame_; 
		bool pause_;
		unsigned int moveUpdateDelay_; // this gets lower during play

		void cleanup(void);
		void respondToInteraction(Input::USERACTION);
		bool catchKeyPress(void);

};



#endif /* __game_h__ */
