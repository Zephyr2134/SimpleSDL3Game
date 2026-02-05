#pragma once
#include <SDL3/SDL.h>
#include <string>

class Game {
public:
    Game(const std::string& winTitle, int winWidth, int winHeight, bool fullscreen);
    ~Game();

    void HandleEvents();
    void Update();
    void RenderGame();
    void Clear();

    bool isRunning() { return running; }

    static SDL_Renderer* ren;
    static SDL_Event event;
    static float deltaTime;
private:
    void handleDeltaTime();

    int flags = 0;
    SDL_Window* win = nullptr;
    bool running = false;

    Uint64 NOW = 0;
    Uint64 LAST = 0;
    const int FPS = 60;
    const int frameDelay;
    int frameTime = 0;
};
