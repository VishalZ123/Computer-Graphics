#include <GL/glut.h>
#include <math.h>

#include "headers/constants.h"
#include "headers/spaceship.h"
#include "headers/game.h"
#include "headers/utils.h"
#include <iostream>

class SpaceStation
{
private:
    float posX, posY, width;

public:
    SpaceStation() {}
    SpaceStation(float width) : width(width)
    {
        posY = randfloat(width / 2, _top - width / 2);
        posX = randfloat(_left + width / 2, _right - width / 2);
    }

    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getWidth() const { return width; }

    void setPosX(float newPosX) { posX = newPosX; }
    void setPosY(float newPosY) { posY = newPosY; }
    void setWidth(float newWidth) { width = newWidth; }
};

SpaceStation spaceStation;

void initSpaceStation()
{
    spaceStation = SpaceStation(200);
}

void drawSpaceStation()
{
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(spaceStation.getPosX() - spaceStation.getWidth() / 2, spaceStation.getPosY() - spaceStation.getWidth() / 2);
    glVertex2f(spaceStation.getPosX() - spaceStation.getWidth() / 2, spaceStation.getPosY() + spaceStation.getWidth() / 2);
    glVertex2f(spaceStation.getPosX() + spaceStation.getWidth() / 2, spaceStation.getPosY() + spaceStation.getWidth() / 2);
    glVertex2f(spaceStation.getPosX() + spaceStation.getWidth() / 2, spaceStation.getPosY() - spaceStation.getWidth() / 2);
    glEnd();
}

void pollSpaceStation()
{
    if (sweepCounter >= totalSweeps && sqrt(pow(spaceStation.getPosX() - spaceship.getCx(), 2) + pow(spaceStation.getPosY() - spaceship.getCy(), 2)) < spaceStation.getWidth() / 2)
    {
        gameState = GAMEWON;
    }
}