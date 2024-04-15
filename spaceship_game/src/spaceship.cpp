#include "include/freeglut/include/GL/glut.h"
#include <math.h>

#include "include/constants.h"
#include "include/utils.h"
#include "include/controls.h"
#include "include/spaceship.h"

Spaceship spaceship(0.0f, _bottom + 50.0f, 150.0f, 100.0f, moveSpeed, 0);
GLuint spaceship_texture;

void initSpaceship()
{
    generateTexture(&spaceship_texture, "./assets/spaceship_texture.png");
}

void drawSpaceship()
{
    // draw the spaceship
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spaceship_texture);

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.5f, 0.5f);
    glVertex2f(spaceship.getCx(), spaceship.getCy()); // Central vertex
    glTexCoord2f(0.625f, 0.1f);
    glVertex2f(spaceship.getCx() + spaceship.getL() / 8, spaceship.getCy() - spaceship.getL() / (2 * sqrt(3))); // A
    glTexCoord2f(0.6875f, 0.0f);
    glVertex2f(spaceship.getCx() + 3 * spaceship.getL() / 16, spaceship.getCy() - 0.3988 * spaceship.getL()); // B
    glTexCoord2f(1.0f, 0.1f);
    glVertex2f(spaceship.getCx() + spaceship.getL() / 2, spaceship.getCy() - spaceship.getL() / (2 * sqrt(3))); // C
    glTexCoord2f(0.5f, 1.0f);
    glVertex2f(spaceship.getCx(), spaceship.getCy() + spaceship.getL() / sqrt(3)); // D
    glTexCoord2f(0.0f, 0.1f);
    glVertex2f(spaceship.getCx() - spaceship.getL() / 2, spaceship.getCy() - spaceship.getL() / (2 * sqrt(3))); // E
    glTexCoord2f(0.3125f, 0.0f);
    glVertex2f(spaceship.getCx() - 3 * spaceship.getL() / 16, spaceship.getCy() - 0.3988 * spaceship.getL()); // F
    glTexCoord2f(0.375f, 0.1f);
    glVertex2f(spaceship.getCx() - spaceship.getL() / 8, spaceship.getCy() - spaceship.getL() / (2 * sqrt(3))); // G
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
