#include "Sound.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

Sound::Sound(std::string filePath)
{
    _sound = Mix_LoadMUS(filePath.c_str());
    if (_sound == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl mix load mus %s failed: %s", filePath.c_str(), Mix_GetError());
        return;
    }
}

void Sound::play(bool repeat)
{
    Mix_PlayMusic(_sound, repeat ? -1 : 1);
}

void Sound::pause()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PauseMusic();
    }
}

void Sound::resume()
{
    if(Mix_PausedMusic() == 0)
    {
        Mix_ResumeMusic();
    }
}

void Sound::halt()
{
    Mix_HaltMusic();
}

void Sound::destroy()
{
    if (_sound != nullptr)
    {
        Mix_FreeMusic(_sound);
    }
}