//
//  Copyright (C) <2021>  <Yan Alcantara>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "audio.h"

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
