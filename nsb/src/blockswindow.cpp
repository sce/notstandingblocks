#include "blockswindow.h"

// init statics:
const unsigned int BlocksWindow::SQUARETILES = GameResc::SQUARETILES;
const unsigned int BlocksWindow::EMPTYTILES = GameResc::EMPTYTILES;
const unsigned int BlocksWindow::SQWIDTH = GameResc::SQWIDTH;
const unsigned int BlocksWindow::SQHEIGHT = GameResc::SQHEIGHT;

BlocksWindow::BlocksWindow(void) 
{
	surfaceX = 180;
	surfaceY = 40;
	background = NULL;
}
	
BlocksWindow::~BlocksWindow(void) 
{
	if ( background ) 	SDL_FreeSurface( background );
}

void BlocksWindow::setup()
{		
	background = GraphicDriver::loadImage(GameResc::GMAINWINDOW);
}


void BlocksWindow::blitTo(SDL_Surface *screen)
{
	int value = 0;
	GraphicDriver::blit(screen, background, surfaceX, surfaceY);

	// go through the map square by square
	for (int y=0; y<Map::MAPY; y++)
		for (int x=0; x<Map::MAPX; x++)
		{
			value = Map::getXY(x,y);

			if ( value != Map::EMPTY ) {
				// counts from zero
				if ( value != -1 && value != Block::BLOCKTYPES+1 ) {
					// the value at (x,y) is an index to which frame we shall draw
					resc->getSquare()->draw(screen, value-1, x*SQWIDTH+surfaceX, y*SQHEIGHT+surfaceY);
				}
				else
					resc->getEmptySq()->draw(screen, 0, x*SQWIDTH+surfaceX, y*SQHEIGHT+surfaceY);

			}
			else
			{
				// that number (0) is the frame. can use this to get random
				// varying background
				//empty_->draw(mainSurface_, 0, x*SQWIDTH, y*SQHEIGHT);
			}
		}
}
