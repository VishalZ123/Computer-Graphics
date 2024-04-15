#ifndef SPACESTATION_H
#define SPACESTATION_H

#include "utils.h"

class SpaceStation
{
private:
    float posX, posY, width;

public:
    SpaceStation() {}
    SpaceStation(float width) : width(width)
    {
        // randomly place the spacestation in upper half of the screen
        posY = randfloat(width / 2, _top - width / 2);
        posX = randfloat(_left + width / 2, _right - width / 2);
    }

    // getter and setter methods
    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getWidth() const { return width; }

    void setPosX(float newPosX) { posX = newPosX; }
    void setPosY(float newPosY) { posY = newPosY; }
    void setWidth(float newWidth) { width = newWidth; }
};

extern SpaceStation spaceStation;
void drawSpaceStation();
void pollSpaceStation();
void initSpaceStation();

#endif