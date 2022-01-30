#ifndef ANIMATION_H
#define ANIMATION_H

#include "Asset.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <chrono>

class Animation
{
    public:
        Animation(Asset *asset, std::string name, int row, int frames, double frameDuration, bool repeat = true);
        void animate(SDL_Renderer* renderer, SDL_Rect* frameData, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void reset();
        inline std::string getName() { return _name; }
        inline bool wasAnimated() { return _animated; }


    private:
        Asset* _asset;
        std::string _name;
        int _row;
        int _frames;
        double _frameDuration; // time in seconds, ex: 1 = one second, 0.1 = 100ms per frame
        int _currentFrame;
        int _animated;
        std::chrono::time_point<std::chrono::system_clock> _start;
        bool _started;
        bool _repeat;

        void next();
};

#endif