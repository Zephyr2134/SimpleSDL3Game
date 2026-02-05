#pragma once

#include "ECS.hpp"
#include "Components.hpp"
#include "../game.hpp"

class KeyboardController : public Component
{

    public:
        TransformComponent *transform;

        void init() override
        {
            transform = nullptr;
            if(entity->hasComponent<TransformComponent>())
                transform = &entity->getComponent<TransformComponent>();
        }

        void update() override
        {
            if(transform){
            if(Game::event.type == SDL_EVENT_KEY_DOWN)
            {
                switch(Game::event.key.key)
                {
                    case SDLK_W:
                        transform->direction[0] = true;
                        break;
                    case SDLK_A:
                        transform->direction[1] = true;
                        break;
                    case SDLK_S:
                        transform->direction[2] = true;
                        break;
                    case SDLK_D:
                        transform->direction[3] = true;
                        break;
                    default:
                        break;
                }
            }

            if(Game::event.type == SDL_EVENT_KEY_UP)
            {
                switch(Game::event.key.key)
                {
                    case SDLK_W:
                        transform->direction[0] = false;
                        break;
                    case SDLK_A:
                        transform->direction[1] = false;
                        break;
                    case SDLK_S:
                        transform->direction[2] = false;
                        break;
                    case SDLK_D:
                        transform->direction[3] = false;
                        break;
                    default:
                        break;
                }
            }
        }
        }

};