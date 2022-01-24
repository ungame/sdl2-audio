#include "Animation.hpp"
#include "Asset.hpp"

#include <SDL2/SDL.h>
#include <string>

Animation::Animation(Asset *asset, std::string name, int row, int frames, int speed)
{
    _asset = asset;
    _name = name;
    _row = row;
    _frames = frames;
    _speed = speed;
    _currentFrame = 0;
    _isFinished = false;
}

void Animation::animate(SDL_Renderer* renderer, SDL_Rect* frameData, int scale, SDL_RendererFlip flip)
{
    _currentFrame = (SDL_GetTicks() / _speed) % _frames;

    int x = frameData->x;
    int y = frameData->y;
    int w = frameData->w;
    int h = frameData->h;

    _asset->draw(renderer, x, y, w, h, _row, _currentFrame, scale, flip);
    
    _isFinished = _currentFrame == _frames - 1;
}