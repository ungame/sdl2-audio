#include "Asset.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

Asset::Asset(SDL_Renderer* renderer, std::string filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl img load %s failed: %s", filePath.c_str(), IMG_GetError());
        return;
    }

    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (_texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create texture from surface failed: %s", SDL_GetError());
        return;
    }

    _w = surface->w;
    _h = surface->h;

    SDL_FreeSurface(surface);
}

void Asset::draw(SDL_Renderer* renderer, int x, int y, int width, int height, int row, int frame, int scale, SDL_RendererFlip flip)
{
    // src recorta um pedaço da textura
    SDL_Rect src;
    src.x = width * frame;
    src.y = height * row;
    src.w = width;
    src.h = height;

    // dst posiciona o pedaço da textura na tela
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = width * scale;
    dst.h = height * scale;

    SDL_RenderCopyEx(renderer, _texture, &src, &dst, 0, nullptr, flip);
}

void Asset::destroy()
{
    if (_texture != nullptr)
    {
        SDL_DestroyTexture(_texture);
    }
}