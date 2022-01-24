#ifndef BLOOD_H
#define BLOOD_H

#include "Asset.hpp"
#include "Animation.hpp"
#include "Input.hpp"
#include "Sound.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>

class Blood
{
    public:
        Blood(SDL_Renderer* renderer, Asset* asset, int x, int y);
        void update();
        void draw(SDL_Renderer* renderer);
        inline bool isFinished() { return _animations[_currentAnimation]->isFinished(); }

    private:
        SDL_RendererFlip _flip;
        int _scale;
        SDL_Rect* _frameData;
        std::map<std::string, Animation*> _animations;
        std::string _currentAnimation;
};

#endif