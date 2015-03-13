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

#include "colorsurf.h"

ColorSurface::ColorSurface()
{
	Surface = NULL;
	Color = NULL;
	Rect = NULL;
	Alpha = 210;

	Color = new SDL_Color;
	Color->r = 30;
	Color->g = 30;
	Color->b = 70;
	//Color->a = Alpha;
	x = 0;
	y = 0;
	visible = 1;
	layer = 0;
}


ColorSurface::ColorSurface(SDL_Rect **rect)
{
	if (*rect) Rect = *rect;
	else Rect = NULL;
	Alpha = 210;
	x = 0;
	y = 0;
	visible = 1;
	layer = 0;
}

ColorSurface::ColorSurface(SDL_Rect **rect, int X, int Y)
{
	if (*rect) Rect = *rect;
	else Rect = NULL;
	Alpha = 210;
	x = X;
	y = Y;
	visible = 1;
	layer = 0;
}


ColorSurface::ColorSurface(SDL_Color **color, SDL_Rect **rect)
{
	Surface = NULL;
	if (*color) Color = *color;
	else Color = NULL;
	if (*rect) Rect = *rect;
	else Rect = NULL;
	Alpha = 210;
	x = 0;
	y = 0;
	visible = 1;
	layer = 0;
}

ColorSurface::ColorSurface(SDL_Color **color, SDL_Rect **rect, int X, int Y)
{
	Surface = NULL;
	if (*color) Color = *color;
	else Color = NULL;
	if (*rect) Rect = *rect;
	else Rect = NULL;
	Alpha = 210;
	x = X;
	y = Y;
	visible = 1;
	layer = 0;
}

ColorSurface::ColorSurface(SDL_Surface *screen, SDL_Color **color, 
		SDL_Rect **rect)
{
	Surface = NULL;
	if (*color) Color = *color;
	else Color = NULL;
	if (*rect) Rect = *rect;
	else Rect = NULL;
	Alpha = 210;
	x = 0;
	y = 0;
	visible = 1;
	layer = 0;
	ReCreate(screen);
}

ColorSurface::ColorSurface(SDL_Surface *screen, SDL_Color **color, 
		SDL_Rect **rect, int X, int Y)
{
	Surface = NULL;
	if (*color) Color = *color;
	else Color = NULL;
	if (*rect) Rect = *rect;
	else Rect = NULL;
	Alpha = 210;
	x = X;
	y = Y;
	visible = 1;
	layer = 0;
	ReCreate(screen);
}

ColorSurface::~ColorSurface()
{
	if (Surface)	delete Surface;	
	if (Color) 		delete Color;	
	if (Rect)		delete Rect;
}

int ColorSurface::ReCreate(SDL_Surface *screen)
{
	// Errorchecking:
	if (Rect == NULL || Color == NULL)
		return 1;
	
	// Delete old surface
	if (Surface != NULL)
		SDL_FreeSurface(Surface);
	
	// Create surface with right size
	SDL_Surface *temp;
	int status = (int)(temp = 
		SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA,
		Rect->w, Rect->h, 
		//screen->format->BitsPerPixel, screen->format->Rmask, 
		32, screen->format->Rmask, 
		screen->format->Gmask, screen->format->Bmask, 
			screen->format->Amask));

	if (!status) return 1;
		
	// Enable alphablending on surface (and set opaque)
	//SDL_SetAlpha(Surface, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(temp, SDL_SRCALPHA, Alpha);
	
	Surface = temp;
	//Surface = SDL_DisplayFormatAlpha(temp);
	//SDL_FreeSurface(temp);

	// And finally draw it
	return DrawSurface(screen);
}

int ColorSurface::DrawSurface(SDL_Surface *screen)
{
	/* Fill with right color */
	return SDL_FillRect(Surface, 0, // zero means fill the whole surface
		SDL_MapRGBA(screen->format, Color->r, Color->g, Color->b, Alpha)); 
}

int ColorSurface::SetColor(SDL_Color **newcolor)
{
	if (*newcolor == NULL)
		return 1;
	
	if (Color)
		delete Color;
	
	Color = *newcolor;
	return 0;
}

void ColorSurface::SetAlpha(int newalpha)
{
	if (newalpha < 0 || newalpha > 255) return;
	
	Alpha = newalpha;
}
	
SDL_Color *ColorSurface::GetColor()
{
	return Color;
}

SDL_Rect *ColorSurface::GetRect()
{
	return Rect;
}

void ColorSurface::SetXY(int X, int Y)
{
	// Notice: no errorchecking
	x = X;
	y = Y;
}

void ColorSurface::Visible()
{ visible = 1; }

void ColorSurface::InVisible()
{ visible = 0; }

void ColorSurface::ShiftVisible()
{ visible = !visible; }

int ColorSurface::GetVisible()
{ return visible; }

int ColorSurface::GetX()
{ return x; }

int ColorSurface::GetY()
{ return y; }

int ColorSurface::GetHeight()
{ return Surface->h; }

int ColorSurface::GetWidth()
{ return Surface->w; }

void ColorSurface::SetLayer(int newlayer)
{ layer = newlayer; }

int ColorSurface::GetLayer()
{ return layer; }

int ColorSurface::Draw(SDL_Surface *screen)
{
	if (visible)
		return GraphicDriver::blit(screen, Surface, x, y);
	return 0; // Meaning OK
}

int ColorSurface::Draw(SDL_Surface *screen, int X, int Y)
{
	// This doesn't change the objects position (x,y), 
	// so a Draw(screen) command would use the old (x,y)
	// Use SetXY(X,Y) for that
	if (visible)
		return GraphicDriver::blit(screen, Surface, X, Y);
	return 0; // Meaning OK
}

int ColorSurface::SetRect(SDL_Rect **rect)
{
	if (*rect == NULL) return 1;
	if (Rect != NULL)
		delete Rect;
	
	Rect = *rect;
	return 0;
}
