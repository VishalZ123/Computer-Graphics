#ifndef SPACESHIP_H
#define SPACESHIP_H

class Spaceship
{
private:
    GLfloat cx, cy, l, health, speed;
    GLint score;

public:
    Spaceship(GLfloat cx, GLfloat cy, GLfloat l, GLfloat health = 100.0f, GLfloat speed = 5.0f, GLint score = 0)
        : cx(cx), cy(cy), l(l), health(health), speed(speed), score(score) {}

    // Getter functions
    GLfloat getCx() const { return cx; }
    GLfloat getCy() const { return cy; }
    GLfloat getL() const { return l; }
    GLfloat getHealth() const { return health; }
    GLint getScore() const { return score; }

    // Setter functions
    void setHealth(GLfloat newHealth) { health = newHealth; }
    void setMoveSpeed(GLfloat newSpeed) { speed = newSpeed; }
    void setCy(GLfloat newCy) { cy = newCy; }
    void setCx(GLfloat newCx) { cx = newCx; }
    void setScore(GLint newScore) { score = newScore; }
};

extern Spaceship spaceship;
void drawSpaceship();
void initSpaceship();

#endif