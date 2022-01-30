#include "Blood.hpp"
#include "Asset.hpp"
#include "Animation.hpp"
#include "Input.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>

Blood::Blood(SDL_Renderer* renderer, Asset* asset, int x, int y)
{
    _flip = SDL_FLIP_NONE;
    _scale = 1;
    
    int row = 0;
    int frames = 14;
    double frameDuration = 0.05f;

    Animation* blood = new Animation(asset, "blood", row, frames, frameDuration);
    _animations[blood->getName()] = blood;
    _currentAnimation = blood->getName();
    
    _frameData = new SDL_Rect;
    _frameData->w = asset->getWidth() / frames + 1;
    _frameData->h = asset->getHeight();
    _frameData->x = x;
    _frameData->y = y;
}

void Blood::update()
{

}

void Blood::draw(SDL_Renderer* renderer)
{
    _animations[_currentAnimation]->animate(renderer, _frameData, _scale, _flip);
}