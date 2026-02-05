#pragma once
#include <SDL3_image/SDL_image.h>
#include <string>

class TextureManager
{
public:
    static SDL_Texture* CreateTexture(const char* imageRelativePath);
    static void Draw(SDL_Texture* tex, SDL_FRect &src, SDL_FRect &dest);
};
