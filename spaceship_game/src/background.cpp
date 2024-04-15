#include "include/freeglut/include/GL/glut.h"
#include "include/constants.h"

GLfloat stars[numStars][2];

void initStars()
{
    for (int i = 0; i < numStars; i++)
    {
        // Random x and y coordinates for stars
        stars[i][0] = static_cast<float>((rand() % (_top - _bottom)) - (_top - _bottom) / 2);
        stars[i][1] = static_cast<float>((rand() % (_top - _bottom)) - (_top - _bottom) / 2);
    }
}

void drawStars()
{
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f); // White color for stars
    for (int i = 0; i < numStars; i++)
    {
        glVertex2f(stars[i][0], stars[i][1]);
    }
    glEnd();
}

void updateStars()
{
    for (int i = 0; i < numStars; i++)
    {
        stars[i][1] -= 1.0f; // Move stars down by 1 units with each frame
        if (stars[i][1] < _bottom)
        {
            stars[i][0] = static_cast<float>((rand() % (_top - _bottom)) - (_top - _bottom) / 2); // Random x-coordinate
            stars[i][1] = _top;                                                                   // Reset y-coordinate to top
        }
    }
}
