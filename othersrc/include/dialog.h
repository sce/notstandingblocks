/***************************************************************************
 *            dialog.h
 *
 *  Sat May  2 13:10:00 2004
 *  Copyright  2004  S. Christoffer Eliesen
 *  Christoffer.Eliesen@GMail.com
 *
 *  Creates a dialogbox, using class Box and class TextBox combined.
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

#ifndef DIALOG_H
#define DIALOG_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

//#include "functions.h"
//#include "../graphics.h"
#include "box.h"
#include "textbox.h"

class Dialog {
	protected:
		int margin;
		Box *bgBox;
		Textbox *txtBox;
	
		int  layer; // when is it drawn? the higher the layer, the later drawn

		int  DrawSurface(SDL_Surface *screen);
		int  ReCreateBox(SDL_Surface *screen);
		int  ReCreateText(SDL_Surface *screen);
	
	public:
		Dialog();
		Dialog(SDL_Surface *screen, TTF_Font *font, char* text);
		Dialog(SDL_Surface *screen, TTF_Font *font, char* text, int X, int Y);
		Dialog(SDL_Surface *screen, SDL_Color **bgcolor, SDL_Color **framecolor,
			TTF_Font *font, char* text);
		Dialog(SDL_Surface *screen, SDL_Color **bgcolor, SDL_Color **framecolor,
			TTF_Font *font, char* text, int X, int Y);

		~Dialog();

		int  SetFont(TTF_Font *newfont);
		void SetFontColor(int r, int g, int b);
		int  SetBackgroundColor(SDL_Color **color);
		int  SetFrameColor(SDL_Color **color);

		void SetMargin(int newmargin);	
		void SetAlignment(enum ALIGNMENT);
		int  GetAlignment();

		int  AddLine(char* string);
		int  InsertLine(int line, char* string);
		int  RemoveLine(int line);

		void SetXY(int X, int Y);
		int  GetX();
		int  GetY();
		int  GetWidth();
		int  GetHeight();

		void Visible();
		void InVisible();
		void ShiftVisible();
		int  GetVisible();

		void SetLayer(int newlayer);
		int  GetLayer();

		void SetThicknes(int thicknes);
		int  GetThicknes();

		void UpdateBox(); // Update rect-struct of bgBox
		int  ReCreate(SDL_Surface *screen);
		int  Draw(SDL_Surface *screen);
		int  Draw(SDL_Surface *screen, int x, int y);
};
#endif
