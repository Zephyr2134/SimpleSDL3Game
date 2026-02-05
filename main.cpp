#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "game.hpp"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    {
    Game game("Window Title", 800, 600, true);

    while (game.isRunning()) {
        game.HandleEvents();
        game.Update();
        game.RenderGame();
    }

    game.Clear();
    }
    SDL_Quit();

    return 0;
}