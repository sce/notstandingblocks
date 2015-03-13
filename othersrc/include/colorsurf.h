/***************************************************************************
 *            colorsurf.h
 *
 *  Wed May  5 12:21:07 2004
 *  Copyright  2004  User
 *  Email
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

#ifndef __COLORSURF_H__
#define __COLORSURF_H__

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"


//#include "functions.h"
//#include "graphics.h"
#include "graphicdriver.h"

class ColorSurface {
	protected:
		SDL_Surface *Surface;
		SDL_Color	*Color;
		SDL_Rect		*Rect;
		int Alpha;
		int x; // Where to draw it?
		int y; 
		int visible; // Draw it, or not?
		int layer; // when is it drawn?

		virtual int DrawSurface(SDL_Surface *screen); // The last function called 
			// from ReCreate, and should be overloaded by childeren
			// Needs to be virtual or else ColorSurface::ReCreate() will use
			// this class' DrawSurface, instead of childrens DrawSurface.
	
	public:
		ColorSurface();
		ColorSurface(SDL_Rect **rect);
		ColorSurface(SDL_Rect **rect, int X, int Y);
		ColorSurface(SDL_Color **color, SDL_Rect **rect);
		ColorSurface(SDL_Color **color, SDL_Rect **rect, int X, int Y);
		ColorSurface(SDL_Surface *screen, SDL_Color **color, SDL_Rect **rect);
		ColorSurface(SDL_Surface *screen, SDL_Color **color, SDL_Rect **rect, 
				int X, int Y);

		virtual ~ColorSurface();

		SDL_Color *GetColor();
		SDL_Rect  *GetRect();

		void SetXY(int X, int Y);
		int  GetX();
		int  GetY();
		int  GetHeight();
		int  GetWidth();

		int  SetRect(SDL_Rect **rect);
		int  SetColor(SDL_Color **color);
		void SetAlpha(int newalpha);

		void Visible();
		void InVisible();
		void ShiftVisible();
		int  GetVisible();

		void SetLayer(int newlayer);
		int  GetLayer();

		int  ReCreate(SDL_Surface *screen);
		int  Draw(SDL_Surface *screen);
		int  Draw(SDL_Surface *screen, int X, int Y);
};

#endif
