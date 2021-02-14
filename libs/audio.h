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

Mix_Chunk * load_audio(const char * filename, int volume) {
	Mix_Chunk * audio = Mix_LoadWAV(filename);
	Mix_VolumeChunk(audio, volume);

	return audio;
}


void audio_play_once(Mix_Chunk * audio, int * flag) {
	if(!*flag) {
		Mix_PlayChannel(-1, audio, 0);
		*flag = 1;
	}
}

#endif
