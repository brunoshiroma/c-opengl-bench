#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <string.h>

int width = 0, height = 0, x = 0, y = 0, fps = 0, lastFPS = 0;
struct timespec last;

void *font = GLUT_STROKE_ROMAN;

void output(GLfloat x, GLfloat y, char *string)
{
    glColor3d(1, 1, 1);
    glLineWidth(2);
    glPushMatrix();
    glTranslatef(x, y + 120, 0);
    glScalef(1, -1, 1);
    for (char *p = string; *p; p++)
    {
        glutStrokeCharacter(font, *p);
    }

    glPopMatrix();
}

void reshape(int w, int h)
{
    /* Because Gil specified "screen coordinates" (presumably with an
     upper-left origin), this short bit of code sets up the coordinate
     system to correspond to actual window coodrinates.  This code
     wouldn't be required if you chose a (more typical in 3D) abstract
     coordinate system. */

    width = w;
    height = h;

    glViewport(0, 0, w, h);      /* Establish viewing area to cover entire window. */
    glMatrixMode(GL_PROJECTION); /* Start modifying the projection matrix. */
    glLoadIdentity();            /* Reset project matrix. */
    glOrtho(0, w, 0, h, -1, 1);  /* Map abstract coords directly to window coords. */
    glScalef(1, -1, 1);          /* Invert Y axis so increasing Y goes down. */
    glTranslatef(0, -h, 0);      /* Shift origin up to upper-left corner. */
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); /* blue */
    glVertex2i(width, 0);
    glColor3f(0.0, 1.0, 0.0); /* green */
    glVertex2i(200, 200);
    glColor3f(1.0, 0.0, 0.0); /* red */
    glVertex2i(x, y);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); /* blue */
    glVertex2i(0, 0);
    glColor3f(0.0, 1.0, 0.0); /* green */
    glVertex2i(200, 200);
    glColor3f(1.0, 0.0, 0.0); /* red */
    glVertex2i(x, y);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); /* blue */
    glVertex2i(width, height);
    glColor3f(0.0, 1.0, 0.0); /* green */
    glVertex2i(200, 200);
    glColor3f(1.0, 0.0, 0.0); /* red */
    glVertex2i(x, y);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); /* blue */
    glVertex2i(0, height);
    glColor3f(0.0, 1.0, 0.0); /* green */
    glVertex2i(200, 200);
    glColor3f(1.0, 0.0, 0.0); /* red */
    glVertex2i(x, y);
    glEnd();

    if (x < width)
    {
        x++;
    }
    else
    {
        x = 0;
    }

    if (y < height)
    {
        y++;
    }
    else
    {
        y = 0;
    }

    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    if (spec.tv_sec > last.tv_sec)
    {

        char fpsMsg[120];
        sprintf(fpsMsg, "FPS %d", fps);

        printf("%s\n", fpsMsg);
        last = spec;
        lastFPS = fps;
        fps = 0;
    }

    fps++;

    char fpsMsg[120];
    sprintf(fpsMsg, "FPS %d", lastFPS);
    output(0, 0, fpsMsg);

    glFlush();
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    clock_gettime(CLOCK_REALTIME, &last);
    printf("INIT...\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("BENCH OPENGL");

    //GL context only exists after creation of window
    const GLubyte *vendor = glGetString(GL_VENDOR);     // Returns the vendor
    const GLubyte *renderer = glGetString(GL_RENDERER); // Returns a hint to the model
    const GLubyte *glVersion = glGetString(GL_VERSION); // Returns a hint to the model

    printf("%s %s %s\n", vendor, renderer, glVersion);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}