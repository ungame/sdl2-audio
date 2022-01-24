#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class Sound
{
    public:
        Sound(std::string filePath);
        void play(bool repeat);
        void pause();
        void resume();
        void halt();
        void destroy();

    private:
        Mix_Music* _sound;
};

#endif