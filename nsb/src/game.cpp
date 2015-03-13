#include "game.h"

Game::Game(void)
{
	//printf("Game()\n");
	wantloglevel_ = LOG::DEFAULTLL;
	playGame_ = true; 
	pause_ = false;
	moveUpdateDelay_ = 0; // this gets lower during play
	gameGraphics = new GameGraphics();
	gameAudio = new GameAudio();
	gameEngine = new GameEngine();
}

Game::~Game() {
	//printf("~Game()\n");
	if ( gameAudio ) delete gameAudio;
	if ( gameGraphics ) delete gameGraphics;
	if ( gameEngine ) delete gameEngine;
}

void Game::cleanup(void)
{
	////blocksWindow.cleanupTerminal();
	//gameEngine_.cleanup();
	gameAudio->fadeAwayMusic();
}

void Game::respondToInteraction(Input::USERACTION action)
{
	char *string = new char[256];

	snprintf(string, 256, "+ Game::respondToInteraction(%i)", int(action) );
	LOG::Log(string, LOG::VERBOSE, wantloglevel_);

	switch (action)
	{
		case Input::GOLEFT:
			//gameEngine_.setdx(gameEngine_.getdx()-1);
			gameEngine->setdx(-1);
			LOG::Log("  * Useraction: LEFT", LOG::VERBOSE, wantloglevel_);
			gameAudio->playKeypress();
			break;

		case Input::GORIGHT:
			//gameEngine_.setdx(gameEngine_.getdx()+1);
			gameEngine->setdx(1);
			LOG::Log("  * Useraction: RIGHT", LOG::VERBOSE, wantloglevel_);
			gameAudio->playKeypress();
			break;

		case Input::GOUP:
			gameEngine->rotateBlock();
			gameAudio->playKeypress();
			break;
			
		case Input::GODOWN:
			gameEngine->actBlockFallNow();
			break;

		case Input::EXITSTATE:
			playGame_ = false;
			break;

		case Input::PAUSE:
			pause_ = !pause_;
			break;

		case Input::SHUTDOWN:
			LOG::Log("  * Useraction: SHUTDOWN", LOG::WARNING, wantloglevel_);
			playGame_ = false;
			break;

		case Input::MUSICON:
		case Input::MUSICOFF:

		case Input::SOUNDON:
		case Input::SOUNDOFF:

		case Input::NOTHING: // fall down to default
		default:
			//snprintf(string, 256, "  * Useraction: NOTHING (%i)", int(action) );
			//LOG::Log(string, LOG::DEBUG, wantloglevel_);
			break;
	};

	snprintf(string, 256, "- Game::respondToInteraction(%i)", int(action) );
	LOG::Log(string, LOG::VERBOSE, wantloglevel_);
	delete string;
}

bool Game::catchKeyPress()
{
	/* Check for keys, update info based on keys, and stuff */
	SDL_Event event;
	SDL_keysym keysym;
	
	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type ) {
			case SDL_KEYDOWN:	
				keysym = event.key.keysym;
				switch ( keysym.sym ) {
					case SDLK_RETURN:
					case SDLK_ESCAPE:
					case SDLK_q:		
					default:			
						return true;
				};					
				break;
			case SDL_QUIT:
				/* exit(0); immidiate quit */
				return true;
			default:			
				break;		
		};
	}
	return false;
}	


int Game::run(void)
{
	LOG::Log("+ Game::run(void)", LOG::VERBOSE, wantloglevel_);

	playGame_ = true;
	pause_ = false;

	gameEngine->startNew();
	gameGraphics->setup();
	gameAudio->setup();

	gameAudio->playGameMusic();
	gameGraphics->refresh();
	//sleep(1);
	SDL_Delay(1000);

	while (playGame_)
	{
		respondToInteraction(Input::getAction());
		
		// remember, something else might change playGame_!
		if ( !pause_ )
		{
			
			int results = gameEngine->doOneFrame();
			//int results = 0;
			switch ( results )
			{
				case -2:  // new block on the way
					gameAudio->playBlockStopped();
					break;

				case -1: // he's dead
					playGame_ = false; 
					break;

				case 0: // nothing happened
					break;

				default: // rows were removed
					gameAudio->playRowRemoved();
					break;
			};
		}

		gameGraphics->refresh();

		SDL_Delay(1); // hmm..
	};
	
	while ( catchKeyPress() ); // Catch recent key-presses

	gameGraphics->endGame(gameEngine->getScore());	
	cleanup();
	while ( !catchKeyPress() );
	
	printf("Score: %u\n", gameEngine->getScore());
	LOG::Log("- Game::run(void)", LOG::VERBOSE, wantloglevel_);

	return 0; // return score
}

