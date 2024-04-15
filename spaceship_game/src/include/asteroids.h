#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "utils.h"
#include <math.h>

class Asteroid
{
private:
    float x, y;          // Position
    float velocityX = 0; // Velocity in x direction
    float velocityY = 5; // Velocity in y direction
    float size;          // Size
    int sides;
    float vertices[10][2];   // Vertices of the asteroid
    void calculateVertices() // n sides polygon
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
        y = _top + randint(0, 300); // start from top of the screen
        calculateVertices();
    }

    Asteroid(float top, float x = 0, float size = 50, int sides = 6, float speedX = 0, float speedY = 0) : x(x), size(size), sides(sides), velocityX(speedX), velocityY(speedY)
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

extern Asteroid asteroids[];
void initAsteroids();
void drawAsteroids();
void updateAsteroids();

#endif