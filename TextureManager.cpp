#include "TextureManager.hpp"
#include "game.hpp"

SDL_Texture* TextureManager::CreateTexture(const char* imageRelativePath)
{
    const char* base = SDL_GetBasePath();
    if (!base) {
        SDL_Log("SDL_GetBasePath failed: %s", SDL_GetError());
        return nullptr;
    }

    std::string fullPath = std::string(base) + imageRelativePath;
    SDL_free((void*)base);

    SDL_Surface* surf = IMG_Load(fullPath.c_str());
    if (!surf) {
        SDL_Log("IMG_Load failed: %s", SDL_GetError());
        return nullptr;
    }

     if (!Game::ren) {
    SDL_Log("Error: Game::ren is nullptr when creating texture!");
    SDL_DestroySurface(surf);
    return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::ren, surf);
    SDL_DestroySurface(surf);

    if (!tex) {
        SDL_Log("CreateTexture failed: %s", SDL_GetError());
        return nullptr;
    }

    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_FRect &src, SDL_FRect &dest)
{
    if (!SDL_RenderTexture(Game::ren, tex, &src, &dest))
    {
        SDL_Log("Draw failed: %s", SDL_GetError());
    }
}
