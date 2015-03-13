#include "input.h"

enum Input::USERACTION Input::getAction(void)
{
	USERACTION lastvalue = NOTHING;	
	SDL_Event event;
	SDL_keysym keysym;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type) 
		{
			case SDL_KEYDOWN:	
				keysym = event.key.keysym;
				switch (keysym.sym) 
				{
					case SDLK_UP:    lastvalue = GOUP;
						break;
					case SDLK_DOWN:	 lastvalue = GODOWN;
						break;
					case SDLK_LEFT:	 lastvalue = GOLEFT;
						break;
					case SDLK_RIGHT: lastvalue = GORIGHT;
						break;

					case SDLK_PAUSE:
					case SDLK_BREAK: lastvalue = PAUSE;
						break;

				// case SDLK_RETURN:
					case SDLK_ESCAPE:
					case SDLK_q:
						return EXITSTATE;

					default:				
						break;
				};	
				break; // loop the while

			case SDL_QUIT:	
				return SHUTDOWN; // recieved kill signal

			default:			
				break; // loop the while
		};	 
	}; 
	
	return lastvalue;
	// that's right, everything else gets ignored
}	

