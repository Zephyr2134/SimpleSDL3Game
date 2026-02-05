#pragma once

#include "Components.hpp"
#include <SDL3/SDL.h>
#include "../TextureManager.hpp"

class SpriteComponent : public Component
{
private:
    TransformComponent* transform = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_FRect srcRect{}, dstRect{};
    float fullWidth = 0;
    float fullHeight = 0;
    int imagesX = 0;
    int imagesY = 0;
    const char* path;

public:
    SpriteComponent() = default;
    SpriteComponent(const char* imagePath, int spritesXDir, int spritesYDir) : 
    path(imagePath), 
    imagesX(spritesXDir), 
    imagesY(spritesYDir) {}

    void setTex(const char* imagePath, int spritesXDir, int spritesYDir)
    {
        path = imagePath;
        imagesX = spritesXDir;
        imagesY = spritesYDir;
        texture = TextureManager::CreateTexture(path);

        if (texture) {
            SDL_GetTextureSize(texture,&fullWidth, &fullHeight);
        }

        srcRect.w = fullWidth / imagesX;
        srcRect.h = fullHeight / imagesY;

    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        dstRect = {0,0,0,0};
        dstRect.w = transform->width;
        dstRect.h = transform->height;
        setTex(path, imagesX, imagesY);
    }

    void update() override
    {
        if (transform) {
            dstRect.x = transform->xPos;
            dstRect.y = transform->yPos;
        }
    }

    void draw() override
    {
        if (texture)
            TextureManager::Draw(texture, srcRect, dstRect);
    }

    ~SpriteComponent() override
    {
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
};
