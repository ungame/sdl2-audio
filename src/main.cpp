#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Input.hpp"
#include "Asset.hpp"
#include "Animation.hpp"
#include "Pistol.hpp"
#include "Zombie.hpp"
#include "Blood.hpp"
#include "Sound.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl init failed: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    int imgInitted = IMG_Init(imgFlags);

    if ((imgInitted&imgFlags) != imgFlags)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl img init failed: %s", IMG_GetError());
        return EXIT_FAILURE;
    }

    if (Mix_Init(MIX_INIT_MP3) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl mix init failed: %s", Mix_GetError());
        return EXIT_FAILURE;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl mix init failed: %s", Mix_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Sounds", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create window failed: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create renderer failed: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    Sound* gunshot = new Sound("assets/audio/9mm-gunshot.mp3");
    Asset* pistolAsset = new Asset(renderer, "assets/weapons/Pistol/Weapon/FULL_Pistol.png");
    Pistol* pistol = new Pistol(renderer, pistolAsset, gunshot, 150, WINDOW_HEIGHT / 2);

    Asset* bloodAsset = new Asset(renderer, "assets/fx/blood-1.png");

    Asset* zombieAsset = new Asset(renderer, "assets/enemies/Zombie.png");
    Zombie* zombie = new Zombie(renderer, zombieAsset, bloodAsset, WINDOW_WIDTH/2, WINDOW_HEIGHT/ 2);  

    Input* input = new Input();

    while(input->listen())
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        pistol->update(input);
        zombie->update(pistol);

        pistol->draw(renderer);
        zombie->draw(renderer);
       
        SDL_RenderPresent(renderer);
    }

    gunshot->destroy();
    pistolAsset->destroy();
    zombieAsset->destroy();
    bloodAsset->destroy();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}