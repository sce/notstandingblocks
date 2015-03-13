#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <stdlib.h>

#include "SDL/SDL_ttf.h"

#include "graphicdriver.h"

class Resources
{
protected:
		
	static int instances;	

	// Fonts:
	static TTF_Font *fontVera;
	const char* FONTVERA;
	const int   FONTVERASIZE;

	void setupFontVera();
	
public:
	static bool graphicsSetup;

	static const int RESX = 640;
	static const int RESY = 480;
	static const int DEPTH = 0; // 0 means: Use whatever's best/in use
	static const unsigned int FLAGS = SDL_HWSURFACE | SDL_DOUBLEBUF 
		//| SDL_HWACCEL;
		| SDL_HWACCEL | SDL_FULLSCREEN;
		//SDL_SRCCOLORKEY | SDL_SRCALPHA | SDL_FULLSCREEN | SDL_ANYFORMAT;

	// Functions:	
	Resources();
	~Resources();
	
	void closeFontVera();

	TTF_Font *getFontVera();

};

#endif /*RESOURCES_H_*/
