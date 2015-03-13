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

#include "border.h"

Border::Border() : ColorSurface()
{
	Thicknes = 2;
	Alpha = 150;
	Color->r = 100;
	Color->g = 100;
	Color->b = 150;
}


Border::Border(SDL_Rect **rect) : ColorSurface(rect)
{
	Thicknes = 2;
	Alpha = 150;
	Color->r = 100;
	Color->g = 100;
	Color->b = 150;
}

Border::Border(SDL_Rect **rect, int X, int Y) : ColorSurface(rect, X, Y)
{
	Thicknes = 2;
	Alpha = 150;
	Color->r = 100;
	Color->g = 100;
	Color->b = 150;
}

Border::Border(SDL_Color **color, SDL_Rect **rect) : ColorSurface(color, rect)
{
	Thicknes = 2;
	Alpha = 150;
	Color->r = 100;
	Color->g = 100;
	Color->b = 150;
}

Border::Border(SDL_Color **color, SDL_Rect **rect, int X, int Y) : ColorSurface(color, rect, X, Y)
{
	Thicknes = 2;
	Alpha = 150;
	Color->r = 100;
	Color->g = 100;
	Color->b = 150;
}

Border::~Border()
{
	/* hmm */
}

void Border::SetThicknes(int newthicknes)
{
	if (newthicknes < 0) return;
	Thicknes = newthicknes;
}

int Border::GetThicknes()
{
	return Thicknes;
}

int Border::DrawSurface(SDL_Surface *screen)
{
	int status = 0, black = SDL_MapRGBA(screen->format, 
			0, 0, 0, 255);
	
	// Enable colorkey (since this is a border/frame, and the middle
	// will be transparent)
	SDL_SetColorKey(Surface, SDL_SRCCOLORKEY, black);

	// Draw top line
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = Rect->w;
	rect.h = Thicknes;

	status = SDL_FillRect(Surface, &rect, SDL_MapRGBA(screen->format, 
		Color->r, Color->g, Color->b, Alpha));

	if ( status != 0 )
		return status;

	// Draw bottom line
	rect.y = Rect->h-Thicknes;

	status = SDL_FillRect(Surface, &rect, SDL_MapRGBA(screen->format, 
		Color->r, Color->g, Color->b, Alpha));

	if ( status != 0 ) 
		return status;		

	// Draw left line
	rect.x = 0;
	rect.y = 0;
	rect.w = Thicknes;
	rect.h = Rect->h;

	status = SDL_FillRect(Surface, &rect, SDL_MapRGBA(screen->format, 
		Color->r, Color->g, Color->b, Alpha));

	if ( status != 0 ) 
		return status;

	// Draw right line
	rect.x = Rect->w-Thicknes;

	return SDL_FillRect(Surface, &rect, SDL_MapRGBA(screen->format, 
		Color->r, Color->g, Color->b, Alpha));
}
