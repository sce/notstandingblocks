#include "fps.h"

FPS::FPS(void)
{
	fps_ = 0;
	previous_ = 0;

	bg_.r = 0;
	bg_.g = 0;
	bg_.b = 0;

	fg_.r = 255;
	fg_.g = 255;
	fg_.b = 255;

	text_ = NULL;
	
	surfaceX = 280+180+100;
	surfaceY = 0;
}

FPS::~FPS(void) {
	if (text_) SDL_FreeSurface(text_);
}

void FPS::refresh(void)
{
	fps_++;
	int now = SDL_GetTicks();

	if ( (now - previous_) >= 1000 || previous_ == 0) 
	{
		if (text_ != NULL) SDL_FreeSurface(text_);
		
		snprintf(string_, 16, "FPS: %i", fps_);
		text_ = GraphicDriver::prepareText(string_, resc.getFontVera(), fg_, bg_);

		SDL_SetColorKey(text_, SDL_SRCCOLORKEY, 0);

		// reset values
		fps_ = 0; previous_ = now;
	}
}

void FPS::blitTo(SDL_Surface *screen) {
	refresh(); // For now...?
	GraphicDriver::blit(screen, text_, surfaceX, surfaceY);
}
