#pragma once
#include "Components.hpp"
#include "../game.hpp"

class TransformComponent : public Component
{
        
    public:
        float xPos, yPos;
        float width, height;
        float velX, velY;
        int speed = 0;
        bool direction[4] = {false, false, false, false};

        TransformComponent()
        {
            xPos = 0;
            yPos = 0;
        }

        TransformComponent(float x, float y)
        {
            xPos = x;
            yPos = y;
            width = 0;
            height = 0;
        }

        TransformComponent(float x, float y, float w, float h)
        {
            xPos = x;
            yPos = y;
            width = w;
            height = h;
        }

        TransformComponent(float x, float y, float w, float h, int spd)
        {
            xPos = x;
            yPos = y;
            width = w;
            height = h;
            speed = spd;
        }

        void init() override
        {
            velX = 0;
            velY = 0;
        }

        void update() override
        {
    
            setVelocity(
            ((direction[1]*-1) + direction[3]) * speed * Game::deltaTime, 
            ((direction[0]*-1) + direction[2]) * speed * Game::deltaTime);

            xPos += velX;
            yPos += velY;
        }

        void setPos(float x, float y)
        {
            xPos = x;
            yPos = y;
        }

        void setVelocity(float x, float y)
        {
            velX = x;
            velY = y;
        }


};

