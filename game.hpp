#include <SDL3/SDL.h>
#include <string>
#include "player.hpp"

class Game{
    public:
        Game(const std::string& winTitle, int winWidth, int winHeight, bool fullscreen);
        ~Game();

        void Update();
        void Clear();

        bool isRunning(){ return running; }
    private:

        void HandleEvents();
        void RenderGame();

        int flags = 0;
        SDL_Window* win = nullptr;
        SDL_Renderer* ren = nullptr;
        SDL_Event event;
        bool running = false;

        Uint64 NOW;
        Uint64 LAST;
        float deltaTime;

        Player player;
};