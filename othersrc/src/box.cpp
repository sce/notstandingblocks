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

#include "box.h"

Box::Box()
{
	Background = new ColorSurface;
	Frame = new Border;
	visible = 1;
	layer = 0;
}

Box::Box(SDL_Color **bgcolor, SDL_Color **framecolor, SDL_Rect **rect)
{
	Background = new ColorSurface;
	Background->SetColor(bgcolor);
	Frame = new Border;
	Frame->SetColor(framecolor);
	SetRect(rect);
	visible = 1;
	layer = 0;
}

Box::Box(SDL_Color **bgcolor, SDL_Color **framecolor, SDL_Rect **rect, int X, int Y)
{
	Background = new ColorSurface;
	Background->SetColor(bgcolor);
	Frame = new Border;
	Frame->SetColor(framecolor);
	SetRect(rect);
	Background->SetXY(X,Y);
	Frame->SetXY(X,Y);
	visible = 1;
	layer = 0;
}

Box::Box(SDL_Surface *screen, SDL_Color **bgcolor, SDL_Color **framecolor, SDL_Rect **rect)
{
	Background = new ColorSurface;
	Background->SetColor(bgcolor);
	Frame = new Border;
	Frame->SetColor(framecolor);
	SetRect(rect);
	ReCreate(screen);
	visible = 1;
	layer = 0;
}

Box::Box(SDL_Surface *screen, SDL_Color **bgcolor, SDL_Color **framecolor, SDL_Rect **rect, int X, int Y)
{
	Background = new ColorSurface;
	Background->SetColor(bgcolor);
	Frame = new Border;
	Frame->SetColor(framecolor);
	Background->SetXY(X,Y);
	Frame->SetXY(X,Y);
	SetRect(rect);
	ReCreate(screen);
	visible = 1;
	layer = 0;
}

Box::~Box()
{
	if (Background != NULL)
		delete Background;
	if (Frame != NULL)
		delete Frame;
}

int Box::SetBackgroundColor(SDL_Color **color)
{
	return Background->SetColor(color);
}

int Box::SetFrameColor(SDL_Color **color)
{
	return Frame->SetColor(color);
}

int Box::ReCreate(SDL_Surface *screen)
{
	int status = Background->ReCreate(screen);
	if (status) return status;
	return Frame->ReCreate(screen);
}


int Box::Draw(SDL_Surface *screen)
{	
	if (!visible) return 0; // if not visible, return OK
	int status = Background->Draw(screen, 
		Background->GetX()+Frame->GetThicknes(), 
		Background->GetY()+Frame->GetThicknes());
	if (status) return status;
	return Frame->Draw(screen);
	return status;
}

int Box::Draw(SDL_Surface *screen, int X, int Y)
{	
	if (!visible) return 0; // if not visible, return OK
	int status = Background->Draw(screen, 
		X+Frame->GetThicknes(), Y+Frame->GetThicknes());
	if (status) return status;
	return Frame->Draw(screen, X, Y);
	return status;
}

SDL_Rect* Box::GetRect()
{
	return Frame->GetRect(); // since frame has the biggest/actual rect
}

int Box::GetThicknes()
{
	if (Frame) return Frame->GetThicknes();
	else return 0;
}

void Box::Visible()
{
	visible = 1;
	Background->Visible();
	Frame->Visible();
}

void Box::InVisible()
{
	visible = 0;
	Background->InVisible();
	Frame->InVisible();
}

void Box::ShiftVisible()
{
	if (Background->GetVisible() == 0) { // 0 meaning false
		visible = 1;
		Background->Visible();
		Frame->Visible();
	}
	else {
		visible = 0;
		Background->InVisible();
		Frame->InVisible();
	}
}

int Box::GetVisible()
{ return Background->GetVisible(); }

void Box::SetXY(int X, int Y)
{
	Background->SetXY(X,Y);
	Frame->SetXY(X,Y);
}

int Box::GetX()
{ return Background->GetX(); }

int Box::GetY()
{ return Background->GetY(); }

int Box::GetHeight()
{ return Frame->GetHeight(); } // Since the frame is the biggest

int Box::GetWidth()
{ return Frame->GetWidth(); } // Since the frame is the biggest

void Box::SetThicknes(int thicknes)
{ Frame->SetThicknes(thicknes); }

void Box::SetLayer(int newlayer)
{ layer = newlayer; }

int Box::GetLayer()
{ return layer; }

int Box::SetRect(SDL_Rect **rect)
{
	int status = Frame->SetRect(rect);
	if (status) return status;			
		
	// Feed Background a smaller rectangle, since it needs to be smaller
	// than the Frame.
	SDL_Rect *smallrect = new SDL_Rect;
	smallrect->x = 0;
	smallrect->y = 0;
	smallrect->w = (*rect)->w-Frame->GetThicknes()-Frame->GetThicknes();
	smallrect->h = (*rect)->h-Frame->GetThicknes()-Frame->GetThicknes();
	return Background->SetRect(&smallrect);
}
