#ifndef ASSET_H
#define ASSET_H

#include <SDL2/SDL.h>
#include <string>

class Asset
{
    public:
        Asset(SDL_Renderer* renderer, std::string filePath);
        void draw(SDL_Renderer* renderer, int x, int y, int width, int height, int row, int frame, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        inline int getWidth() const { return _w; };
        inline int getHeight() const { return _h; };
        void destroy();

    private:
        SDL_Texture* _texture;
        int _w;
        int _h;
};

#endif