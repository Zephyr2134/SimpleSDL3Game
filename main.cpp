#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "game.hpp"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    Game game("Window Title", 800, 600, true);

    while(game.isRunning())
    {
    game.Update();
    }
    game.Clear();
    return 0;
}
