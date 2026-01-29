#include <SDL3_image/SDL_image.h>
#include <string>

class TextureManager
{
    public:
        static SDL_Texture* CreateTexture(SDL_Renderer* ren, const std::string& imageRelativePath);
};