#include "log.h"
#include "game.h"

#include "gameresc.h"
#include "menutest1.h"
#include "audiodriver.h"

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

int main(int argc, char *argv[])
{
	//LOG::setLoglevel(LOG::VERBOSE);
	//LOG::setLoglevel(LOG::DEBUG); 
	LOG::setLoglevel(LOG::NONE); 

	//LOG::setLogfile("log.log.txt");
	//Block::setLoglevel(LOG::DEBUG);
	//Gamewindow::setLoglevel(LOG::DEBUG);

	LOG::Log("+ Main(void)", LOG::WARNING, LOG::NONE);
	LOG::Log("* Trying to start menutest..", LOG::WARNING, LOG::NONE);

	//atexit(SDL_Quit);
	//atexit(TTF_Quit);
	
	Menu *menutest = new Menu();
	menutest->menutest();
	delete menutest;
	//printf("Done with menutest\n");
	// Right, in the future this will be fixed,
	// but right now we need to close the font and audio before we exit.
	//GameResc *resc = new GameResc();
	//resc->closeFontVera();
	//delete resc;
	SDL_Delay(1000); // in case we immediatly quit from menutest
	SDL_Quit();
	//printf("Done with everything\n");
	return 0;
}

