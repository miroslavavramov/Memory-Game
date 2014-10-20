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
#include <iostream>
#include <string>
using namespace std;


class SoundsBank {
public:
	static SoundsBank* sound;
	vector<Mix_Chunk*> SoundEffectList;
	vector<Mix_Music*> SoundMusicList;

	int initSoundEffect(string);
	void PlaySoundEffect(unsigned ID);
	int initMusic(string);
	void PlayMusic(unsigned ID);

	SoundsBank();
	virtual ~SoundsBank();

};

#endif /* SOUNDSBANK_H_ */
