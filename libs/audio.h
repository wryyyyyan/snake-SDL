#include <SDL2/SDL_mixer.h>

#ifndef AUDIO_H
#define AUDIO_H

int init_audio();
Mix_Chunk * load_audio(const char * filename, int volume);
void audio_play_once(Mix_Chunk * audio, int * flag);

#endif
