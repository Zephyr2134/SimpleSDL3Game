#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "player.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class Game{
    public:
        Game(const std::string& winTitle, int winWidth, int winHeight, bool fullscreen);
        ~Game();

        void HandleEvents();
        void Update();
        void RenderGame();
        void Clear();

        bool isRunning(){ return running; }
    private:

        void handleFps();
        void handleDeltaTime();

        int flags = 0;
        SDL_Window* win = nullptr;
        SDL_Renderer* ren = nullptr;
        SDL_Event event;
        bool running = false;

        Uint64 NOW;
        Uint64 LAST;
        float deltaTime;
        const int FPS = 60;
        const int frameDelay;
        int frameTime;

        Player player;
};