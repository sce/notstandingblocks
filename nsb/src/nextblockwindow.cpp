#include "nextblockwindow.h"


NextBlockWindow::NextBlockWindow(void) //: x(0), y(0)
//	: surfaceX(280+180+30), surfaceY(220)
{
	nextBlock = NULL;

	surfaceX = 280+180+30;
	surfaceY = 220;
}

NextBlockWindow::~NextBlockWindow(void)
{
	// don't delete empty_ or square_ : might be in use by others
	// and leave nextBlock alone too.
}

void NextBlockWindow::setup()
{
	//empty_ = empty;
	//square_ = square;
	
	if ( nextBlock == NULL)
		nextBlock = gameEngine_.getNextBlock();

	// The box:
	SDL_Rect *boxRect = new SDL_Rect;
	boxRect->x = 0;
	boxRect->y = 0;
	boxRect->w = BlocksWindow::SQWIDTH*(5+1); 
	boxRect->h = BlocksWindow::SQWIDTH*(2+1); 

	backgroundBox.SetRect(&boxRect);
	backgroundBox.ReCreate(GraphicDriver::getScreen());

}

void NextBlockWindow::blitTo(SDL_Surface *screen) {
	backgroundBox.Draw(screen, surfaceX, surfaceY);
	
	int halfX = BlocksWindow::SQWIDTH/2;
	int halfY = BlocksWindow::SQHEIGHT/2;
	
	// trekk fra Map::MAPX/2 for å få (0,0)-relative coordinater
	for ( int i=0; i<Block::MAXSQUARES; i++)
	{
		Point *point = nextBlock->getCoordinates(i);
		
		resc.getSquare()->draw(screen, nextBlock->getBlocktype(), 
			   ( point->x-Map::MAPX/2+2 )* BlocksWindow::SQWIDTH+halfX+surfaceX, 
	 		   ( point->y )*BlocksWindow::SQHEIGHT+halfY+surfaceY );
	 		   
		delete point;
	}
}
