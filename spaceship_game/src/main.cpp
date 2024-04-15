#include "include/freeglut/include/GL/glut.h"
#include <cstdlib>
#include <ctime>

#include "include/constants.h"
#include "include/background.h"
#include "include/spaceship.h"
#include "include/controls.h"
#include "include/asteroids.h"
#include "include/spacestation.h"
#include "include/minimap.h"
#include "include/game.h"
#include "include/utils.h"

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (gameState == GAMEOVER)
    {
        drawGameOver(); // Draw game over screen
        glutSwapBuffers();
        return;
    }
    if (gameState == GAMEWON)
    {
        drawGameOver(true); // Draw game won screen
        glutSwapBuffers();
        return;
    }
    if (gameState == PAUSE)
    {
        drawPause(); // Draw pause screen
        glutSwapBuffers();
        return;
    }
    if (gameState == GAMESTART)
    {
        drawStartScreen(); // Draw start screen
        glutSwapBuffers();
        return;
    }

    // draw different components
    drawStars();
    drawAsteroids();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    if (sweepCounter >= totalSweeps)
    {
        drawSpaceStation();
    }
    drawSpaceship();
    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    drawMiniMap();
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
    gluOrtho2D(_left, _right, _bottom, _top); // Orthographic projection
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

    // update different components
    updateStars();
    updateSpaceship();
    updateAsteroids();

    // track the progress of the game
    backgroundSweep -= sweepSpeed;
    if (backgroundSweep < _bottom && sweepCounter < totalSweeps)
    {
        sweepCounter++;
        backgroundSweep = _top;
    }

    // check if the spaceship has reached the space station
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
    glutCreateWindow("Space Odyssey");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black background

    // initiate different components
    initStars();
    initMinimap();
    initSpaceship();
    initAsteroids();
    initSpaceStation();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(specialKeyPressed);
    glutSpecialUpFunc(specialKeyReleased);

    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
