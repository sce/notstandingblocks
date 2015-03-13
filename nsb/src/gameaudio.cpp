#include "gameaudio.h"

int GameAudio::instances = 0;
AudioDriver *GameAudio::audioDrv = NULL;
bool GameAudio::audioIsSetup_ = false; // do we need to call Audio::setup()?
bool GameAudio::useAudio_ = false; // can/should we use audio?

Mix_Music *GameAudio::gameMusic_ = NULL;
Mix_Music *GameAudio::wonMusic_ = NULL;
Mix_Music *GameAudio::menuMusic_ = NULL;
		
Mix_Chunk *GameAudio::rowRemovedSound_ = NULL;
Mix_Chunk *GameAudio::blockStopSound_ = NULL;

GameAudio::GameAudio(void)
{
	instances++;
	//printf("GameAudio(): %i\n", instances);
}

GameAudio::~GameAudio(void)
{
	//printf("~GameAudio(): %i\n", instances-1);
	if ( --instances == 0 ) {
		//printf(" -> Last one alive:\n");
		stopAll();
		//SDL_Delay(1000);
		//printf("  -> Deleting gameMusic\n");
		if ( gameMusic_ ) Mix_FreeMusic(gameMusic_);
		//printf("  -> Deleting wonMusic\n");
		if ( wonMusic_ ) Mix_FreeMusic(wonMusic_);
		//printf("  -> Deleting menuMusic\n");
		if ( menuMusic_ ) Mix_FreeMusic(menuMusic_);

		//printf("  -> Deleting rowRemovedSound\n");
		if ( rowRemovedSound_ ) Mix_FreeChunk(rowRemovedSound_);
		//printf("  -> Deleting blockStopSound\n");
		if ( blockStopSound_ ) Mix_FreeChunk(blockStopSound_);
		//printf(" -> Done\n");
	
		if ( audioDrv ) delete audioDrv;
	}
}

void GameAudio::setup(void)
{
	if ( !audioIsSetup_ )
	{
		if ( audioDrv == NULL )
			audioDrv = new AudioDriver();
			
		if ( audioDrv->setup() == 0 )
			useAudio_ = true;
		else
			printf(" * GameAudio::setup: Disabling sound.\n");

		audioIsSetup_ = true;
	}

	if ( !gameMusic_ ) 
		gameMusic_ = Mix_LoadMUS(GameResc::GAMEMUSIC);

	if ( !gameMusic_ )
		printf(" * GameAudio::setup: Couldn't load %s.\n", GameResc::GAMEMUSIC);


	if ( !wonMusic_ ) 
		wonMusic_ = Mix_LoadMUS(GameResc::WONMUSIC);

	if ( !wonMusic_ )
		printf(" * GameAudio::setup: Couldn't load %s.\n", GameResc::WONMUSIC);


	if ( !menuMusic_ ) 
		menuMusic_ = Mix_LoadMUS(GameResc::MENUMUSIC);

	if ( !menuMusic_ )
		printf(" * GameAudio::setup: Couldn't load %s.\n", GameResc::MENUMUSIC);


	if ( !rowRemovedSound_ ) 
		rowRemovedSound_ = Mix_LoadWAV(GameResc::ROWREMOVEDSOUND);

	if ( !rowRemovedSound_ )
		printf(" * GameAudio::setup: Couldn't load %s.\n", GameResc::ROWREMOVEDSOUND);


	if ( !blockStopSound_ ) 
		blockStopSound_ = Mix_LoadWAV(GameResc::BLOCKSTOPSOUND2);

	if ( !blockStopSound_ )
		printf(" * GameAudio::setup: Couldn't load %s.\n", GameResc::BLOCKSTOPSOUND2);
}

void GameAudio::playBlockStopped(void)
{
	if ( useAudio_ )
		Mix_PlayChannel(-1, blockStopSound_, 0);
}

void GameAudio::playKeypress(void)
{
	//Mix_PlayChannel(-1, blockStopSound_, 0);
}

void GameAudio::playRowRemoved(void)
{
	//Mix_PlaySound(popSound_, 0);
	if ( useAudio_ )
		Mix_PlayChannel(-1, rowRemovedSound_, 0);
}

void GameAudio::playGameMusic(void)
{
	if ( useAudio_ )
		Mix_PlayMusic(gameMusic_, -1); // -1 means repeat indefinite
}

void GameAudio::playMenuMusic(void)
{
	if ( useAudio_ )
		Mix_PlayMusic(menuMusic_, -1); // -1 means repeat indefinite
}

void GameAudio::fadeAwayMusic(void)
{
	Mix_FadeOutMusic(1000); // Fade out over 1000ms, returns 1 on success
}

void GameAudio::stopAll(void)
{
	//Mix_HaltMusic();
	Mix_ExpireChannel(-1, 0); // Stop playing all channels after 0 ticks
}

