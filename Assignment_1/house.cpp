#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static float z = -10.0;
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

void drawQuadilateral(float vertices[4][3], float color[3], float z_offset = 0, float x_offset=0, float y_offset = 0)
{
    glBegin(GL_QUADS);
    glColor3f(color[0],color[1],color[2]);
    for (int i = 0; i < 4; i++) {
        glVertex3f(vertices[i][0] + x_offset, vertices[i][1] + y_offset, vertices[i][2] + z_offset);
    }
    glEnd();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,1);
    glBegin(GL_TRIANGLES);
        glColor3f(0.498, 0.2, 0);
        glVertex3f(-1, 2, z);
        glVertex3f(-2, 3.732, z);
        glVertex3f(-3, 2, z);
    glEnd();

    // roof
    float roof[4][3] = {{2,2,z},{1,3.732,z},{-2, 3.732,z},{-1, 2, z}};
    float roofColor[3] = {0.298, 0.502, 0.8};
    drawQuadilateral(roof, roofColor);

    // front
    float front[4][3] = {{-1, 0, z},{-1, 2, z},{-3, 2, z},{-3, 0, z}};
    float frontColor[3] = {0.035, 0.098, 0.2};
    drawQuadilateral(front, frontColor);

    // side
    float side[4][3] = {{2, 0, z},{2, 2, z},{-1, 2, z},{-1, 0, z}};
    float sideColor[3] = {0.098, 0.2, 0.298};
    drawQuadilateral(side, sideColor);

    // door
    float door[4][3] = {{-1.5, 0, z},{-1.5, 1.25, z},{-2.5,1.25, z},{-2.5, 0, z}};
    float doorColor[3] = {0.498, 0.2, 0};
    drawQuadilateral(door, doorColor, 0.01);


    // door knob
    float doorKnob[4][3] = {{-2.25, 0.5, z},{-2.25, 0.65, z},{-2.4, 0.65, z},{-2.4, 0.5, z}};
    float doorKnobColor[3] = {0.325, 0.674, 0.878};
    drawQuadilateral(doorKnob, doorKnobColor, 0.02);

    // window
    float pane[4][3] = {{-0.2, 1.3, z+0.01},{-0.2,1.7,z+0.01},{-0.7, 1.7,z+0.01},{-0.7, 1.3, z+0.01}};
    float paneColor[3] = {0.8, 0.8, 0.109};
    drawQuadilateral(pane, paneColor);
    drawQuadilateral(pane, paneColor, 0, 0.525);
    drawQuadilateral(pane, paneColor, 0, 0,-0.45);
    drawQuadilateral(pane, paneColor, 0, 0.525, -0.45);
    drawQuadilateral(pane, paneColor, 0, 1.25);
    drawQuadilateral(pane, paneColor, 0, 1.775);
    drawQuadilateral(pane, paneColor, 0, 1.25, -0.45);
    drawQuadilateral(pane, paneColor, 0, 1.775, -0.45);

    float road[4][3] = {{-2.5, 0, z},{-3.125, -1, z},{-1.763, -1, z},{-1.5, 0, z}};
    drawQuadilateral(road, roofColor);

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

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
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

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0.498,0.898,0.4, 1);
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
