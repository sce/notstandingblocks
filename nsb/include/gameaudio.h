#ifndef __GAMEAUDIO_H__
#define __GAMEAUDIO_H__

#include "SDL/SDL_mixer.h"

#include "audiodriver.h"
#include "gameresc.h"
/*
 * Handles all the audio for the game, not the the menu.
 *
 */


class GameAudio
{
	private:
		static int instances;
		static AudioDriver *audioDrv;
		static bool audioIsSetup_; // do we need to call Audio::setup()?
		static bool useAudio_; // can/should we use audio?

		static Mix_Music *gameMusic_;
		static Mix_Music *wonMusic_;
		static Mix_Music *menuMusic_;
		
		static Mix_Chunk *rowRemovedSound_;
		static Mix_Chunk *blockStopSound_;

	public:
		GameAudio(void);
		~GameAudio(void);

		void setup(void);

		void playGameMusic(void);
		void playMenuMusic(void);
		
		void playRowRemoved(void);
		void playBlockStopped(void);
		void playKeypress(void);

		void fadeAwayMusic(void);
		void stopAll(void);
};

#endif
