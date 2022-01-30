#include "Animation.hpp"
#include "Asset.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <chrono>

Animation::Animation(Asset *asset, std::string name, int row, int frames, double frameDuration, bool repeat)
{
    _asset = asset;
    _name = name;
    _row = row;
    _frames = frames;
    _frameDuration = frameDuration;
    _currentFrame = 0;
    _animated = 0;
    _started = false;
    _repeat = repeat;
}

void Animation::animate(SDL_Renderer* renderer, SDL_Rect* frameData, int scale, SDL_RendererFlip flip)
{
    if (_started == false)
    {
        _start = std::chrono::system_clock::now();
        _started = true;
    }

    int x = frameData->x;
    int y = frameData->y;
    int w = frameData->w;
    int h = frameData->h;

    _asset->draw(renderer, x, y, w, h, _row, _currentFrame, scale, flip);

    next();
}

void Animation::next()
{
    std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - _start;

    if (_name == "pistol_shooting")
        SDL_Log("Animation=%s, Frame=%d, Elapsed=%lf, FrameDuration=%lf", _name.c_str(), _currentFrame, elapsed.count(), _frameDuration);

    if(elapsed.count() >= _frameDuration)
    {
        if (_currentFrame == _frames - 1) 
        {
            _currentFrame = _repeat ? 0 : _currentFrame;
            _animated++;
        } 
        else 
        {
            _currentFrame++;
        }

        _start = std::chrono::system_clock::now();
    }
}

void Animation::reset()
{
    _currentFrame = 0;
    _animated = 0;
    _started = false;
}