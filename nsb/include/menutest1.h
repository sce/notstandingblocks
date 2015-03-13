#ifndef MENUTEST1_H_
#define MENUTEST1_H_

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

#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "box.h"
#include "textbox.h"
#include "dialog.h"
#include "selector.h"

#include "graphicdriver.h"
#include "gameresc.h"
#include "game.h"

class Menu {
private:
	static const int MAX_OBJECTS = 256;
	static const int MAX_LAYERS = 16;
	
	Textbox *textboxes[MAX_OBJECTS];
	Dialog *dialogs[MAX_OBJECTS];
	Selector *selectors[MAX_OBJECTS];
	
	int tp; // textboxes-pointer
	int dp; // dialogs-pointer
	int sp; // selectors-pointer
	int toplayer; // which is the highest level? -> meant to ease computation
	int menuposition; // which selector is selected?

	const char *VERSION;
	const char *DATE;
	
	// For easy reffering: make global pointers to all objects 
	Selector *startsel;
	Selector *aboutsel;
	Selector *quitsel;
	Dialog *aboutdia;
	Textbox *welcometxt;
	
	SDL_Surface *background;
	Game *nsb;
	GameAudio *audio; // heh.. menuaudio anyone?

	GraphicDriver *graphicDrv;
	GameResc *resc; // GameResources

	int Quit;

	enum STATE { // which state is the menu in, as in what is it displaying
		MENU,
		ABOUT
	};

	STATE state;
	
	// ---------
	void ChangeState(enum STATE newstate);
	void UpdateDisplay(SDL_Surface *screen);
	void UpdateMenu(SDL_Surface *screen);
	void AboutKeyHandler(SDL_Surface *screen);
	void MenuKeyHandler(SDL_Surface *screen);
	void KeyHandler(SDL_Surface *screen);
	int  initprog();

public:
	Menu();
	virtual ~Menu();

	int  menutest();	
};

#endif /*MENUTEST1_H_*/
