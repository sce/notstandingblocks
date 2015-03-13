#ifndef GAMERESC_H_
#define GAMERESC_H_

#include "SDL/SDL.h"

#include "resources.h"
#include "sprite.h"
#include "graphicdriver.h"

class GameResc : public Resources
{
private:

	void setupSquare();
	void setupEmptySq();

	static Sprite *square;
	static Sprite *empty;

	//const char* FONTVERA;
	//const int   FONTVERASIZE;

public:
	// Paths to graphics:
	static const char* EMPTYH;
	static const char* EMPTY0;
	static const char* EMPTY1;
	static const char* EMPTY2;
	static const char* EMPTY3;

	static const char* BLOCK0;
	static const char* BLOCK1;
	static const char* BLOCK2;
	static const char* BLOCK3;

	static const char* GBWBACKGROUND;
	static const char* GMAINWINDOW;
	static const char* GBACKGROUND;
	static const char* MAINMENUBACKGROUND;

	// Music/sounds:
	static const char* GAMEMUSIC;
	static const char* WONMUSIC;
	static const char* MENUMUSIC;
	
	static const char* BLOCKSTOPSOUND;
	static const char* BLOCKSTOPSOUND2;
	static const char* ROWREMOVEDSOUND;
	
	// Constant ints must be in the header file:
		
	// Stopping sirkular reference by putting it here:
	static const int MAPX = 14;  // size of map
	static const int MAPY = 20; // size of map
		
	static const unsigned int SQUARETILES = 4;
	static const unsigned int EMPTYTILES = 1;
	static const unsigned int SQWIDTH = 20;
	static const unsigned int SQHEIGHT = 20;
	
	GameResc();
	virtual ~GameResc();
	
	Sprite *getSquare();
	Sprite *getEmptySq();
};

#endif /*GAMERESC_H_*/
