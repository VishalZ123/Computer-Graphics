#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

float angleX = 0.0f;
float angleY = 0.0f;
int lastMouseX;
int lastMouseY;
bool mouseDown = false;
static float z = -6.0;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void drawDodecahedron() {
    // Define vertices of the dodecahedron
    GLfloat vertices[20][3] = {
        { 0.5, -1.30901694, 0.0 },
        { 0.809017, -0.809017, 0.809017 },
        { -0.5, -1.30901694, 0.0 },
        { 0.0, -0.5, 1.30901694 },
        { -0.809017, -0.809017, 0.809017 },
        { -0.809017, -0.809017, -0.809017 },
        { 0.0, -0.5, -1.30901694 },
        { 0.809017, -0.809017, -0.809017 },
        { 1.30901694, 0.0, -0.5 },
        { 1.30901694, 0.0, 0.5 },
        { 0.0, 0.5, -1.30901694 },
        { 0.809017, 0.809017, -0.809017 },
        { 0.0, 0.5, 1.30901694 },
        { 0.809017, 0.809017, 0.809017 },
        { -0.5, 1.30901694, 0.0 },
        { 0.5, 1.30901694, 0.0 },
        { -0.809017, 0.809017, -0.809017 },
        { -1.30901694, 0.0, -0.5 },
        { -1.30901694, 0.0, 0.5 },
        { -0.809017, 0.809017, 0.809017 }
    };

    // Define faces of the dodecahedron
    GLuint faces[36][3] = {
        {0, 1, 2},
        {1, 3, 2},
        {3, 4, 2},
        {2, 5, 6},
        {6, 7, 0},
        {0, 2, 6},
        {7, 8, 0},
        {8, 9, 0},
        {9, 1, 0},
        {8, 7, 6},
        {6, 10, 8},
        {10, 11, 8},
        {12, 3, 1},
        {1, 9, 12},
        {9, 13, 12},
        {14, 15, 11},
        {11, 10, 14},
        {10, 16, 14},
        {17, 18, 14},
        {17, 14, 16},
        {18, 19, 14},
        {10, 6, 5},
        {5, 17, 10},
        {17, 16, 10},
        {2, 4, 18},
        {18, 17, 5},
        {5, 2, 18},
        {11, 15, 9},
        {11, 9, 8},
        {15, 13, 9},
        {12, 13, 15},
        {15, 14, 12},
        {14, 19, 12},
        {18, 4, 3},
        {3, 12, 18},
        {12, 19, 18}
    };

    // Define colors for each external vertex
    GLfloat colors[20][3] = {
    {0.258, 0.701, 0.394},
    {0.573, 0.123, 0.866},
    {0.945, 0.586, 0.021},
    {0.342, 0.456, 0.912},
    {0.723, 0.098, 0.521},
    {0.812, 0.294, 0.723},
    {0.165, 0.891, 0.634},
    {0.425, 0.743, 0.102},
    {0.633, 0.278, 0.942},
    {0.874, 0.665, 0.381},
    {0.205, 0.531, 0.793},
    {0.981, 0.412, 0.218},
    {0.498, 0.815, 0.701},
    {0.732, 0.159, 0.483},
    {0.357, 0.624, 0.876},
    {0.632, 0.845, 0.219},
    {0.126, 0.392, 0.761},
    {0.941, 0.267, 0.573},
    {0.583, 0.921, 0.341},
    {0.309, 0.781, 0.921}
    };

    // Draw the dodecahedron
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 3; j++) {
            glColor3fv(colors[faces[i][j]]);
            glVertex3fv(vertices[faces[i][j]]);
        }
    }
    glEnd();
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, z);
    glRotatef(angleX, 0.0f, 1.0f, 0.0f);
    glRotatef(angleY, 1.0f, 0.0f, 0.0f);
    drawDodecahedron();

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case '+':
            if(z<=-2){
                z+=0.5;
            }
            break;
        case '-':
            if (z>=-99)
            {
                z-=0.5;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN){
            mouseDown = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            mouseDown = false;
        }
    }
}

void motion(int x, int y) {
    if (mouseDown) {
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;
        angleX += deltaX*0.5;
        angleY += deltaY*0.5;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 0.5f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Regular Dodecahedron");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);

    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
