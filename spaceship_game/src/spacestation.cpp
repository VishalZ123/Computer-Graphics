#include "include/freeglut/include/GL/glut.h"
#include <math.h>

#include "include/constants.h"
#include "include/spaceship.h"
#include "include/game.h"
#include "include/utils.h"
#include "include/spacestation.h"

SpaceStation spaceStation;
GLuint spacestation_texture;

void initSpaceStation()
{
    spaceStation = SpaceStation(400);                                            // Create spacestation
    generateTexture(&spacestation_texture, "./assets/spacestation_texture.png"); // Load spacestation texture
}

void drawSpaceStation()
{
    // Draw spacestation
    // a square with the texture of the spacestation

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spacestation_texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(spaceStation.getPosX() - spaceStation.getWidth() / 2, spaceStation.getPosY() - spaceStation.getWidth() / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(spaceStation.getPosX() + spaceStation.getWidth() / 2, spaceStation.getPosY() - spaceStation.getWidth() / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(spaceStation.getPosX() + spaceStation.getWidth() / 2, spaceStation.getPosY() + spaceStation.getWidth() / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(spaceStation.getPosX() - spaceStation.getWidth() / 2, spaceStation.getPosY() + spaceStation.getWidth() / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void pollSpaceStation()
{
    // Check if the spaceship is close enough to the spacestation
    if (sweepCounter >= totalSweeps && sqrt(pow(spaceStation.getPosX() - spaceship.getCx(), 2) + pow(spaceStation.getPosY() - spaceship.getCy(), 2)) < 20)
    {
        gameState = GAMEWON; // Set game state to game won
    }
}