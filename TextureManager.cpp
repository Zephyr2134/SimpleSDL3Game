#include "textureManager.hpp"

SDL_Texture* TextureManager::CreateTexture(SDL_Renderer* ren, const std::string& imageRelativePath)
{
    std::string basePath = SDL_GetBasePath();
    std::string fullPath = basePath + imageRelativePath;

    SDL_Surface* surf = IMG_Load(fullPath.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);

    SDL_DestroySurface(surf);

    if(tex == NULL)
    {
        SDL_Log("Texture failed to load %s", SDL_GetError());
    }

    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);

    return tex;
}