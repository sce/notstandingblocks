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

#include "selector.h"

Selector::Selector()
{
	selected = UNSELECTED;

	Selected   = new Dialog();
	UnSelected = new Dialog();

	SDL_Color *bg = new SDL_Color;
	bg->r = 20;
	bg->g = 20;
	bg->b = 40;
	UnSelected->SetBackgroundColor(&bg);

	SDL_Color *frame = new SDL_Color;
	frame->r = 55;
	frame->g = 55;
	frame->b = 105;
	UnSelected->SetFrameColor(&frame);
	layer = 0;
}

Selector::Selector(SDL_Surface *screen, TTF_Font *font, char* string)
{
	selected = UNSELECTED;

	Selected    = new Dialog(screen, font, string);
	UnSelected  = new Dialog();
	
	// Make it look darker as default
	UnSelected->SetFont(font);
	UnSelected->SetFontColor(150, 150, 150);

	UnSelected->AddLine(string);

	SDL_Color *bg = new SDL_Color;
	bg->r = 20;
	bg->g = 20;
	bg->b = 40;
	UnSelected->SetBackgroundColor(&bg);

	SDL_Color *frame = new SDL_Color;
	frame->r = 55;
	frame->g = 55;
	frame->b = 105;
	UnSelected->SetFrameColor(&frame);
	layer = 0;
}	

Selector::~Selector()
{
	if (Selected)   delete Selected;
	if (UnSelected) delete UnSelected;
}

void Selector::Select()
{ selected = SELECTED; }

void Selector::UnSelect() 
{ selected = UNSELECTED; }
	
void Selector::Shift() 
{
	if ( selected == SELECTED )
		selected = UNSELECTED;
	else
		selected = SELECTED;
}

int  Selector::SetFont(enum SELECTOR selector, TTF_Font *newfont)
{
	int status = 0;
	switch (selector) {
		case SELECTED:
			return Selected->SetFont(newfont);
		case UNSELECTED:
			return UnSelected->SetFont(newfont);
		case BOTH:
			status = Selected->SetFont(newfont);
			if (status) return status;
			return UnSelected->SetFont(newfont);

		default:
			return 1;
	}
}

void Selector::SetFontColor(enum SELECTOR selector, int r, int g, int b)
{
	switch (selector) {
		case SELECTED:
			Selected->SetFontColor(r, g, b);
			break;
		case UNSELECTED:
			UnSelected->SetFontColor(r, g, b);
			break;
		case BOTH:
			Selected->SetFontColor(r, g, b);
			UnSelected->SetFontColor(r, g, b);
		default:
			return;
	}
}

int  Selector::SetBackgroundColor(enum SELECTOR selector, SDL_Color **color)
{
	int status = 0;
	switch (selector) {
		case SELECTED:
			return Selected->SetBackgroundColor(color);
		case UNSELECTED:
			return UnSelected->SetBackgroundColor(color);
		case BOTH:
			status = Selected->SetBackgroundColor(color);
			if (status) return status;
			return UnSelected->SetBackgroundColor(color);

		default:
			return 1;
	}
}

int  Selector::SetFrameColor(enum SELECTOR selector, SDL_Color **color)
{
	int status = 0;
	switch (selector) {
		case SELECTED:
			return Selected->SetFrameColor(color);
		case UNSELECTED:
			return UnSelected->SetFrameColor(color);
		case BOTH:
			status = Selected->SetFrameColor(color);
			if (status) return status;
			return UnSelected->SetFrameColor(color);

		default:
			return 1;
	}
}

void Selector::SetMargin(enum SELECTOR selector, int newmargin)
{
	switch (selector) {
		case SELECTED:
			Selected->SetMargin(newmargin);
			break;
		case UNSELECTED:
			UnSelected->SetMargin(newmargin);
			break;
		case BOTH:
			Selected->SetMargin(newmargin);
			UnSelected->SetMargin(newmargin);
			break;
		default:
			return;
	}
}

void Selector::SetAlignment(enum SELECTOR selector, enum ALIGNMENT alignment)
{
	switch (selector) {
		case SELECTED:
			Selected->SetAlignment(alignment);
			break;
		case UNSELECTED:
			UnSelected->SetAlignment(alignment);
			break;
		case BOTH:
			Selected->SetAlignment(alignment);
			UnSelected->SetAlignment(alignment);
			break;
		default:
			return;
	}
}

