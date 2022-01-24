#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Asset.hpp"
#include "Animation.hpp"
#include "Input.hpp"
#include "Pistol.hpp"
#include "Blood.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>

class Zombie
{
    public:
        Zombie(SDL_Renderer* renderer, Asset* asset, Asset* blood, int x, int y);
        void update(Pistol* pistol);
        void draw(SDL_Renderer* renderer);

    private:
        SDL_RendererFlip _flip;
        int _scale;
        SDL_Rect* _frameData;
        std::map<std::string, Animation*> _animations;
        std::string _currentAnimation;
        Blood* _blood;
        bool _wasShot;
};

#endif