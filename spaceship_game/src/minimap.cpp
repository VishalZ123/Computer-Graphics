#include "include/freeglut/include/GL/glut.h"
#include <math.h>

#include "include/constants.h"
#include "include/utils.h"
#include "include/game.h"
#include "include/spaceship.h"
#include "include/spacestation.h"
#include "include/asteroids.h"

GLuint minimap_texture;
GLuint needle_texture;
float minimapSize = 200.0f;
float posx = _left + minimapSize / 2 + 10;
float posy = _bottom + minimapSize / 2 + 10;
float angle = 0.0f;

void rectCoordsToPolarCoords(float x, float y, float *r, float *theta)
{
    // map the square coordinates to polar coordinates
    x = 2 * (x - _right) / (_right - _left) + 1;
    y = 2 * (y - _top) / (_top - _bottom) + 1;
    float distance = sqrt(x * x + y * y) < 1 ? sqrt(x * x + y * y) : 1;
    *r = (minimapSize / 2) * distance;
    *theta = atan2(y, x);
}

void initMinimap()
{
    generateTexture(&minimap_texture, "./assets/minimap_texture.png");
}

void drawMiniMap()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, minimap_texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(posx - minimapSize / 2, posy - minimapSize / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(posx + minimapSize / 2, posy - minimapSize / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(posx + minimapSize / 2, posy + minimapSize / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(posx - minimapSize / 2, posy + minimapSize / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    glVertex2f(posx - minimapSize / 2, posy);
    glVertex2f(posx + minimapSize / 2, posy);
    glEnd();

    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    glVertex2f(posx, posy - minimapSize / 2);
    glVertex2f(posx, posy + minimapSize / 2);
    glEnd();

    float r_spaceship = 0, theta_spaceship = 0, r_spacestation = 0, theta_spacestation = 0;
    rectCoordsToPolarCoords(spaceship.getCx(), spaceship.getCy(), &r_spaceship, &theta_spaceship);
    rectCoordsToPolarCoords(spaceStation.getPosX(), spaceStation.getPosY(), &r_spacestation, &theta_spacestation);

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(posx + r_spaceship * cos(theta_spaceship), posy + r_spaceship * sin(theta_spaceship)); // draw spaceship on minimap
    if (sweepCounter >= totalSweeps)
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(posx + r_spacestation * cos(theta_spacestation), posy + r_spacestation * sin(theta_spacestation)); // draw spacestation on minimap
    }
    glEnd();

    // draw asteroids on minimap
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < numAsteroids; i++)
    {
        float r_asteroid = 0, theta_asteroid = 0;
        rectCoordsToPolarCoords(asteroids[i].getX(), asteroids[i].getY(), &r_asteroid, &theta_asteroid);
        if (r_asteroid < minimapSize / 2)
        {
            glVertex2f(posx + r_asteroid * cos(theta_asteroid), posy + r_asteroid * sin(theta_asteroid));
        }
    }
    glEnd();
}
