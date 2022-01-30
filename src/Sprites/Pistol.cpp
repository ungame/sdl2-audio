#include "Asset.hpp"
#include "Animation.hpp"
#include "Input.hpp"
#include "Pistol.hpp"
#include "Sound.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <chrono>

Pistol::Pistol(SDL_Renderer* renderer, Asset* asset, Sound* gunshot, int x, int y)
{
    _scale = 2;
    _flip = SDL_FLIP_NONE;
    _gunshot = gunshot;
  
    int row = 0;
    int frames = 1;
    double frameDuration = 1.0f;
    Animation* idle = new Animation(asset, "pistol_idle", row, frames, frameDuration);
    _animations[idle->getName()] = idle;
    _currentAnimation = idle->getName();

    frames = 12;
    frameDuration = 0.05f; // 50ms
    Animation* shooting = new Animation(asset, "pistol_shooting", row, frames, frameDuration);
    _animations[shooting->getName()] = shooting;

    _frameData = new SDL_Rect;
    _frameData->w = asset->getWidth() / frames;
    _frameData->h = asset->getHeight();
    _frameData->x = x;
    _frameData->y = y - _frameData->h;
}

void Pistol::update(Input* input)
{
    if (input->isMouseLeftButtonDown() && _currentAnimation != "pistol_shooting")
    {
        // const std::chrono::duration<double> d = std::chrono::system_clock::now() - _lastShot;

        // if (d.count() >= 1)
        // {
        //     _currentAnimation = "pistol_shooting";
        //     _gunshot->play(false);
        // }

        _currentAnimation = "pistol_shooting";
        _gunshot->play(false);

    } else {

        if (_animations[_currentAnimation]->wasAnimated() >= 1 && _currentAnimation == "pistol_shooting")
        {
            _animations[_currentAnimation]->reset();
            _currentAnimation = "pistol_idle";
            // _lastShot = std::chrono::system_clock::now();
        } 
    }
}

void Pistol::draw(SDL_Renderer* renderer)
{
    _animations[_currentAnimation]->animate(renderer, _frameData, _scale, _flip);
}