#include "game.hpp"

Manager manager;
auto& newPlayer(manager.addEntity()); 

Game::Game(const std::string& winTitle, int winWidth, int winHeight, bool fullscreen) : 
flags(fullscreen * SDL_WINDOW_FULLSCREEN), 
win(SDL_CreateWindow(winTitle.c_str(), winWidth, winHeight, flags)), 
ren(SDL_CreateRenderer(win, NULL)), 
player(ren, "assets/player/IDLE/idle_down.png", 95.0f, 80.0f, 500.0f, 500.0f),
frameDelay(1000 / FPS)
{
    if(win == NULL)
    {
        SDL_Log("Window failed to initialize %s", SDL_GetError());
        return;
    }
    else if(ren == NULL)
    {
        SDL_Log("Renderer failed to initialize %s", SDL_GetError());
        return;
    }
    running = true;
    LAST = 0;
    deltaTime = 0;

    newPlayer.addComponent<PositionComponent>();
}

Game::~Game()
{}

void Game::HandleEvents()
{
    SDL_PollEvent(&event);
    player.InputHandling(event);
    switch(event.type)
    {
        case SDL_EVENT_QUIT:
            running = false;
            break;
    }
}

void Game::Update()
{
    handleDeltaTime();

    player.UpdatePlayer(deltaTime);

    manager.update();
    std::cout << newPlayer.getComponent<PositionComponent>().x() << '.' << newPlayer.getComponent<PositionComponent>().y() << std::endl;

    handleFps();
}

void Game::RenderGame()
{
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_RenderClear(ren);

    player.RenderPlayer(ren);

    SDL_RenderPresent(ren);
}

void Game::handleDeltaTime()
{
    NOW = SDL_GetPerformanceCounter();
    deltaTime = (NOW - LAST) / (float)SDL_GetPerformanceFrequency();
    LAST = NOW;
}

void Game::handleFps()
{
    frameTime = SDL_GetPerformanceCounter() - NOW;
    if(frameDelay > frameTime)
    {
        SDL_Delay(frameTime - frameDelay);
    }
}

void Game::Clear()
{
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
}