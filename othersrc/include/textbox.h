/***************************************************************************
 *            textbox.h
 *
 *  Tue Apr 27 13:17:57 2004
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

#ifndef TEXTBOX_H
#define TEXTBOX_H

//#include "functions.h"
//#include "graphics.h"
#include "graphicdriver.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#define MAXLINES 128 // Legacy: 128, should be dynamic though

enum ALIGNMENT { RIGHT, CENTER, LEFT };

class Textbox {
	protected:
		SDL_Surface *textbox;
		SDL_Surface *text[MAXLINES];
		TTF_Font 	*font;

		SDL_Color fg; // foreground color
		SDL_Color bg; // background color. should always be black though... no?

		int linespace;
		int alignment; // RIGHT, CENTER, LEFT
		int colorkey; // Which color is transparent?
		int visible;
		int layer; // when is it drawn? the higher the layer, the later drawn
	
		int width;
		int height;
		int x;
		int y;

	public:
		Textbox();
		Textbox(SDL_Surface *screen);
		Textbox(SDL_Surface *screen, TTF_Font *newfont, char* text);
		Textbox(SDL_Surface *screen, TTF_Font *newfont, char* text, int X, int Y);
		~Textbox();

		void SetXY(int X, int Y);
		int  SetFont(TTF_Font *newfont);
		void SetBG(int r, int g, int b);
		void SetFG(int r, int g, int b);
		void SetColorKey(int newcolorkey);

		void SetAlignment(enum ALIGNMENT);
		int  GetAlignment();

		int  AddLine(char* string);
		int  InsertLine(int line, char* string);
		int  RemoveLine(int line);

		void Visible();
		void InVisible();
		void ShiftVisible();
		int  GetVisible();

		void SetLayer(int newlayer);
		int  GetLayer();

		int  GetX();
		int  GetY();
		int  GetWidth();
		int  GetHeight();
		SDL_Rect* GetRect();

		int  Draw(SDL_Surface *screen);
		int  Draw(SDL_Surface *screen, int x, int y);
		int  ReCreate(SDL_Surface *screen);
};
#endif
