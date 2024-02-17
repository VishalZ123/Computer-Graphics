#include <GL/glut.h>
#include <stdlib.h>

float angleX = 0.0f;
float angleY = 0.0f;
int lastMouseX;
int lastMouseY;
bool mouseDown = false;

static float z = -30.0;

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

void drawDecagonalPrism() {
    // Define vertices of the dodecahedron
    GLfloat vertices[22][3] = {
        {2.0, -6.155, 0.0},
        {5.236, -3.804, 0.0},
        {2.0, -6.155, 4.0},
        {5.236, -3.804, 4.0},
        {6.472, 0.0, 0.0},
        {6.472, 0.0, 4.0},
        {5.236, 3.804, 0.0},
        {5.236, 3.804, 4.0},
        {2.0, 6.155, 0.0},
        {2.0, 6.155, 4.0},
        {-2.0, 6.155, 0.0},
        {-2.0, 6.155, 4.0},
        {-5.236, 3.804, 0.0},
        {-5.236, 3.804, 4.0},
        {-6.472, 0.0, 0.0},
        {-6.472, 0.0, 4.0},
        {-5.236, -3.804, 0.0},
        {-5.236, -3.804, 4.0},
        {-2.0, -6.155, 0.0},
        {-2.0, -6.155, 4.0},
        {0.0, -6.155, 0.0},
        {0.0, -6.155, 4.0}
    };

    // Define faces of the dodecahedron
    GLuint faces[40][3] = {
        { 0,  1,  2},
        { 2,  1,  3},
        { 1,  4,  3},
        { 3,  4,  5},
        { 4,  6,  5},
        { 5,  6,  7},
        { 6,  8,  7},
        { 7,  8,  9},
        { 8, 10,  9},
        { 9, 10, 11},
        {10, 12, 11},
        {11, 12, 13},
        {12, 14, 13},
        {13, 14, 15},
        {14, 16, 15},
        {15, 16, 17},
        {16, 18, 17},
        {17, 18, 19},
        {18, 20, 19},
        {19, 20, 21},
        {21, 20,  2},
        {20,  0,  2},
        {14, 20, 16},
        {16, 20, 18},
        {14, 12, 20},
        {20,  1,  0},
        {12, 10, 20},
        {20,  4,  1},
        {10,  8, 20},
        {20,  6,  4},
        { 8,  6, 20},
        {21, 15, 17},
        {21, 17, 19},
        {13, 15, 21},
        { 3, 21,  2},
        {11, 13, 21},
        { 5, 21,  3},
        { 9, 11, 21},
        { 7, 21,  5},
        { 7,  9, 21}
        };

    // Define colors for each external vertex
    GLfloat colors[22][3] = {
       {0.629, 0.078, 0.77 },
       {0.924, 0.7  , 0.084},
       {0.253, 0.822, 0.924},
       {0.616, 0.139, 0.854},
       {0.327, 0.997, 0.591},
       {0.473, 0.65 , 0.639},
       {0.279, 0.132, 0.335},
       {0.682, 0.761, 0.838},
       {0.047, 0.593, 0.545},
       {0.347, 0.919, 0.566},
       {0.335, 0.676, 0.845},
       {0.178, 0.107, 0.636},
       {0.31 , 0.991, 0.077},
       {0.244, 0.388, 0.328},
       {0.633, 0.632, 0.527},
       {0.55 , 0.742, 0.541},
       {0.853, 0.184, 0.363},
       {0.464, 0.076, 0.895},
       {0.366, 0.856, 0.296},
       {0.543, 0.25 , 0.812},
       {0.56 , 0.135, 0.778},
       {0.278, 0.825, 0.16 }};

    // Draw the dodecahedron
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 40; i++) {
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
    drawDecagonalPrism();

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
        if (state == GLUT_DOWN) {
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
