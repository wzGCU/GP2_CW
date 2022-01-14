#include "AudioRelated.h"


/* Constructor which passes the parameters to Open Audio */

AudioRelated::AudioRelated() 
{
    /* Variables speak for themself :p */
    int audioRate = 22050;
    Uint16 audioFormat = AUDIO_S16SYS;
    int audioChannels = 2;
    int audioBuffers = 4096;
    if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
        exit(-1);
    }
}


/* Deconstructor */

AudioRelated::~AudioRelated() {
    SDL_Quit();
}


/* Function to add (load) a sound effect */

void AudioRelated::AddSoundEffect(const char* path){
    Mix_Chunk* tmpChunk = Mix_LoadWAV(path);

    if (tmpChunk != nullptr)
    {
        mSoundEffectBank.push_back(tmpChunk);
        std::cout << (mSoundEffectBank.size() - 1) << " Sound is Ready, path: " << path << '\n';
    }
    else
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
    }

}


/* Function to play the set sound effect */

void AudioRelated::PlaySoundEffect(const int id)  const{
    if (id > mSoundEffectBank.size() - 1)
    {
        std::cout << "Sound out of range.\n";
        return;
    }

    Mix_PlayChannel(-1, mSoundEffectBank[id], 0);

    std::cout << "Played Sound: " << id << '\n';

}


/* Function to add a Background track */

void AudioRelated::AddBGMusicTrack(const char* path)
{
    bgMusic = Mix_LoadMUS(path);

    if (bgMusic == NULL)
    {
        printf("Failed to load bg music! SDL_mixer Error: %s\n", Mix_GetError());
    }

}

/* Function to play the audio track */

void AudioRelated::PlayBGMusic() {
    if (Mix_PlayingMusic() == 0)
    {
        //Play the music
        Mix_PlayMusic(bgMusic, -1);
    }

}


/* Function to stop playing bg music */

void AudioRelated::StopBGMusic() {
    Mix_HaltMusic();
}