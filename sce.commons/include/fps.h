#ifndef __FPS_H__
#define __FPS_H__

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "graphicdriver.h"
#include "graphicobject.h"
#include "resources.h" // this will be moved to sce.commons

/**
 * Creates a surface with the text "FPS: fps@time" written on it.
 */

class FPS : protected GraphicObject
{
	private:
		int fps_;
		int previous_;
		char string_[16];

		SDL_Color bg_;
		SDL_Color fg_;

		Resources resc;
		SDL_Surface *text_;

		void refresh();

	public:
		FPS(void);
		~FPS(void);

		void setup();
		void blitTo(SDL_Surface *screen);
};

#endif
