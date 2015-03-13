#include "audiodriver.h"

int AudioDriver::openAudio = 0;
int AudioDriver::instances = 0;

AudioDriver::AudioDriver(void)
{
		//printf("AudioDriver(): %i\n", instances+1);
		instances++;
		
		//audioRate_ = 22050;
		audioRate_ = 44100;
		audioFormat_ = AUDIO_S16SYS;
		audioChannels_ = 2;
		audioBuffers_ = 4096;
}

AudioDriver::~AudioDriver(void)
{
	//printf("~AudioDriver(): %i\n", instances-1);
	if ( --instances == 0 ) {
		closeAudio();	
	}
}

int AudioDriver::setup(void)
{
	// setup/start audio system
	if( Mix_OpenAudio(audioRate_, audioFormat_, 
							audioChannels_, audioBuffers_) != 0) 
	{
		//printf(" * AudioDriver::setup(): Can't setup audio.\n");
		return -1;
	}

	//printf("+ openAudio: %i\n", ++openAudio);
	return 0;
}

void AudioDriver::closeAudio() {
	while ( --openAudio > 0 ) {
		Mix_CloseAudio();
	}
	openAudio = 0;
	
	//printf("- openAudio: %i\n", openAudio);
}
		
