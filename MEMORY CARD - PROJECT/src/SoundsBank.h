/*
 * SoundsBank.h
 *
 *  Created on: Sep 30, 2014
 *      Author: User
 */

#ifndef SOUNDSBANK_H_
#define SOUNDSBANK_H_

#include "SDL.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
using namespace std;

class SoundsBank {
public:
	static SoundsBank* sound;
	vector<Mix_Chunk*> SoundEffectList;
	vector<Mix_Music*> SoundMusicList;
	int initSoundEffect(const char* File);
	void PlaySoundEffect(unsigned int ID);
	int initMusic(const char* File);
	void PlayMusic(unsigned int ID);
	SoundsBank();
	virtual ~SoundsBank();

};

#endif /* SOUNDSBANK_H_ */
