#ifndef ANIMATION_H
#define ANIMATION_H

#include "Asset.hpp"

#include <SDL2/SDL.h>
#include <string>

class Animation
{
    public:
        Animation(Asset *asset, std::string name, int row, int frames, int speed);
        void animate(SDL_Renderer* renderer, SDL_Rect* frameData, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        inline std::string getName() { return _name; }
        inline bool isFinished() { return _isFinished; }

    private:
        Asset* _asset;
        std::string _name;
        int _row;
        int _frames;
        int _speed;
        int _currentFrame;
        bool _isFinished;
};

#endif