int  Selector::GetAlignment(enum SELECTOR selector)
{
	if (selector == SELECTED)
		return Selected->GetAlignment();
	return UnSelected->GetAlignment();
}

int  Selector::AddLine(enum SELECTOR selector, char* string)
{
	int status = 0;
	switch (selector) {
		case SELECTED:
			return Selected->AddLine(string);
		case UNSELECTED:
			return UnSelected->AddLine(string);
		case BOTH:
			status = Selected->AddLine(string);
			if (status) return status;
			return UnSelected->AddLine(string);
		default:
			return 1;
	}
}

int Selector::InsertLine(enum SELECTOR selector, int line, char* string)
{
	int status = 0;
	switch (selector) {
		case SELECTED:
			return Selected->InsertLine(line, string);
		case UNSELECTED:
			return UnSelected->InsertLine(line, string);
		case BOTH:
			status = Selected->InsertLine(line, string);
			if (status) return status;
			return UnSelected->InsertLine(line, string);
		default:
			return 1;
	}
}

int  Selector::RemoveLine(enum SELECTOR which, int line)
{
	int status = 0;
	switch (which) {
		case SELECTED:
			return Selected->RemoveLine(line);
		case UNSELECTED:
			return UnSelected->RemoveLine(line);
		case BOTH:
			status = Selected->RemoveLine(line);
			if (status) return status;
			return UnSelected->RemoveLine(line);
		default:
			return 1;
	}
}

void Selector::Visible()
{
	Selected->Visible();
	UnSelected->Visible();
}

void Selector::InVisible()
{
	Selected->InVisible();
	UnSelected->InVisible();
}

void Selector::ShiftVisible()
{
	Selected->ShiftVisible();
	UnSelected->ShiftVisible();
}

void Selector::SetLayer(int newlayer)
{ layer = newlayer; }

int Selector::GetLayer()
{ return layer; }

int Selector::GetVisible()
{ return Selected->GetVisible(); }

void Selector::SetXY(int X, int Y)
{
	Selected->SetXY(X,Y);
	UnSelected->SetXY(X,Y);
}

int Selector::GetX()
{ return Selected->GetX(); } // no particular reason why Selected is used

int Selector::GetY()
{ return Selected->GetY(); }

int Selector::GetWidth()
{ 
	if (selected == SELECTED)
		return Selected->GetWidth(); 
	return UnSelected->GetWidth();
} 

int Selector::GetHeight()
{
	if (selected == SELECTED)
		return Selected->GetHeight(); 
	return UnSelected->GetHeight();
}

void Selector::SetThicknes(enum SELECTOR which, int thicknes)
{
	switch (which)
	{
		case SELECTED:
			Selected->SetThicknes(thicknes);
			break;
		case UNSELECTED:
			UnSelected->SetThicknes(thicknes);
			break;
		case BOTH:
			Selected->SetThicknes(thicknes);
			UnSelected->SetThicknes(thicknes);
			break;
		default:
			break;
		}
}

int Selector::GetThicknes(enum SELECTOR which)
{
	if (which == SELECTED)
		return Selected->GetThicknes();
	return UnSelected->GetThicknes();
}

int  Selector::ReCreate(SDL_Surface *screen)
{
	int status = Selected->ReCreate(screen);
	if (status) return 1;
	return UnSelected->ReCreate(screen);
}

int  Selector::Draw(SDL_Surface *screen)
{
	if (Selected->GetVisible() == 0 ) return 0; // if not visible, return OK
	if (selected == SELECTED)
		return Selected->Draw(screen);
	return UnSelected->Draw(screen);
}

int  Selector::Draw(SDL_Surface *screen, int X, int Y)
{
	if (Selected->GetVisible() == 0 ) return 0; // if not visible, return OK
	if (selected == SELECTED)
		return Selected->Draw(screen, X, Y);
	return UnSelected->Draw(screen, X, Y);
}

		//void UpdateBox(); // Update rect-struct of bgBox


