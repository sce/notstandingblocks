#ifndef __input_h__
#define __input_h__

#include <stdlib.h>
#include <stdio.h>

#include "SDL/SDL.h"

class Input
{
	private:

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
			GOUP,		
			GODOWN		
			//ROTATEBLOCK	// not used in menu
		};

		Input(void);
		static enum USERACTION getAction(void);
};

#endif
