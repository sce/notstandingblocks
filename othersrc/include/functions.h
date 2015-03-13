/***************************************************************************
 *            functions.c
 *
 *  Tue Mar 23 12:23:21 2004
 *  Copyright  2004  User (some taken from sdl-book..)
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

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

TTF_Font *SCE_OpenFont( const char* font, int ptsize );
/* Errorproof loading of ttf font */

SDL_Surface *SCE_SetVideoMode( int w, int h, int bpp, Uint32 flags );
/* Errorproof SDL_SetVideoMode */

SDL_Surface *LoadImage ( char* imagename );
/* Errorproof loading of image, returns image in correct display format. */

int Blit ( SDL_Surface *screen, SDL_Surface *surface, int x, int y );
/* Blit surface onto screen */

SDL_Surface *PrepareText( char* text, TTF_Font *font, SDL_Color fg, SDL_Color bg );
/* Return text rendered on surface with font and fb/bg */

SDL_Surface* PrintText ( SDL_Surface *screen, int x, int y, char* text, TTF_Font *font, SDL_Color fg, SDL_Color bg);
/* Prints text on screen at (x,y), with font and fg/bg color. */

#endif
