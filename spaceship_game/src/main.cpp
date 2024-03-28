#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include "headers/constants.h"
#include "headers/background.h"
#include "headers/spaceship.h"
#include "headers/controls.h"
#include "headers/asteroids.h"
#include "headers/spacestation.h"
#include "headers/game.h"
#include "headers/utils.h"

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (gameState == GAMEOVER)
    {
        drawGameOver();
        glutSwapBuffers();
        return;
    }
    if (gameState == GAMEWON)
    {
        drawGameOver(true);
        glutSwapBuffers();
        return;
    }
    if (gameState == PAUSE)
    {
        drawPause();
        glutSwapBuffers();
        return;
    }
    if (gameState == GAMESTART)
    {
        drawStartScreen();
        glutSwapBuffers();
        return;
    }

    drawStars();
    drawSpaceship();
    drawAsteroids();
    if (sweepCounter >= totalSweeps)
    {
        drawSpaceStation();
    }
    drawScore();
    
    glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
    drawProgressBar(200);
    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    float progress = (sweepCounter + (_top - backgroundSweep) / (2 * _top)) / totalSweeps;
    drawProgressBar(min(progress, 1.0f) * 200);

    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    drawHealthBar(300 * spaceship.getHealth() / 100.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
    drawHealthBar(300, true);

    glutSwapBuffers();
}

void handleKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q': // exit the game
        if (gameState != PLAY)
        {
            exit(0);
        }
        break;
    case 'p': // pause the game
        if (gameState == PAUSE)
        {
            gameState = PLAY;
        }
        else if (gameState == PLAY)
        {
            gameState = PAUSE;
        }
        break;
    case 'r': // restart the game
        if (gameState != PLAY && gameState != GAMESTART)
        {
            restartGame();
        }
        break;
    case 's': // start the game
        if (gameState == GAMESTART)
        {
            gameState = PLAY;
        }
        break;
    }
}

void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(_left, _right, _bottom, _top);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void update(int value)
{

    if (gameState != PLAY)
    {
        glutPostRedisplay();
        glutTimerFunc(16, update, 0);
        return;
    }
    updateStars();
    updateSpaceship();
    updateAsteroids();
    backgroundSweep -= sweepSpeed;
    if (backgroundSweep < _bottom && sweepCounter < totalSweeps)
    {
        sweepCounter++;
        backgroundSweep = _top;
    }

    if (sweepCounter >= totalSweeps)
    {
        pollSpaceStation();
    };

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char **argv)
{
    srand(time(nullptr));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Spaceship Game");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(specialKeyPressed);
    glutSpecialUpFunc(specialKeyReleased);

    initStars();
    initAsteroids();
    initSpaceStation();
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
