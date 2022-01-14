#pragma once
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <iostream>
#include <vector>

/* Fun fact: it is called as AudioRelated cause the tutorial said to name 
the class as something audio related and I am very funny */
class AudioRelated
{
public:

	AudioRelated();
	~AudioRelated();

	void AddSoundEffect(const char* path); // function to add (load) a sound effect 
	void PlaySoundEffect(const int which) const; // function to play the set sound effect
	void AddBGMusicTrack(const char* path); // function to add a bg track
	void PlayBGMusic(); // function to play the bg track
	void StopBGMusic(); //function to stop bg track

private:

	Mix_Music* bgMusic;
	std::vector<Mix_Chunk*> mSoundEffectBank;

};

