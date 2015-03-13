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

/*
 * textbox.cpp
 * Contains functions for controlling textboxes
 */

#include "textbox.h"

Textbox::Textbox()
{
	int i = 0;
	for ( i=0; i<MAXLINES; i++ )
		text[i] = NULL;
	textbox = NULL;
	linespace = 4;
	SetFG(255, 255, 255);
	SetBG(0, 0, 0);
	alignment = RIGHT;
	colorkey = 0; // hmm..
	x = 0;
	y = 0;
	visible = 1;
	width = 0;
	height = 0;
	layer = 0;
}

Textbox::Textbox(SDL_Surface *screen)
{
	int i = 0;
	for ( i=0; i<MAXLINES; i++ )
		text[i] = NULL;
	textbox = NULL;
	linespace = 4;
	SetFG(255, 255, 255);
	SetBG(0, 0, 0);
	alignment = RIGHT;
	colorkey = SDL_MapRGB(screen->format, 0, 0, 0); // black
	x = 0;
	y = 0;
	visible = 1;
	width = 0;
	height = 0;
	layer = 0;
}

Textbox::Textbox(SDL_Surface *screen, TTF_Font *newfont, char* string)
{
	int i = 0;
	for ( i=0; i<MAXLINES; i++ )
		text[i] = NULL;
	textbox = NULL;
	linespace = 4;
	SetFG(255, 255, 255);
	SetBG(0, 0, 0);
	alignment = RIGHT;
	font = newfont;
	colorkey = SDL_MapRGB(screen->format, 0, 0, 0); // black
	x = 0;
	y = 0;
	visible = 1;
	width = 0;
	height = 0;
	AddLine(string);
	ReCreate(screen);
	layer = 0;
}

Textbox::Textbox(SDL_Surface *screen, TTF_Font *newfont, char* string, int X, int Y)
{
	int i = 0;
	for ( i=0; i<MAXLINES; i++ )
		text[i] = NULL;
	textbox = NULL;
	linespace = 4;
	SetFG(255, 255, 255);
	SetBG(0, 0, 0);
	alignment = RIGHT;
	font = newfont;
	colorkey = SDL_MapRGB(screen->format, 0, 0, 0); // black
	x = X;
	y = Y;
	visible = 1;
	width = 0;
	height = 0;
	layer = 0;
	AddLine(string);
	ReCreate(screen);
}

Textbox::~Textbox()
{
	int i;
	for ( i=0; i<MAXLINES; i++ )
		if ( text[i] != NULL )
			SDL_FreeSurface( text[i] );

	if ( textbox != NULL )
		SDL_FreeSurface( textbox );
}

int Textbox::GetAlignment()
{
	return alignment;
}

void Textbox::SetAlignment(enum ALIGNMENT Alignment)
{
	alignment = Alignment;
}

int Textbox::SetFont(TTF_Font *newfont)
{
	if (newfont) font = newfont;
	else return 1;
	return 0;
}


void Textbox::SetFG(int r, int g, int b)
{
	fg.r = (int)r;
	fg.g = (int)g;
	fg.b = (int)b;
}

void Textbox::SetBG(int r, int g, int b)
{
	bg.r = (int)r;
	bg.g = (int)g;
	bg.b = (int)b;
}

int Textbox::AddLine(char* string)
{
	// Find first empty text-surface
	int i, empty = -1;
	for ( i=0; i<MAXLINES; i++ )
		if ( text[i] == NULL ) {
			empty = i;
			break; }

	//printf("(%u)AddLine: empty=%i, \"%s\"\n", int(this), empty, string);
	/* None are empty, text can not be added */
	if ( empty == -1 )
		return 1;

	// Render text on that surface
	if (!(text[empty] = GraphicDriver::prepareText(string, font, fg, bg)))
		return 1; // CreateSurface returns zero on failure

	SDL_SetColorKey(text[empty], SDL_SRCCOLORKEY, colorkey);
	// Update textbox-surface
	//return ReCreateTextbox(screen);
	return 0;
}

int Textbox::RemoveLine(int line)
{
	int i = 0;
	// Check if exists
	if(text[line] == NULL)
		return 1;

	// Remove surface
	SDL_FreeSurface(text[line]);
	text[line] = NULL;

	// Update text[] table
	/*
	text[line] = text[line+1];
	text[line+1] = text[line+2];
	...
	text[MAXLINES-2] = text[MAXLINES-1];
	done */

	for(i=line; i<MAXLINES-1; i++)
		text[i] = text[i+1]; // each pointer after "line" now points to
							 // the surface benieth it in the table,
							 // effectively bumping those surfaces one place up

	// The last one will be empty, since we've removed a line
	text[MAXLINES-1] = (int)NULL;

	return 0;
}

