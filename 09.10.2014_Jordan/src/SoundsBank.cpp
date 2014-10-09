/*
 * SoundsBank.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: User
 */

#include "SoundsBank.h"
#include <iostream>
using namespace std;

SoundsBank::SoundsBank() {
	// TODO Auto-generated constructor stub

}

int SoundsBank::initSoundEffect(const char* File) {
	Mix_Chunk* TempSound = NULL;

	if((TempSound = Mix_LoadWAV(File)) == NULL)
	{
		return -1;
	}

	SoundEffectList.push_back(TempSound);

	return (SoundEffectList.size() - 1);
}

void SoundsBank::PlaySoundEffect(unsigned int ID)
{
	if ( ID < 0 || ID >= SoundEffectList.size()) return;
	if(SoundEffectList[ID] == NULL) return;


	Mix_PlayChannel(-1, SoundEffectList[ID], 0);
}

int SoundsBank::initMusic(const char* File)
{
	Mix_Music* TempSound = NULL;

	if((TempSound = Mix_LoadMUS(File)) == NULL)
	{
		return -1;
	}

	SoundMusicList.push_back(TempSound);

	return (SoundMusicList.size() - 1);
}

void SoundsBank::PlayMusic(unsigned int ID)
{
//	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4097 );
	if ( ID < 0 || ID >= SoundMusicList.size()) return;
	if(SoundMusicList[ID] == NULL) return;

	Mix_PlayMusic(SoundMusicList[ID], 1);
}

SoundsBank::~SoundsBank() {
	// TODO Auto-generated destructor stub
}

