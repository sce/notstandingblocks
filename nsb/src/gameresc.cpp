#include "gameresc.h"

// static const inits:
// used by gamemainwindowg.cpp:
const char* GameResc::EMPTYH = "resources/pics/2020emptyh.png";

const char* GameResc::EMPTY0 = "resources/pics/round1.png";
const char* GameResc::EMPTY1 = "resources/pics/round2.png";
const char* GameResc::EMPTY2 = "resources/pics/round3.png";
const char* GameResc::EMPTY3 = "resources/pics/round4.png";

const char* GameResc::BLOCK0 = "resources/pics/round1a2.png";
const char* GameResc::BLOCK1 = "resources/pics/round2a.png";
const char* GameResc::BLOCK2 = "resources/pics/round3a.png";
const char* GameResc::BLOCK3 = "resources/pics/round4a.png";

const char* GameResc::GBWBACKGROUND  = "resources/pics/12060background.png";

const char* GameResc::GMAINWINDOW = "resources/pics/blocksbackground1.png";
const char* GameResc::GBACKGROUND = "resources/pics/background1.png";
const char* GameResc::MAINMENUBACKGROUND = "resources/pics/mscrbk1.png";

// Music/sounds:
const char* GameResc::GAMEMUSIC = "resources/music/gamemusic.mp3";
const char* GameResc::WONMUSIC  = "resources/music/wonmusic.mp3";
const char* GameResc::MENUMUSIC  = "resources/music/menumusic.mp3";

const char* GameResc::BLOCKSTOPSOUND = "resources/sounds/pop.wav";
const char* GameResc::BLOCKSTOPSOUND2 = "resources/sounds/punch.wav";
const char* GameResc::ROWREMOVEDSOUND = "resources/sounds/explosion.wav";

// static non-const inits:
Sprite *GameResc::square = NULL;
Sprite *GameResc::empty = NULL;

GameResc::GameResc() : Resources()//,
	//FONTVERA("resources/fonts/vera.ttf"), FONTVERASIZE(16)
{ 
	//printf("GameResc()\n");
}

GameResc::~GameResc()
{
	if ( instances-1 == 0 ) { // ~Resources() comes in later and makes this 0
		if ( square ) delete square;
		if ( empty ) delete empty;
	}	
}

void GameResc::setupSquare() {
	if ( square == NULL && graphicsSetup ) {
		square = new Sprite(SQUARETILES);

		square->loadFrame(0, GraphicDriver::loadImage(BLOCK0) );
		square->loadFrame(1, GraphicDriver::loadImage(BLOCK1) );
		square->loadFrame(2, GraphicDriver::loadImage(BLOCK2) );
		square->loadFrame(3, GraphicDriver::loadImage(BLOCK3) );
	}
}

void GameResc::setupEmptySq() {
	if ( empty == NULL && graphicsSetup ) {
		empty = new Sprite(EMPTYTILES);
		empty->loadFrame(0, GraphicDriver::loadImage(EMPTYH) );
	}
}

/* A good thing:
   The GraphicDriver::loadImage() function forcefully exits if it
   can't open an image. Thus we don't have to worry about that
   here. For some reason, we need error handling in resources.cpp,
   but who cares. */
   
Sprite *GameResc::getSquare() {
	setupSquare();
	return square;
}

Sprite *GameResc::getEmptySq() {
	setupEmptySq();
	return empty;
}
