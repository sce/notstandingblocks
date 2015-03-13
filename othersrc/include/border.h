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

#ifndef BORDER_H
#define BORDER_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

//#include "functions.h"
//#include "../graphics.h"
#include "colorsurf.h"

class Border : public ColorSurface {
	protected:
		int Thicknes;
		int DrawSurface(SDL_Surface *screen);
	
	public:
		Border();
		Border(SDL_Rect **rect);
		Border(SDL_Rect **rect, int X, int Y);
		Border(SDL_Color **color, SDL_Rect **rect);
		Border(SDL_Color **color, SDL_Rect **rect, int X, int Y);
		~Border();
		void SetThicknes(int newthicknes);
		int  GetThicknes();
};

#endif
