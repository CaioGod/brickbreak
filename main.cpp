#include <stdlib.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Structure to store the coordinates of each brick
struct brick_coords
{
    GLfloat x;
    GLfloat y;
};

int score = 0;
int pause = 0;
GLfloat twoModel[] = {GL_TRUE};
int brick_color = 0, level = 0, size = 0;
int game_level[] = {7, 3};
GLfloat paddle_size[] = {4, 2};
float rate = game_level[level];

//red, geen, blue
GLfloat brick_color_array[][3] = {{0, 1, 1}, {0, 1, 0}, {1, 0, 0}};
GLfloat paddle_color[3] = {0, 0, 1};
GLfloat text_color[4] = {1, 0, 0, 1};

//The grid parameters for the bricks
int rows = 4;
int columns = 10;

//Array to store the bricks
brick_coords brick_array[50][50];
GLfloat px, bx = 0, by = -12.8, speed = 0, dirx = 0, diry = 0, auxx = 0, auxy = 0, start = 0;

// Function to draw the paddle
void draw_paddle()
{
    glDisable(GL_LIGHTING);
    glColor3fv(paddle_color);
    glBegin(GL_POLYGON);
    glVertex3f(-paddle_size[size] + px, 0 - 15, 0);
    glVertex3f(paddle_size[size] + px, 0 - 15, 0);
    glVertex3f(paddle_size[size] + px, 1 - 15, 0);
    glVertex3f(-paddle_size[size] + px, 1 - 15, 0);
    glEnd();
    glEnable(GL_LIGHTING);
}

//Function to draw a single brick
void brick(GLfloat x, GLfloat y, GLfloat z)
{
    glDisable(GL_LIGHTING);
    glColor3fv(brick_color_array[brick_color]);
    glBegin(GL_QUADS);
    glVertex3f(x, y, z);
    glVertex3f(x + 3, y, z);
    glVertex3f(x + 3, y + 1, z);
    glVertex3f(x, y + 1, z);
    glEnd();
    glEnable(GL_LIGHTING);
}

// Function to draw the grid of bricks
void draw_bricks()
{
    int i, j;
    if (start == 0)
    {
        for (i = 1; i <= rows; i++)
        {
            for (j = 1; j <= columns; j++)
            {
                brick_array[i][j].x = (GLfloat)(j * 4 * 0.78);
                brick_array[i][j].y = (GLfloat)(i * 2 * 0.6);
            }
        }
    }

    glPushMatrix();
    glTranslatef(-19.5, 5, 0);

    for (i = 1; i <= rows; i += 1)
    {
        for (j = 1; j <= columns; j += 1)
        {

            if (brick_array[i][j].x == 0 || brick_array[i][j].y == 0)
            {
                continue;
            }
            brick(brick_array[i][j].x, brick_array[i][j].y, 0);
        }
    }
    glPopMatrix();
}

//Function to draw the spherical ball
void draw_ball()
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(bx, by, 0);
    glScalef(1.0, 1.0, 0.5);
    glutSolidSphere(1.0, 30, 30);

    glPopMatrix();
}

//mouse function
void mousemotion(int x, int y)
{

    if (start == 1 && pause != 1)
    {
        px = (x - glutGet(GLUT_WINDOW_WIDTH) / 2) / 20;
        if (px > 15)
        {
            px = 15;
        }
        if (px < -15)
        {
            px = -15;
        }
    }

    else
        glutSetCursor(GLUT_CURSOR_INHERIT);
}

//Function to print the score on the screen
void text(int sc)
{
    glDisable(GL_LIGHTING);
    char text[40];
    if (sc == 0 && size == 0)
        sprintf(text, "Level 1");
    else if (sc == 40)
    {
        sprintf(text, "You have won !!! Wanna try level 2?");
        brick_color = 1;
        size = 1;
        start = 0;
        by = -12.8;
        bx = 0;
        dirx = 0;
        diry = 0;
        px = 0;
    }
    else if (sc == 80)
    {
        sprintf(text, "You have won !!! Wanna try level 3?");
        brick_color = 2;
        size = 1;
        level = 1;
        start = 0;
        by = -12.8;
        bx = 0;
        dirx = 0;
        diry = 0;
        px = 0;
    }
    else
    {
        sprintf(text, "Your Score: %d", sc);
    }
    // The color
    glColor4fv(text_color);
    // Position of the text to be printer
    glPushMatrix();
    glTranslatef(-1, 0, 0);
    glRasterPos3f(0, 0, 15);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

//The main display function
void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 0, 0, 0, -25, 0, 1, 0);
    glTranslatef(0, 0, -25);
    draw_paddle();
    draw_bricks();
    draw_ball();
    text(score);
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

