#ifndef GRAPHICOBJECT_H_
#define GRAPHICOBJECT_H_

#include "SDL/SDL.h"

class GraphicObject
{
protected:
	int surfaceX;
	int surfaceY;
	
public:
	GraphicObject();
	GraphicObject(SDL_Surface *screen);
	virtual ~GraphicObject();
	
	virtual void blitTo(SDL_Surface *screen) = 0;
};

#endif /*GRAPHIC_H_*/
