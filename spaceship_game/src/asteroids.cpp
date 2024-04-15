#include <cstdlib>
#include <math.h>
#include "include/freeglut/include/GL/glut.h"

#include "include/spaceship.h"
#include "include/constants.h"
#include "include/utils.h"
#include "include/game.h"
#include "include/asteroids.h"

Asteroid asteroids[numAsteroids];

bool didCollide(Asteroid asteroid, Spaceship spaceship) // check if asteroid and spaceship collided
{
    if (sqrt(pow(asteroid.getX() - spaceship.getCx(), 2) + pow(asteroid.getY() - spaceship.getCy(), 2)) <= asteroid.getSize() + spaceship.getL() / (2 * sqrt(3)))
    {
        return true;
    }
    return false;
}

Asteroid randomAsteroid() // generate a randomly placed asteroid of random size and speed
{
    int sides = randint(6, 10);
    float x = static_cast<float>(randint(_left - 5, _right - 5));
    float size = static_cast<float>(randfloat(20.0f, 100.0f));
    float speedX = static_cast<float>(randRange(-1, 0, 0, 1));
    int speedY = randint(4, 10);
    return Asteroid(x, size, sides, speedX, speedY);
}

void initAsteroids() // initiate asteroids
{
    for (int i = 0; i < numAsteroids; i++)
    {
        asteroids[i] = randomAsteroid();
    }
}

void drawAsteroids()
{
    for (int i = 0; i < numAsteroids; i++)
    {
        const int sides = asteroids[i].getSides();
        const float(*vertices)[2] = asteroids[i].getVertices();

        // rotate the asteroid with time
        glPushMatrix();
        glTranslatef(asteroids[i].getX(), asteroids[i].getY(), 0);
        int angle = asteroids[i].getX() * 5;
        glRotatef(angle, 0, 0, 1);
        glTranslatef(-asteroids[i].getX(), -asteroids[i].getY(), 0);

        glBegin(GL_POLYGON);
        glColor3f(0.325f, 0.274f, 0.258f);
        for (int j = 0; j < sides; j++)
        {
            glVertex2f(vertices[j][0], vertices[j][1]);
        }
        glEnd();

        glPopMatrix();
    }
}

void updateAsteroids()
{
    for (int i = 0; i < numAsteroids; i++)
    {
        asteroids[i].updatePosition();
        if (didCollide(asteroids[i], spaceship)) // if the asteroids collide with the spaceship
        {
            spaceship.setHealth(spaceship.getHealth() - asteroids[i].getSize() / 10); // reduce spaceship health
            if (spaceship.getHealth() <= 0)                                           // if spaceship health is less than 0
            {
                gameState = GAMEOVER; // set game state to game over
            }
            asteroids[i] = randomAsteroid(); // reset the asteroid
        }

        float size = asteroids[i].getSize();
        if (asteroids[i].getX() > _right + size || asteroids[i].getX() < _left - size || asteroids[i].getY() < _bottom - size) // if asteroid goes out of the screen
        {
            spaceship.setScore(spaceship.getScore() + asteroids[i].getSize() / 20); // increase spaceship score
            asteroids[i] = randomAsteroid();                                        // reset the asteroid
        }
    }
}
