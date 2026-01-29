#include "player.hpp"
#include <SDL3_image/SDL_image.h>
#include "textureManager.hpp"

Player::Player(SDL_Renderer* ren, const std::string& relativeImgPath, float imgWidth, float imgHeight, float playerWidth, float playerHeight) : 
dstRect{0,0,playerWidth,playerHeight},
srcRect{0,0,imgHeight,imgHeight},
dir{false,false,false,false}
{
    playerTexture = TextureManager::CreateTexture(ren, relativeImgPath);
}

Player::~Player()
{
    SDL_DestroyTexture(playerTexture);
}

void Player::InputHandling(SDL_Event& event)
{
    switch(event.type)
    {
    case SDL_EVENT_KEY_DOWN:
            switch(event.key.key)
            {
                case SDLK_W:
                    dir[0] = true;
                    break;
                case SDLK_S:
                    dir[1] = true;
                    break;
                case SDLK_A:
                    dir[2] = true;
                    break;
                case SDLK_D:
                    dir[3] = true;
                    break;
            }
            break;
        case SDL_EVENT_KEY_UP:
            switch(event.key.key)
            {
                case SDLK_W:
                    dir[0] = false;
                    break;
                case SDLK_S:
                    dir[1] = false;
                    break;
                case SDLK_A:
                    dir[2] = false;
                    break;
                case SDLK_D:
                    dir[3] = false;
                    break;
            }
            break;
        }
}

void Player::UpdatePlayer(float dt)
{
    velY = (dir[0]*-1 + dir[1]) * playerSpeed;
    velX = (dir[2]*-1 + dir[3]) * playerSpeed;

    if(velX != 0 && velY != 0)
    {
        velY = velY * diagonalScale;
        velX = velX * diagonalScale;
    }

    dstRect.y += velY * dt;
    dstRect.x += velX * dt;
}

void Player::RenderPlayer(SDL_Renderer* ren)
{
    SDL_RenderTexture(ren, playerTexture, &srcRect, &dstRect);
}