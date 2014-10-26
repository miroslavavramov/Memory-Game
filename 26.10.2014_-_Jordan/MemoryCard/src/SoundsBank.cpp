/*
 * SoundsBank.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: User
 */

#include "SoundsBank.h"


SoundsBank::SoundsBank() {
	// TODO Auto-generated constructor stub
}

SoundsBank::~SoundsBank() {
	// TODO Auto-generated destructor stub
	delete sound;
}

int SoundsBank::initSoundEffect(string File) {
	Mix_Chunk* TempSound = NULL;

	if((TempSound = Mix_LoadWAV(File.c_str())) == NULL)
	{
		return -1;
	}

	SoundEffectList.push_back(TempSound);

	return (SoundEffectList.size() - 1);
}

void SoundsBank::PlaySoundEffect(unsigned ID)
{
	if ( ID < 0 || ID >= SoundEffectList.size()) return;
	if(SoundEffectList[ID] == NULL) return;


	Mix_PlayChannel(1, SoundEffectList[ID], 0);
}

int SoundsBank::initMusic(string File)
{
	Mix_Music* TempSound = NULL;

	if((TempSound = Mix_LoadMUS(File.c_str())) == NULL)
	{
		return -1;
	}

	SoundMusicList.push_back(TempSound);

	return (SoundMusicList.size() - 1);
}

void SoundsBank::PlayMusic(unsigned ID)
{

	if ( ID < 0 || ID >= SoundMusicList.size()) return;
	if(SoundMusicList[ID] == NULL) return;

	Mix_PlayMusic(SoundMusicList[ID], -1);
}

