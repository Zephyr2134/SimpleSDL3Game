#pragma once
#include "ECS.hpp"

class PositionComponent : public Component
{
    private:
        float xPos, yPos;
    public:
        float x() {return xPos;}
        float y() {return yPos;}

        void init() override
        {
            xPos = 0;
            yPos = 0;
        }

        void update() override
        {
            xPos++;
            yPos++; 
        }

        void setPos(float x, float y)
        {
            xPos = x;
            yPos = y;
        }


};