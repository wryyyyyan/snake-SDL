#include <SDL2/SDL_mixer.h>

#ifndef AUDIO_H
#define AUDIO_H

int init_audio() {
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0) {
		printf("erro inicializando SDL_Mixer: %s\n", Mix_GetError());
		return 1;
	}
	return 0;
}

#endif
