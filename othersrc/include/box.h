/***************************************************************************
 *            box.h
 *
 *  Sat May  1 19:16:15 2004
 *  Copyright  2004  S. Christoffer Eliesen
 *  Christoffer.Eliesen@NRKpost.no
 *
 *  Creates a box meant to put text into, width background color/picture,
 *  and borders pluss alphablending.
 ****************************************************************************
 *
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

#ifndef BOX_H
#define BOX_H

//#include "functions.h"
//#include "../graphics.h"
#include "colorsurf.h"
#include "border.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <unistd.h> // required for sleep(int)

class Box {
	protected:
		ColorSurface *Background; // since SDL_FillRect() wont allow alphavalues,
		Border *Frame;  // a separate surface for the border is needed

		int visible;
		int layer; // when is it drawn? the higher the layer the later drawn
		int DrawSurface(SDL_Surface *screen);
	
	public:
		Box();
		Box(SDL_Color **bgcolor, SDL_Color **framecolor, SDL_Rect **rect);
		Box(SDL_Color **bgcolor, SDL_Color **framecolor, SDL_Rect **rect, 
				int X, int Y);
		Box(SDL_Surface *screen, SDL_Color **bgcolor, SDL_Color **framecolor, 
			SDL_Rect **rect);
		Box(SDL_Surface *screen, SDL_Color **bgcolor, SDL_Color **framecolor, 
			SDL_Rect **rect, int X, int Y);

		~Box();

		void SetXY(int X, int Y);
		int  GetX();
		int  GetY();
		int  GetWidth();
		int  GetHeight();

		int  SetBackgroundColor(SDL_Color **color);
		int  SetFrameColor(SDL_Color **color);
		int  SetRect(SDL_Rect **rect);

		void Visible();
		void InVisible();
		void ShiftVisible();
		int  GetVisible();

		void SetThicknes(int thicknes);
		int  GetThicknes();

		void SetLayer(int newlayer);
		int  GetLayer();

		int  ReCreate(SDL_Surface *screen);
		int  Draw(SDL_Surface *screen);
		int  Draw(SDL_Surface *screen, int x, int y);
		SDL_Rect *GetRect();
};
#endif
