/*
 * Copyright 2004 Sten Christoffer Eliesen
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
/*
 * sprite.h 
 * Made by S. Christoffer Eliesen
 * June 3rd 2004
 */

#ifndef SPRITE_H
#define SPRITE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "graphicdriver.h"

/* load images in frames, draw them */

class Sprite {
	protected:
		SDL_Surface **imgs_;
		unsigned int frames_;
		//GraphicDriver graphics_;
		//int visible_; // a global value. needed?

	public:
		Sprite(unsigned int frames);
		~Sprite();
		int loadFrame(unsigned int frame, SDL_Surface* surf);
		int draw(SDL_Surface *screen, unsigned int frame, int x, int y);
		int getFrames();
};


#endif
