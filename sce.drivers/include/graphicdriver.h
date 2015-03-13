#ifndef __graphicdriver_h__
#define __graphicdriver_h__

#include <stdlib.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"


class GraphicDriver
{
	private:
	
		static int instances;
		static SDL_Surface *screen; // yes, there can be only one
		
		//SDL_Surface *setVideoMode( int w, int h, int bpp, Uint32 flags );
		SDL_Surface *setVideoMode( int w, int h, int bpp, unsigned int flags );

		static int resX;
		static int resY;
		static int depth;

	public:
		GraphicDriver(void);
		~GraphicDriver(void);

		void setupScreen(int resx, int resy, int depth, unsigned int flags);
		void setupFont(void);

		void flip(void); // flip main surface

		int getResX(void);
		int getResY(void);
		int getDepth(void);
	
		static int blitToMain( SDL_Surface *surface, int x, int y);
		static SDL_Surface *getScreen(void);

		/* Return text rendered on surface with font and fb/bg */
		static SDL_Surface *prepareText( char* text, TTF_Font *font, 
				SDL_Color fg, SDL_Color bg );

		/* Errorproof loading of image, returns image in correct display format.*/
		static SDL_Surface *loadImage ( const char* imagename );

		/* Errorproof loading of ttf font */
		static TTF_Font *openFont( const char* font, int ptsize );

		/* Prints text on screen at (x,y), with font and fg/bg color. */
		static SDL_Surface* printText ( SDL_Surface *screen, int x, int y, 
				char* text, TTF_Font *font, SDL_Color fg, SDL_Color bg);

		/* Blit surface onto given screen */
		static int blit ( SDL_Surface *screen, SDL_Surface *surface, 
				int x, int y );

};


#endif