//function to take in keyboard entries
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
        px += 3;
        break;
    case 'a':
        px -= 3;
        break;
    case 'q':
        exit(0);
        break;
    case 'w':
        if (!pause)
        {
            auxx = dirx;
            auxy = diry;
            dirx = diry = 0;
        }
        else
        {
            dirx = auxx;
            diry = auxy;
        }
        pause = 1 - pause;
        break;
    case 'r':
        level = 0;
        size = 0;
        brick_color = 0;
        start = 0;
        by = -12.8;
        bx = 0;
        dirx = 0;
        diry = 0;
        px = 0;
        break;
    case 's':
        if (!start)
        {
            dirx = diry = 1;
            rate = game_level[level];
            start = 1;
            score = 0;
        }
        break;
    }
    if (px > 15)
    {
        px = 15;
    }
    if (px < -15)
    {
        px = -15;
    }
    if (start == 0)
    {
        px = 0;
    }
    glutPostRedisplay();
}

//Function to handle the case when the ball strikes the bricks
void hit()
{
    int i, j;
    for (i = 1; i <= rows; i++)
        for (j = 1; j <= columns; j++)
        {
            if ((bx >= brick_array[i][j].x - 19.5 - 0.1) && (bx <= brick_array[i][j].x + 3 - 19.5 + 0.1))
            {
                if (by >= brick_array[i][j].y + 5 - 0.1 && by <= brick_array[i][j].y + 5 + 1.2 + 0.1)
                {
                    brick_array[i][j].x = 0;
                    brick_array[i][j].y = 0;
                    diry = diry * -1;

                    score++;
                }
            }
            else if (by >= brick_array[i][j].y + 5 - 0.1 && by <= brick_array[i][j].y + 5 + 1.2 + 0.1)
            {
                if ((bx >= brick_array[i][j].x - 19.5 - 0.1) && (bx <= brick_array[i][j].x + 3 - 19.5 + 0.1))
                {
                    brick_array[i][j].x = 0;
                    brick_array[i][j].y = 0;
                    dirx = dirx * -1;
                    score++;
                }
            }
        }
}

//The idle function. Handles the motion of the ball along with rebounding from various surfaces
void idle()
{
    hit();
    if (bx < -16 || (bx > 16 && start == 1))
    {
        dirx = dirx * -1;
    }
    if (by < -15 || (by > 14 && start == 1))
    {
        diry = diry * -1;
    }
    bx += dirx / (rate);
    by += diry / (rate);
    rate -= 0.001; // Rate at which the speed of ball increases

    float x = paddle_size[size];
    //Make changes here for the different position of ball after rebounded by paddle
    if (by <= -12.8 && bx < (px + x * 2 / 3) && bx > (px + x / 3) && start == 1)
    {
        dirx = 1;
        diry = 1;
    }
    else if (by <= -12.8 && bx < (px - x / 3) && bx > (px - x * 2 / 3) && start == 1)
    {
        dirx = -1;
        diry = 1;
    }
    else if (by <= -12.8 && bx < (px + x / 3) && bx > (px - x / 3) && start == 1)
    {
        dirx = dirx;
        diry = 1;
    }
    else if (by <= -12.8 && bx < (px - (x * 2 / 3)) && bx > (px - (x + 0.3)) && start == 1)
    {
        dirx = -1.5;
        diry = 0.8;
    }
    else if (by <= -12.8 && bx < (px + (x + 0.3)) && bx > (px + x / 3) && start == 1)
    {
        dirx = 1.5;
        diry = 0.8;
    }
    else if (by < -13)
    {
        start = 0;
        by = -12.8;
        bx = 0;
        dirx = 0;
        diry = 0;
        px = 0;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Brickbreaker");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(mousemotion);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
