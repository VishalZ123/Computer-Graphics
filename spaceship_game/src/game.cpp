#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <string>
using namespace std;
#include "headers/spaceship.h"
#include "headers/constants.h"
#include "headers/asteroids.h"
#include "headers/spacestation.h"
#include "headers/background.h"

GLint sweepCounter = 0;
GLfloat backgroundSweep = _top;
int gameState = GAMESTART;

void glutBitmapString(void *font, const unsigned char *string)
{
    while (*string)
    {
        glutBitmapCharacter(font, *string++);
    }
}

void drawGameOver(bool won = false)
{
    glClearColor(0.078f, 0.078f, 0.078f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (won)
    {
        glColor3f(0.0f, 1.0f, 0.0f);
    }
    else
    {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    glRasterPos2f(0.30 * _left, 0.25 * _top);
    const unsigned char *message = won ? (const unsigned char *)"You Won" : (const unsigned char *)"Game Over";
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, message);
    glRasterPos2f(0.30 * _left, 0.25 * _top - 50.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Press 'r' to restart");
    glRasterPos2f(0.30 * _left, 0.25 * _top - 100.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Press 'q' to quit");
    
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "Score: %d", spaceship.getScore());
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(0.30 * _left, 0.25 * _top - 250.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)buffer);

}

void drawPause()
{
    glClearColor(0.078f, 0.078f, 0.078f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(0.25 * _left, 0.25 * _top);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Game Paused");
    glRasterPos2f(0.25 * _left, 0.25 * _top - 50.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Press 'p' to resume");
    glRasterPos2f(0.25 * _left, 0.25 * _top - 100.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Press 'q' to quit");
}

void drawStartScreen()
{
    glClearColor(0.078f, 0.078f, 0.078f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(0.4 * _left, 0.75 * _top);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Welcome to Space Odyssey");

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(0.45 * _left, 0.75 * _top - 60.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Press 's' to start, Press 'q' to quit");

    glColor3f(1.0f, 0.0f, 1.0f);
    glRasterPos2f(0.2 * _left, 0.75 * _top - 180.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Instructions");

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(0.55 * _left, 0.75 * _top - 240.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Use arrow keys to move the spaceship");

    glRasterPos2f(0.25 * _left, 0.75 * _top - 300.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Avoid asteroids!");

    glRasterPos2f(0.55 * _left, 0.75 * _top - 360.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Bigger asteroids cause more damage.");

    glRasterPos2f(0.35 * _left, 0.75 * _top - 420.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"Reach the space station!");
}

void restartGame()
{
    gameState = PLAY;
    sweepCounter = 0;
    backgroundSweep = _top;
    spaceship.setHealth(100.0f);
    spaceship.setScore(0);
    spaceship.setCy(_bottom + 50.0f);
    initStars();
    initAsteroids();
    spaceship.setHealth(100.0f);
    glutPostRedisplay();
}

void drawProgressBar(float height)
{
    float angle;
    float width = 20.0f;
    float radius = width / 2;
    float offset = 50.0f;
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 30; i++)
    {
        angle = -i * M_PI / 30;
        glVertex2f(_right - offset - width / 2 + radius * cos(angle), height - radius * sin(angle));
    }
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(_right - offset, height);
    glVertex2f(_right - offset - width, height);
    glVertex2f(_right - offset - width, 0.0f);
    glVertex2f(_right - offset, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i <= 30; i++)
    {
        angle = -i * M_PI / 30;
        glVertex2f(_right - offset - width / 2 + radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

void drawHealthBar(float width, bool container = false)
{
    float angle;
    float height = 20.0f;
    float radius = height / 2;
    float offset = 50.0f;

    glBegin(GL_POLYGON);
    for (int i = 0; i <= 30; i++)
    {
        angle = i * M_PI / 30 + M_PI / 2;
        glVertex2f(_left + offset + radius * cos(angle), _top - offset - height / 2 - radius * sin(angle));
    }
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(_left + offset, _top - offset);
    glVertex2f(_left + offset, _top - offset - height);
    glVertex2f(_left + offset + width, _top - offset - height);
    glVertex2f(_left + offset + width, _top - offset);
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i <= 30; i++)
    {
        angle = -i * M_PI / 30 + M_PI / 2;
        glVertex2f(_left + offset + width + radius * cos(angle), _top - offset - height / 2 + radius * sin(angle));
    }
    glEnd();
    if (container)
    {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "%.0f", spaceship.getHealth());
        strcat(buffer, "/100");
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glRasterPos2f(_left + offset + width + 20.0f, _top - offset - height / 2 - 5.0f);
        glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char *)buffer);
    }
}

void drawScore()
{
    char score[20];
    snprintf(score, sizeof(score), "Score: %d", spaceship.getScore());
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos2f(_right - 200.0f, _top - 50.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)score);
}
