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
 * sprite.cpp 
 * Made by S. Christoffer Eliesen
 * June 3rd 2004
 */

#include "sprite.h"

Sprite::Sprite(unsigned int frames) 
{ 
	imgs_ = new SDL_Surface *[frames]; 

	for (unsigned int i=0; i<frames; i++)
		imgs_[i] = NULL; 

	frames_ = frames; 
	//visible_ = 1; 
}

Sprite::~Sprite() 
{ 
	if (imgs_)
		for ( unsigned int i=0; i<frames_; i++)
			if ( imgs_[i] )
				SDL_FreeSurface(imgs_[i]);

	//if (imgs_) delete []imgs_; 
}

int Sprite::loadFrame(unsigned int frame, SDL_Surface* surf) 
{ 
		if (surf == NULL || frame >= frames_ ) return 1;

		if (imgs_[frame] != NULL) 
		{
			SDL_FreeSurface(imgs_[frame]);
			imgs_[frame] = NULL;
		}

		// assuming see-through:
		SDL_SetColorKey(surf, SDL_SRCCOLORKEY | SDL_RLEACCEL, 0);
		//SDL_SetAlpha(surf, SDL_SRCALPHA, 255);
		//SDL_SetAlpha(surf, SDL_SRCALPHA, 120);

		imgs_[frame] = surf;
		return 0; 
}

int Sprite::draw(SDL_Surface *screen, unsigned int frame, int x, int y)
{
	////if (!visible) return 0;

	if ( frame < frames_ && imgs_[frame] != NULL )
		return GraphicDriver::blit(screen, imgs_[frame], x, y); 
	else
		return 0;
}

int Sprite::getFrames() { return frames_; }