int Textbox::InsertLine(int line, char* string)
{
	// - Remove last surface if needed
	if(text[MAXLINES-1] != NULL) {
		SDL_FreeSurface( text[MAXLINES-1] );
		text[MAXLINES-1] = (int)NULL;
	}

	// Bump all pointers after 'line' one place down in the table.
/*	text[line+1] = text[line];
 *	text[line+2] = text[line+1];
 *	...
 *	text[MAXLINES-1] = text[MAXLINES-2];
 *	done
 *	-- this will duplicate all lines to one surface, so use reversed order.
 * text[MAXLINES-1] = text[MAXLINES-2];
 *	text[MAXLINES-2] = text[MAXLINES-3];
 *	...
 *	text[line+1] = text[line];
 *	done */

	int i = 0;
	for(i=MAXLINES-1; i>=line; i--)
		text[i] = text[i-1]; // each line (starting from the end of the table)
							 // now points to the surface before it

	// Create surface from string + Insert string
	if ( (text[line] = GraphicDriver::prepareText(string, font, fg, bg)) == NULL)
		return 1;
	// Set correct colorkey
	SDL_SetColorKey(text[line], SDL_SRCCOLORKEY, colorkey);

	return 0; // hmm?
}

void Textbox::Visible()
{ visible = 1; }

void Textbox::InVisible()
{ visible = 0; }

void Textbox::ShiftVisible()
{ visible = !visible; }

int Textbox::GetVisible()
{ return visible; }

int Textbox::GetHeight()
{ return height; }

int Textbox::GetWidth()
{ return width; }


int Textbox::ReCreate(SDL_Surface* screen)
{
	//int width = 0, height = 0, lineheight = 0, i = 0, blit = 0;
	width = 0; // reset width & height
	height = 0;
	int lineheight = 0, i = 0, blit = 0;

	// - Find width & height of textbox
	for ( i=0; i<MAXLINES; i++ ) {
		if ( text[i] != NULL ) {
			height += (text[i]->h + linespace); // update total height
			if ( text[i]->h > lineheight ) // get max height
				lineheight = text[i]->h;
			if ( text[i]->w > width ) // get max width
				width = text[i]->w;
		}
	}

	// - Destroy / remove old surface
	if (textbox != NULL) {
		SDL_FreeSurface( textbox );
		textbox = NULL;
	}

	// - Create new surface
	int status = (int)(textbox = 
		// hmm.. SW surface or HW surface?
		SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCCOLORKEY 
			| SDL_SRCALPHA | SDL_HWACCEL | SDL_RLEACCEL,
		width, height, screen->format->BitsPerPixel, screen->format->Rmask, 
		screen->format->Gmask, screen->format->Bmask, screen->format->Amask));
	
	if (!status) return 1; // CreateSurface returns zero on failure

	// Make the black (colorkey) transparent... or the ... bg transparent?
	SDL_SetColorKey(textbox, SDL_SRCCOLORKEY, colorkey);

	// - Blit text to new surface
	status = 0;
	for (i=0; i<MAXLINES; i++) {
		if (text[i] != NULL) {
			switch (alignment) {
				case RIGHT:
					blit = GraphicDriver::blit(textbox, text[i], 0,
							(lineheight+linespace)*i);
					break;
				case CENTER:
					blit = GraphicDriver::blit(textbox, text[i],
							(width/2)-(text[i]->w/2), (lineheight+linespace)*i);
					break;
				case LEFT:
					blit = GraphicDriver::blit(textbox, text[i], width-text[i]->w,
						(lineheight+linespace)*i);
					break;
			};
			if (blit) status = blit; // catch last non-zero (error) value
		}
	}
	return status;
}

int Textbox::Draw(SDL_Surface *screen)
{
	if (!visible) return 0; // if not visible, return OK
	return GraphicDriver::blit(screen, textbox, x, y);
}

int Textbox::Draw(SDL_Surface *screen, int X, int Y)
{
	if (!visible) return 0; // if not visible, return OK
	return GraphicDriver::blit(screen, textbox, X, Y);
}

void Textbox::SetColorKey(int newcolorkey)
{ colorkey = newcolorkey; }

void Textbox::SetXY(int X, int Y)
{
	x = X;
	y = Y;
}

int Textbox::GetX()
{ return x; }

int Textbox::GetY()
{ return y; }

void Textbox::SetLayer(int newlayer)
{ layer = newlayer; }

int Textbox::GetLayer()
{ return layer; }

SDL_Rect *Textbox::GetRect()
{
	SDL_Rect *rect = new SDL_Rect;

	rect->x = 0;
	rect->y = 0;
	rect->w = textbox->w;
	rect->h = textbox->h;

	return rect;
}
