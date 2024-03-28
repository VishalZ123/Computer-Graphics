#include <cstdlib>
#include <math.h>
#include <GL/glut.h>

#include "headers/spaceship.h"
#include "headers/constants.h"
#include "headers/utils.h"
#include "headers/game.h"

class Asteroid
{
private:
    float x, y;          // Position
    float velocityX = 0; // Velocity in x direction
    float velocityY = 5; // Velocity in y direction
    float size;          // Size
    int sides;
    float vertices[10][2]; // Vertices of the asteroid
    void calculateVertices()
    {
        float angle = 0.0f;
        for (int i = 0; i < sides; i++)
        {
            vertices[i][0] = x + size * cos(angle);
            vertices[i][1] = y + size * sin(angle);
            angle += 2 * M_PI / sides;
        }
    }

public:
    // Constructor
    Asteroid() {}

    Asteroid(float x, float size, int sides, int speedX, int speedY)
        : x(x), size(size), sides(sides), velocityX(speedX), velocityY(speedY)
    {
        y = _top + randint(0, 300);
        calculateVertices();
    }

    Asteroid(float top, float x=0, float size = 50, int sides = 6, float speedX = 0, float speedY = 0):
        x(x), size(size), sides(sides), velocityX(speedX), velocityY(speedY)
    {   
        y = top + 100;
        calculateVertices();
    }

    // Getter functions
    float getX() const { return x; }
    float getY() const { return y; }
    float getSize() const { return size; }
    int getSides() const { return sides; }
    const float (*getVertices() const)[2] { return vertices; }

    // Setter functions
    void setPosition(float newX, float newY)
    {
        x = newX;
        y = newY;
    }
    void setX(float newX) { x = newX; }
    void setSize(float newSize) { size = newSize; }

    // Function to update asteroid position based on velocity
    void updatePosition()
    {
        y -= velocityY;
        x += velocityX;
        calculateVertices();
    }
};

Asteroid asteroids[numAsteroids];

bool didCollide(Asteroid asteroid, Spaceship spaceship)
{
    if (sqrt(pow(asteroid.getX() - spaceship.getCx(), 2) + pow(asteroid.getY() - spaceship.getCy(), 2)) <= asteroid.getSize() + spaceship.getL() / (2 * sqrt(3)))
    {
        return true;
    }
    return false;
}

Asteroid randomAsteroid()
{
    int sides = randint(6, 10);
    float x = static_cast<float>(randint(_left - 5, _right - 5));
    float size = static_cast<float>(randfloat(20.0f, 100.0f));
    float speedX = static_cast<float>(randRange(-1, 0, 0, 1));
    int speedY = randint(4, 10);
    return Asteroid(x, size, sides, speedX, speedY);
}

void initAsteroids()
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
        int angle = asteroids[i].getX()*5;
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
        if (didCollide(asteroids[i], spaceship))
        {
            spaceship.setHealth(spaceship.getHealth() - asteroids[i].getSize() / 10);
            if (spaceship.getHealth() <= 0)
            {
                gameState = GAMEOVER;
            }
            asteroids[i] = randomAsteroid();
        }

        float size = asteroids[i].getSize();
        if (asteroids[i].getX() > _right + size || asteroids[i].getX() < _left - size || asteroids[i].getY() < _bottom - size)
        {   
            spaceship.setScore(spaceship.getScore() + asteroids[i].getSize() / 20);
            if (sweepCounter < totalSweeps)
            {
                asteroids[i] = randomAsteroid();
            }else{
                asteroids[i] = Asteroid(_top + 100);
            }
        }
    }
}
