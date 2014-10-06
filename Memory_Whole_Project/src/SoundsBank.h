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
	int initSoundEffect(char* File);
	void PlaySoundEffect(int ID);
	int initMusic(char* File);
	void PlayMusic(int ID);
	SoundsBank();
	virtual ~SoundsBank();

};

#endif /* SOUNDSBANK_H_ */
