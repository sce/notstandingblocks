#ifndef __graphicdriver_h__
#define __graphicdriver_h__

#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"


class GraphicDriver
{
	private:

		static int instances;

		static SDL_Window *window;
		static SDL_Renderer *renderer;
		//static SDL_Texture *screen;

		void setVideoMode( int w, int h, int bpp, unsigned int flags );

		static int resX;
		static int resY;
		static int depth;

    static bool isInsideRenderer(int x, int y);

	public:
		GraphicDriver(void);
		~GraphicDriver(void);

		void setupScreen(int resx, int resy, int depth, unsigned int flags);
		void setupFont(void);

		void flip(void); // flip main surface

		int getResX(void);
		int getResY(void);
		int getDepth(void);

		static SDL_Renderer *getRenderer(void);

		static int blitToMain( SDL_Texture *texture, int x, int y);

		/* Return text rendered on surface with font and fb/bg */
		static SDL_Texture *prepareText( char* text, TTF_Font *font,
				SDL_Color fg, SDL_Color bg );

		/* Errorproof loading of image, returns image in correct display format.*/
		static SDL_Texture *loadImage ( const char* imagename );

		/* Errorproof loading of ttf font */
		static TTF_Font *openFont( const char* font, int ptsize );

		/* Prints text on screen at (x,y), with font and fg/bg color. */
		static SDL_Texture* printText (
        int x, int y, char* text,
        TTF_Font *font, SDL_Color fg, SDL_Color bg);

};


#endif
