/***************************************************************************
 *            selector.h
 *
 *  Tue May  4 21:22:20 2004
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

#ifndef SELECTOR_H
#define SELECTOR_H
#include "dialog.h"

enum SELECTOR {
	SELECTED,
	UNSELECTED,
	BOTH
};


class Selector {
	protected:
		Dialog *Selected;
		Dialog *UnSelected;

		int layer; // when is it drawn? the higher the layer, the later drawn
		enum SELECTOR selected; // which one to display?

	public:
		Selector();
		Selector(SDL_Surface *screen, TTF_Font *font, char* string);
		~Selector();

		void Shift(); // Change state (selected/unselected)
		void Select(); // Change to state "selected"
		void UnSelect(); // Change to state "unselected"

		int  SetFont(enum SELECTOR, TTF_Font *newfont);
		void SetFontColor(enum SELECTOR, int r, int g, int b);
		int  SetBackgroundColor(enum SELECTOR, SDL_Color **color);
		int  SetFrameColor(enum SELECTOR, SDL_Color **color);

		void SetMargin(enum SELECTOR, int newmargin);	
		void SetAlignment(enum SELECTOR, enum ALIGNMENT);
		int  GetAlignment(enum SELECTOR);

		int  AddLine(enum SELECTOR, char* string);
		int  InsertLine(enum SELECTOR, int line, char* string);
		int  RemoveLine(enum SELECTOR, int line);

		void Visible();
		void InVisible();
		void ShiftVisible();
		int  GetVisible();

		void SetLayer(int newlayer);
		int  GetLayer();

		void SetThicknes(enum SELECTOR, int thicknes);
		int  GetThicknes(enum SELECTOR);

		void SetXY(int X, int Y);
		int  GetX();
		int  GetY();
		int  GetWidth();
		int  GetHeight();

		//void UpdateBox(); // Update rect-struct of bgBox
		int  ReCreate(SDL_Surface *screen);
		int  Draw(SDL_Surface *screen);
		int  Draw(SDL_Surface *screen, int x, int y);
};

#endif
