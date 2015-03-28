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

SDL_Window *GraphicDriver::window = NULL;
SDL_Renderer *GraphicDriver::renderer = NULL;

GraphicDriver::GraphicDriver(void) {
	//printf("GraphicDriver()\n");
	instances++;
}

GraphicDriver::~GraphicDriver(void) {
  --instances;
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
  SDL_RenderPresent(renderer);
}

SDL_Renderer *GraphicDriver::getRenderer(void) {
	return renderer;
}

void GraphicDriver::setupFont(void) {
	if ( TTF_Init() == -1 ) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(1);
	}
	atexit(TTF_Quit);
}

void GraphicDriver::setupScreen(int resx, int resy, int newDepth, unsigned int flags) {
  // int subsystem_init = SDL_WasInit(SDL_INIT_EVERYTHING);
  // bool video = subsystem_init & SDL_INIT_VIDEO;
  bool video = (SDL_WasInit(SDL_INIT_VIDEO) != 0);

  if (!video && SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
    printf("SDL init failed!\n");
    exit(1); }

	this->resX = resx;
	this->resY = resy;
	depth = newDepth;

	setVideoMode(resX, resY, depth, flags);
  atexit(SDL_Quit);
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

void GraphicDriver::setVideoMode(int w, int h, int bpp, unsigned int flags) {
  // TODO: Add title.
  // We as for 0/0 width/height to make SDL use the current resolution, and
  // rather set "logical size" to have SDL do hardware scaling.
  if ( window == NULL ) {
    window = SDL_CreateWindow(
      "",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      //0, 0, flags );
      w, h, 0 );
  }

	if ( window == NULL ) {
		printf(" * Graphics::setVideoMode():"
			"\nUnable to set video mode: %s\n", SDL_GetError() );
		exit(1); /* Hard exit */
	}

  if ( renderer == NULL ) {
    //renderer = SDL_CreateRenderer(window, -1, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  }

  if ( renderer == NULL ) {
    printf(" * Graphics::setVideoMode():"
        "\nUnable to create renderer: %s\n", SDL_GetError() );
    exit(1);
  }

  // to make the scaled rendering look smoother:
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(renderer, w, h);

  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

SDL_Texture *GraphicDriver::loadImage(const char* imagename) {
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
	//SDL_Surface *image = SDL_DisplayFormatAlpha(temp);

	SDL_Texture *image = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	return image;
}


bool GraphicDriver::isInsideRenderer(int x, int y) {
  if (x < 0 || y < 0)
    return false;

  if (!renderer)
    return false;

  bool results = true;
  SDL_RendererInfo ri;

  if (SDL_GetRendererInfo(renderer, &ri)) {
    printf(" * GraphicsDriver::is:InsideRenderer: %s.\n", SDL_GetError());
    return false;
  }

  if (x > ri.max_texture_width || y > ri.max_texture_height )
    results = false;

  return results;
}

int GraphicDriver::blitToMain(SDL_Texture *source, int x, int y) {
	if ( renderer == NULL || source == NULL ) {
		printf("Error: Blit: renderer || source == 0!\n");
		return 1;
	}

	if (!isInsideRenderer(x, y)) {
		return 1;
	}

	SDL_Rect src, dest;

	src.x = 0;
	src.y = 0;

  SDL_QueryTexture(source, NULL, NULL, &src.w, &src.h);

	dest.x = x;
	dest.y = y;

  SDL_QueryTexture(source, NULL, NULL, &dest.w, &dest.h);

	/* Blit to target */
	return SDL_RenderCopy( renderer, source, &src, &dest );
}

SDL_Texture *GraphicDriver::prepareText(char* text, TTF_Font *font,
		SDL_Color fg, SDL_Color bg)
{
	SDL_Surface *temp;

	/* Render font on new surface */
	if ( !(temp=TTF_RenderText_Shaded(font,text,fg,bg)) ) {
		printf(" * Graphics::prepareText:"
			"\nTTF_RenderText_Shaded: %s\n", TTF_GetError());
		printf("\nSDL_GetError: %s\n", SDL_GetError());
		return NULL; // returns NULL on failure
	}

	SDL_Texture *text_surface = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface( temp );

	return text_surface;
}

SDL_Texture* GraphicDriver::printText(int x, int y,
		char* text, TTF_Font *font, SDL_Color fg, SDL_Color bg)
{
	SDL_Texture *text_surface = prepareText( text, font, fg, bg );
	if (!text_surface) return NULL; // Returns NULL on failure

	if ( blitToMain( text_surface, x, y) ) {
    SDL_DestroyTexture(text_surface);
    return NULL; // Returns NULL on failure
  }

	return text_surface;
}
