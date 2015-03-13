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

#include "dialog.h"

Dialog::Dialog() 
{
	bgBox = new Box;
	txtBox = new Textbox;
	//margin = bgBox->GetThicknes(); // minimum
	margin = 10;
}

Dialog::Dialog(SDL_Surface *screen, TTF_Font *font, char* text)
{
	txtBox = new Textbox(screen, font, text);
	bgBox = new Box;
	//margin = bgBox->GetThicknes(); // minimum
	margin = 10;
	UpdateBox();
}

Dialog::Dialog(SDL_Surface *screen, SDL_Color **bgcolor, 
	SDL_Color **framecolor, TTF_Font *font, char* text) 
{
	txtBox = new Textbox(screen, font, text);
	bgBox = new Box;
	bgBox->SetFrameColor(framecolor);
	bgBox->SetBackgroundColor(bgcolor);
	//bgBox->SetThicknes(10);
	//margin = bgBox->GetThicknes(); // minimum
	margin = 10;
	UpdateBox();
}

Dialog::~Dialog() 
{
	if (txtBox) delete txtBox;
	if (bgBox) delete bgBox;
};	


int Dialog::Draw(SDL_Surface *screen, int X, int Y)
{
	if (bgBox->GetVisible() == 0) return 0; // if not visible, return OK
	int status = bgBox->Draw(screen, X, Y);
	if (status) return status;
	return txtBox->Draw(screen, X+margin, Y+margin);
}

int Dialog::Draw(SDL_Surface *screen)
{
	if (bgBox->GetVisible() == 0) return 0; // if not visible, return OK
	int status = bgBox->Draw(screen);
	if (status) return status;
	return txtBox->Draw(screen, bgBox->GetX()+margin, bgBox->GetY()+margin);
}

int Dialog::AddLine(char* string)
{
	return txtBox->AddLine(string);
}

void Dialog::UpdateBox()
{
	if (txtBox->GetRect() == NULL) return;
	// update dimensions so that it fits to the textbox
	SDL_Rect *rect = txtBox->GetRect();
	rect->w += margin+margin; 	// whooops, inconsistency since
	rect->h += margin+margin; 	// borderthicknes is kept separate
										// the whole time
	bgBox->SetRect(&rect);
}

int Dialog::ReCreateText(SDL_Surface *screen)
{
	return txtBox->ReCreate(screen);
}

int Dialog::ReCreateBox(SDL_Surface *screen)
{
	return bgBox->ReCreate(screen);
}

int Dialog::ReCreate(SDL_Surface *screen)
{
	// Should be internal functions? (... what?) 
	int status = txtBox->ReCreate(screen);
	if (status) return status;

	UpdateBox();
	return bgBox->ReCreate(screen);
}

void Dialog::SetMargin(int newmargin)
{
	margin = newmargin;
}

int Dialog::InsertLine(int line, char* string)
{
	return txtBox->InsertLine(line, string);
}

int Dialog::RemoveLine(int line)
{
	return txtBox->RemoveLine(line);
}

int Dialog::SetFrameColor(SDL_Color **color)
{
	if (color == NULL) return 1;
	return bgBox->SetFrameColor(color);
}


int Dialog::SetBackgroundColor(SDL_Color **color)
{
	if (color == NULL) return 1;
	return bgBox->SetBackgroundColor(color);
}

int Dialog::SetFont(TTF_Font *newfont)
{
	if (newfont == NULL) return 1;
	return txtBox->SetFont(newfont);
}

void Dialog::SetFontColor(int r, int g, int b)
{
	txtBox->SetFG(r,g,b);
}

void Dialog::SetAlignment(enum ALIGNMENT alignment)
{
	txtBox->SetAlignment(alignment);
}

int Dialog::GetAlignment()
{
	return txtBox->GetAlignment();
}

void Dialog::Visible()
{ 
	txtBox->Visible();
	bgBox->Visible();
}

void Dialog::InVisible()
{ 
	txtBox->InVisible();
	bgBox->InVisible();
}

void Dialog::ShiftVisible()
{ 
	if (txtBox->GetVisible() == 0) { // 0 meaning false
		txtBox->Visible();
		bgBox->Visible();
	}
	else {
		txtBox->InVisible();
		bgBox->InVisible();
	}
}

int Dialog::GetVisible()
{ return txtBox->GetVisible(); } 

void Dialog::SetXY(int X, int Y)
{
	txtBox->SetXY(X,Y);
	bgBox->SetXY(X,Y);
}

int Dialog::GetX()
{ return txtBox->GetX(); }

int Dialog::GetY()
{ return txtBox->GetY(); }

int Dialog::GetWidth()
{ return bgBox->GetWidth(); } // since the background is the bigger of the two

int Dialog::GetHeight()
{ return bgBox->GetHeight(); } // since the background is the bigger of the two

void Dialog::SetThicknes(int thicknes)
{ bgBox->SetThicknes(thicknes); }

int Dialog::GetThicknes()
{ return bgBox->GetThicknes(); }

void Dialog::SetLayer(int newlayer)
{ layer = newlayer; }

int Dialog::GetLayer()
{ return layer; }


