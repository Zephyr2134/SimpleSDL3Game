#include <SDL3/SDL.h>
#include <string>

class Player
{
    public:
        Player(SDL_Renderer* ren, const std::string& relativeImgPath, float imgWidth, float imgHeight, float playerWidth, float playerHeight);
        ~Player();

        void InputHandling(SDL_Event& event);
        void UpdatePlayer(float dt);
        void RenderPlayer(SDL_Renderer* ren);

    private:
        SDL_FRect dstRect;
        SDL_FRect srcRect;
        SDL_Texture* playerTexture;
        bool dir[4];
        float velY = 0;
        float velX = 0;
        int playerSpeed = 400;
        const float diagonalScale = 0.70710678f;
};