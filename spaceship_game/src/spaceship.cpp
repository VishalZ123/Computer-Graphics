#include <GL/glut.h>
#include <math.h>
#include "headers/constants.h"
#include "headers/utils.h"

class Spaceship
{
private:
    float cx, cy, l, health, speed;
    int score;

public:
    Spaceship(float cx, float cy, float l, float health = 100.0f, float speed = 5.0f, int score = 0)
        : cx(cx), cy(cy), l(l), health(health), speed(speed), score(score) {}

    float getCx() const { return cx; }
    float getCy() const { return cy; }
    float getL() const { return l; }
    float getHealth() const { return health; }
    int getScore() const { return score; }

    void setHealth(float newHealth) { health = newHealth; }
    void setMoveSpeed(float newSpeed) { speed = newSpeed; }
    void setCy(float newCy) { cy = newCy; }
    void setCx(float newCx) { cx = newCx; }
    void setScore(int newScore) { score = newScore; }
};

Spaceship spaceship(0.0f, _bottom + 50.0f, 100.0f, 100.0f, moveSpeed, 0);

void drawSpaceship()
{   
    glVertex2f(spaceship.getCx(), spaceship.getCy() + spaceship.getL() / sqrt(3));
    glVertex2f(spaceship.getCx() - spaceship.getL() / 2, spaceship.getCy() - spaceship.getL() / (2 * sqrt(3)));
    glVertex2f(spaceship.getCx() + spaceship.getL() / 2, spaceship.getCy() - spaceship.getL() / (2 * sqrt(3)));
    glEnd();
}
