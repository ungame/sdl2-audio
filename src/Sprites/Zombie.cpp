#include "Asset.hpp"
#include "Animation.hpp"
#include "Input.hpp"
#include "Zombie.hpp"
#include "Pistol.hpp"
#include "Blood.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>

Zombie::Zombie(SDL_Renderer* renderer, Asset* asset, Asset* blood, int x, int y)
{
    _scale = 3;
    _flip = SDL_FLIP_HORIZONTAL;
    _wasShot = false;

    int row = 2;
    int frames = 8;
    int speed = 100;

    Animation* walk = new Animation(asset, "zombie_walk", row, frames, speed); 
    _animations[walk->getName()] = walk;
    _currentAnimation = walk->getName();

    _frameData = new SDL_Rect;
    _frameData->w = asset->getWidth() / 13;
    _frameData->h = asset->getHeight() / 6;
    _frameData->x = x - (_frameData->w * _scale / 2);
    _frameData->y = y - (_frameData->h * _scale / 2);

    _blood = new Blood(renderer, blood, _frameData->x-(_frameData->w / 2), _frameData->y - _frameData->h);
}

void Zombie::update(Pistol* pistol)
{
    if (pistol->isShooting())
    {
        SDL_Log("Zombie: Ai!");
        _wasShot = true;
    } else {
        if (_blood->isFinished())
        {
            SDL_Log("Zombie: Cérebro!");
            _wasShot = false;
        }
    }
}

void Zombie::draw(SDL_Renderer* renderer)
{
    _animations[_currentAnimation]->animate(renderer, _frameData, _scale, _flip);
    if (_wasShot) _blood->draw(renderer);
}