#include "gamegraphics.h"

GameGraphics::GameGraphics(void) {
	background = NULL;
	graphicDrv = new GraphicDriver();
	blocksWindow = new BlocksWindow();
	nextBlockWin = new NextBlockWindow();
	scoreWindow = new ScoreWindow();
	fps = new FPS();
}

GameGraphics::~GameGraphics(void) {
	if ( background ) SDL_FreeSurface( background );
	// don't think we need the iffies below, but what the heck
	if ( graphicDrv ) delete graphicDrv;
	if ( blocksWindow ) delete blocksWindow;
	if ( nextBlockWin) delete nextBlockWin;
	if ( scoreWindow ) delete scoreWindow;
	if ( fps ) delete fps;	
}

void GameGraphics::setup(void)
{
	graphicDrv->setupScreen(GameResc::RESX, GameResc::RESY, GameResc::DEPTH, GameResc::FLAGS);
	graphicDrv->setupFont();
	GameResc::graphicsSetup = true;

	// remember: setup the screen first, then the other surfaces
	blocksWindow->setup();
	nextBlockWin->setup();
	scoreWindow->setup();

	if ( background ) SDL_FreeSurface(background);
	background = GraphicDriver::loadImage(GameResc::GBACKGROUND);
}

void GameGraphics::refresh(void)
{
	/* blit to main surface: */
	graphicDrv->blitToMain(background, 0, 0); // just for now
	blocksWindow->blitTo(graphicDrv->getScreen());
	nextBlockWin->blitTo(graphicDrv->getScreen());
	scoreWindow->blitTo(graphicDrv->getScreen());
	fps->blitTo(graphicDrv->getScreen());
	
	graphicDrv->flip();	
}

void GameGraphics::endGame(int points) {
	Dialog endText(GraphicDriver::getScreen(), resc->getFontVera(), "Ahhh... you lost :-(");	
	char score[128];
	snprintf(score, 128, "But you did get %i points! :D", points);

	endText.AddLine(score);
	endText.ReCreate(graphicDrv->getScreen());
	endText.Draw(graphicDrv->getScreen(), GameResc::RESX/2-endText.GetWidth()/2, 
									   	 GameResc::RESY/2-endText.GetHeight()/2);
	graphicDrv->flip();
}
