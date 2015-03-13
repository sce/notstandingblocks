#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include <stdio.h> // printf
#include <stdlib.h> // atexit

/*
 * Sets up/handles audio (low-level).
 *
 */

class AudioDriver
{
	private:
		static int instances;
		static int openAudio;
		
		int audioRate_;
		Uint16 audioFormat_;
		int audioChannels_;
		int audioBuffers_;

		void closeAudio(void);

	public:
		AudioDriver(void);
		~AudioDriver(void);

		int setup(void); // returns 0 on success, -1 on failure
		
		int play(Mix_Music* music);
};

#endif
