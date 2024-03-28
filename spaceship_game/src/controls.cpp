#include <math.h>
#include <GL/glut.h>
#include "headers/spaceship.h"
#include "headers/constants.h"

static bool upPressed = false;
static bool downPressed = false;
static bool leftPressed = false;
static bool rightPressed = false;

void specialKeyPressed(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        upPressed = true;
        break;
    case GLUT_KEY_DOWN:
        downPressed = true;
        break;
    case GLUT_KEY_LEFT:
        leftPressed = true;
        break;
    case GLUT_KEY_RIGHT:
        rightPressed = true;
        break;
    case 113:
        exit(0);
        break; // exit the game
    }
}

void specialKeyReleased(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        upPressed = false;
        break;
    case GLUT_KEY_DOWN:
        downPressed = false;
        break;
    case GLUT_KEY_LEFT:
        leftPressed = false;
        break;
    case GLUT_KEY_RIGHT:
        rightPressed = false;
        break;
    }
}

void moveLeft()
{
    if (spaceship.getCx() > _left + spaceship.getL() / 2)
    {
        spaceship.setCx(spaceship.getCx() - moveSpeed);
    }
}

void moveRight()
{
    if (spaceship.getCx() < _right - spaceship.getL() / 2)
    {
        spaceship.setCx(spaceship.getCx() + moveSpeed);
    }
}

void moveUp()
{
    if (spaceship.getCy() < _top - spaceship.getL() / (2 * sqrt(3)))
    {
        spaceship.setCy(spaceship.getCy() + moveSpeed);
    }
}

void moveDown()
{
    if (spaceship.getCy() > _bottom + spaceship.getL() / (2 * sqrt(3)))
    {
        spaceship.setCy(spaceship.getCy() - moveSpeed);
    }
}

void updateSpaceship()
{
    if (upPressed && leftPressed)
    {
        // Handle combination of up and left arrow keys pressed
        moveUp();
        moveLeft();
    }
    else if (upPressed && rightPressed)
    {
        // Handle combination of up and right arrow keys pressed
        moveUp();
        moveRight();
    }
    else if (downPressed && leftPressed)
    {
        // Handle combination of down and left arrow keys pressed
        moveDown();
        moveLeft();
    }
    else if (downPressed && rightPressed)
    {
        // Handle combination of down and right arrow keys pressed
        moveDown();
        moveRight();
    }
    else if (leftPressed & rightPressed)
    {
    }
    else if (upPressed & downPressed)
    {
    }
    else if (upPressed)
    {
        // Handle up arrow key pressed
        moveUp();
    }
    else if (downPressed)
    {
        // Handle down arrow key pressed
        moveDown();
    }
    else if (leftPressed)
    {
        // Handle left arrow key pressed
        moveLeft();
    }
    else if (rightPressed)
    {
        // Handle right arrow key pressed
        moveRight();
    }
}
