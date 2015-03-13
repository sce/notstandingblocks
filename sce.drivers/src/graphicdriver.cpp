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
 * graphicdriver.cpp
 * Contains several nice functions
 */

#include "graphicdriver.h"

// initialize static members:
int GraphicDriver::resX = 0;
int GraphicDriver::resY = 0;
int GraphicDriver::depth = 0;
int GraphicDriver::instances = 0;
SDL_Surface *GraphicDriver::screen = NULL;

GraphicDriver::GraphicDriver(void) {
	//printf("GraphicDriver()\n");
	instances++;
}

GraphicDriver::~GraphicDriver(void) {
	//printf("~GraphicDriver()\n");
	if ( --instances == 0 && screen != NULL ) {
		//printf(" -> Destroying screen\n");
		SDL_FreeSurface(screen);
		//if ( TTF_WasInit() ) {
			//printf("  -> Quitting TTF\n");
			//TTF_Quit();
		//}
		/*
		if ( SDL_WasInit(SDL_INIT_EVERYTHING) ) {
			//printf("   -> And finally shutting down SDL\n");
			//SDL_Quit();
		}
		else
			//printf("   -> ..SDL not initialized??");
			 */
	}
}

int GraphicDriver::getResX(void) {
	if ( resX == 0 ) {
		printf("Graphics::getResx(): Returning resX before it's given value.\n");
		exit(1); }

	return resX;
}

int GraphicDriver::getResY(void) {
	if ( resY == 0 ) {
		printf("Grapihcs::getResY(): Returning resY before it's given value.\n");
		exit(1); }

 	return resY;
}

int GraphicDriver::getDepth(void) {
	if ( depth == 0 ) {
		printf("Graphics::getDepth(): Returning depth before it's given value.\n");
		exit(1); }

	return depth;
}


void GraphicDriver::flip(void) {
	SDL_Flip(screen);
}

SDL_Surface *GraphicDriver::getScreen(void) {
	return screen;
}

void GraphicDriver::setupFont(void) {
	if ( TTF_Init() == -1 ) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(1);
	}
	//atexit(TTF_Quit); // automatic shutdown
}

void GraphicDriver::setupScreen(int resx, int resy, int newDepth, unsigned int flags) {
	// warning: should check if sdl is running first
   if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
		printf("SDL init failed!\n");
      exit(1); }

	//atexit(SDL_Quit); // automatic shutdown

	// continue as normal:

	if ( depth == 0 ) { // meaning: use current bpp
		const SDL_VideoInfo* currentSetup = NULL;

		currentSetup = SDL_GetVideoInfo();
		depth = currentSetup->vfmt->BitsPerPixel;
	}

	resX = resx;
	resY = resy;
	depth = newDepth;

	screen = setVideoMode(resX, resY, depth, flags);
}

TTF_Font *GraphicDriver::openFont(const char* font, int ptsize) {
	TTF_Font *temp;
	temp = TTF_OpenFont( font, ptsize );
	if ( !font ) {
		printf(" * Graphics::openFont(): %s\n", TTF_GetError());
		exit(1);
	}
	return temp;
}

SDL_Surface *GraphicDriver::setVideoMode(int w, int h, int bpp, unsigned int flags) {
	SDL_Surface *temp;
	temp = SDL_SetVideoMode( w, h, bpp, flags );
	if ( temp == NULL ) {
		printf(" * Graphics::setVideoMode():"
			"\nUnable to set video mode: %s\n", SDL_GetError() );
		exit(1); /* Hard exit */
	}
	return temp;
}

SDL_Surface *GraphicDriver::loadImage(const char* imagename) {
	SDL_Surface *temp = IMG_Load( imagename );
	if ( temp == NULL ) {
		printf(" * Graphics::loadImage():"
			"\nLoading \"%s\" failed:\n%s.\n", imagename, SDL_GetError() );
		//	This is not a good solution, as at e.g. forgets to do SDL_Quit(), etc.
		//	The part of the program that started SDL should be the one that closes it as well.
		//exit(1);

		// This is better, as it allows the caller to make the decision necessary.
		return NULL;
	}

	/* Convert to framebuffers displayformat */
	//SDL_Surface *image = SDL_DisplayFormat(temp);
	SDL_Surface *image = SDL_DisplayFormatAlpha(temp);

	SDL_FreeSurface(temp); // free up old surface, preventing memory leak
	return image;
}


int GraphicDriver::blitToMain( SDL_Surface *surface, int x, int y) {
	if ( screen == NULL ) {
		printf("Graphics::blitToMain(): Trying to blit to empty main surface.\n");
		return 1;
	}
	return blit(screen, surface, x, y);
}

int GraphicDriver::blit(SDL_Surface *screen, SDL_Surface *surface, int x, int y) {
	if ( screen == NULL || surface == NULL ) {
		printf("Error: Blit: screen || surface == 0!\n");
		return 1;
	}

	if (x < 0 || y < 0 || x > screen->w || y > screen->h) {
		printf("Error: Blit: x < 0 || y < 0"
			" || x > screen->w || y > screen->h!\n");
		return 1;
	}

	SDL_Rect src, dest;

	src.x = 0;
	src.y = 0;
	src.w = surface->w;
	src.h = surface->h;
	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;

	/* Blit to screen */
	return SDL_BlitSurface( surface, &src, screen, &dest );
}

SDL_Surface *GraphicDriver::prepareText(char* text, TTF_Font *font,
		SDL_Color fg, SDL_Color bg)
{
	SDL_Surface *text_surface;
	SDL_Surface *temp;

	/* Render font on new surface */
	if ( !(temp=TTF_RenderText_Shaded(font,text,fg,bg)) ) {
		printf(" * Graphics::prepareText:"
			"\nTTF_RenderText_Shaded: %s\n", TTF_GetError());
		printf("\nSDL_GetError: %s\n", SDL_GetError());
		return NULL; // returns NULL on failure
	}

	/* Fix display format of new surface for future use */
	text_surface = SDL_DisplayFormat( temp );
	SDL_FreeSurface( temp );

	return text_surface;
}

SDL_Surface* GraphicDriver::printText(SDL_Surface *screen, int x, int y,
		char* text, TTF_Font *font, SDL_Color fg, SDL_Color bg)
{
	SDL_Surface *text_surface = NULL;

	text_surface = prepareText( text, font, fg, bg );
	if (!text_surface) return NULL; // Returns NULL on failure

	int status = blit( screen, text_surface, x, y );
	if (status) return NULL; // Returns NULL on failure

	return text_surface;
}
