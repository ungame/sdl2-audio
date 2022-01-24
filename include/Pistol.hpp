#ifndef PISTOL_H
#define PISTOL_H

#include "Asset.hpp"
#include "Animation.hpp"
#include "Input.hpp"
#include "Sound.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <chrono>

class Pistol
{
    public:
        Pistol(SDL_Renderer* renderer, Asset* asset, Sound* _shootingSound, int x, int y);
        void update(Input* input);
        void draw(SDL_Renderer* renderer);
        inline bool isShooting() { return _currentAnimation == "pistol_shooting"; }

    private:
        std::map<std::string, Animation*> _animations;
        SDL_RendererFlip _flip;
        int _scale;
        SDL_Rect* _frameData;
        std::string _currentAnimation;
        Sound* _gunshot;
        std::chrono::time_point<std::chrono::system_clock> _lastShot;
};

#endif