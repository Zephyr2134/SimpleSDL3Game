#include "game.hpp"
#include "ECS/Components.hpp"

//When a varible is static, it should be initialized at the top of the script.
SDL_Renderer* Game::ren = nullptr;
SDL_Event Game::event;
Manager manager;
float Game::deltaTime;

Game::Game(const std::string& winTitle, int winWidth, int winHeight, bool fullscreen) :
    frameDelay(1000 / FPS)
{
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

    win = SDL_CreateWindow(winTitle.c_str(), winWidth, winHeight, flags);
    if (!win) {
        SDL_Log("Window failed to initialize: %s", SDL_GetError());
        return;
    }

    Game::ren = SDL_CreateRenderer(win, nullptr);
    if (!ren) {
        SDL_Log("Renderer failed to initialize: %s", SDL_GetError());
        return;
    }

    running = true;
    LAST = SDL_GetPerformanceCounter();
    NOW = LAST;

    Entity& player = manager.addEntity();
    player.addComponent<TransformComponent>(20.0f, 20.0f, 640.0f, 640.0f, 200);
    player.addComponent<SpriteComponent>("assets\\player\\IDLE\\idle_down.png", 8, 1);
    player.addComponent<KeyboardController>();
}

Game::~Game()
{
    Clear();
}

void Game::HandleEvents()
{
    SDL_PollEvent(&event);
    if (event.type == SDL_EVENT_QUIT) running = false;
}

void Game::Update()
{
    handleDeltaTime();

    manager.refresh();
    manager.update();
}

void Game::RenderGame()
{
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_RenderClear(ren);
    manager.draw();
    SDL_RenderPresent(ren);
}

void Game::handleDeltaTime()
{
    NOW = SDL_GetPerformanceCounter();
    deltaTime = (NOW - LAST) / (float)SDL_GetPerformanceFrequency();
    LAST = NOW;
    if (deltaTime > 0.1) deltaTime = 0.1;
}

void Game::Clear()
{
    manager.entities.clear();

    if (Game::ren) { SDL_DestroyRenderer(ren); ren = nullptr; }
    if (win) { SDL_DestroyWindow(win); win = nullptr; }
}
