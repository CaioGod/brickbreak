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
int game_level[] = {7, 3};
GLfloat paddle_size[] = {4, 2};
int level = 0, size = 0;
float rate = game_level[level];
GLfloat paddle_color[3] = {0, 0, 1};
GLfloat text_color[4] = {1, 0, 0, 1};

int rows = 4;
int columns = 10;

//Array to store the bricks
brick_coords brick_matrix[50][50];
GLfloat v, mx, px, ball_y = -13.0, ball_x = 0, speed = 0, dirx = 0, diry = 0, auxv = 0, auxx = 0, auxy = 0, start = 0;

void draw_paddle()
{
    glColor3fv(paddle_color);
    glBegin(GL_POLYGON);
    glVertex3f(-paddle_size[size] + px, 0 - 15, 0);
    glVertex3f(paddle_size[size] + px, 0 - 15, 0);
    glVertex3f(paddle_size[size] + px, 1 - 15, 0);
    glVertex3f(-paddle_size[size] + px, 1 - 15, 0);
    glEnd();
}

void draw_single_brick(GLfloat x, GLfloat y, GLfloat z)
{
    glBegin(GL_QUADS);
    glColor3f(0, 1, size);
    glVertex3f(x, y, z);
    glColor3f(size, level, 1);
    glVertex3f(x + 3, y, z);
    glColor3f(level, 0, size);
    glVertex3f(x + 3, y + 1, z);
    glColor3f(1, level, size);
    glVertex3f(x, y + 1, z);
    glEnd();
}

void draw_bricks()
{
    int i, j;
    if (start == 0)
    {
        for (i = 1; i <= rows; i++)
        {
            for (j = 1; j <= columns; j++)
            {
                brick_matrix[i][j].y = (GLfloat)(i * 2 * 0.7);
                brick_matrix[i][j].x = (GLfloat)(j * 4 * 0.80);
            }
        }
    }

    glPushMatrix();
    glTranslatef(-19.5, 5, 0);

    for (i = 1; i <= rows; i += 1)
    {
        for (j = 1; j <= columns; j += 1)
        {

            if (brick_matrix[i][j].x == 0 || brick_matrix[i][j].y == 0)
            {
                continue;
            }
            draw_single_brick(brick_matrix[i][j].x, brick_matrix[i][j].y, 0);
        }
    }
    glPopMatrix();
}

void draw_ball()
{
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(ball_x, ball_y, 0);
    glScalef(1.0, 1.0, 0.5);
    glutSolidSphere(1.0, 30, 30);

    glPopMatrix();
}

void text(int sc)
{
    char text[40];
    if (sc == 0 && size == 0)
        sprintf(text, "Level 1 press S to start");
    else if (sc == 40)
    {
        sprintf(text, "You have won !!! Wanna try level 2?");
        size = 1;
        start = 0;
        ball_y = -12.8;
        ball_x = 0;
        dirx = 0;
        diry = 0;
        px = 0;
    }
    else if (sc == 80)
    {
        sprintf(text, "You have won !!! Wanna try level 3?");
        size = 1;
        level = 1;
        start = 0;
        ball_y = -12.8;
        ball_x = 0;
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
    glPopMatrix();
}

void mouse(int x, int y)
{
    float point[2];
    if (start == 1 && pause != 1)
    {
        mx = (x - glutGet(GLUT_WINDOW_WIDTH) / 2) / 20;
        if (mx > -0.5 && mx < 0.5)
        {
            v = 0;
        }
        else
        {
            v = mx * 0.05368;
        }
    }

    else
        glutSetCursor(GLUT_CURSOR_INHERIT);
}

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

void hotkeys(unsigned char key, int x, int y)
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
            auxv = v;
            dirx = diry = 0;
            v = 0;
        }
        else
        {
            v = auxv;
            dirx = auxx;
            diry = auxy;
        }
        pause = 1 - pause;
        break;
    case 'r':
        level = 0;
        size = 0;
        start = 0;
        ball_y = -12.8;
        ball_x = 0;
        dirx = 0;
        diry = 0;
        px = 0;
        v = 0;
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
    if (start == 0)
    {
        px = 0;
    }
    if (px < -15)
    {
        px = -15;
    }
    if (px > 15)
    {
        px = 15;
    }
    glutPostRedisplay();
}

void collision()
{
    int i, j;
    for (i = 1; i <= rows; i++)
        for (j = 1; j <= columns; j++)
        {
            if ((ball_x <= brick_matrix[i][j].x + 3 - 19.5 + 0.1) && (ball_x >= brick_matrix[i][j].x - 19.5 - 0.1))
            {
                if (ball_y <= brick_matrix[i][j].y + 5 + 1.2 + 0.1 && ball_y >= brick_matrix[i][j].y + 5 - 0.1)
                {
                    brick_matrix[i][j].y = 0;
                    brick_matrix[i][j].x = 0;
                    score++;
                    diry = diry * -1;
                }
            }
            else if (ball_y <= brick_matrix[i][j].y + 5 + 1.2 + 0.1 && ball_y >= brick_matrix[i][j].y + 5 - 0.1)
            {
                if ((ball_x <= brick_matrix[i][j].x + 3 - 19.5 + 0.1) && (ball_x >= brick_matrix[i][j].x - 19.5 - 0.1))
                {
                    brick_matrix[i][j].x = 0;
                    brick_matrix[i][j].y = 0;
                    score++;
                    dirx = dirx * -1;
                }
            }
        }
}

void game()
{
    collision();

    px += v;
    if (px < -15)
    {
        px = -15;
    }
    if (px > 15)
    {
        px = 15;
    }

    if (ball_y < -15 || (ball_y > 14 && start == 1))
    {
        diry = diry * -1;
    }
    if (ball_x < -16 || (ball_x > 16 && start == 1))
    {
        dirx = dirx * -1;
    }
    ball_x += dirx / (rate);
    ball_y += diry / (rate);
    rate -= 0.001; // Rate at which the speed of ball increases

    float x = paddle_size[size];
    //Make changes here for the different position of ball after rebounded ball_y paddle
    if (ball_y <= -12.8 && ball_x < (px + x * 2 / 3) && ball_x > (px + x / 3) && start == 1)
    {
        dirx = 1;
        diry = 1;
    }
    else if (ball_y <= -12.8 && ball_x < (px + x / 3) && ball_x > (px - x / 3) && start == 1)
    {
        dirx = dirx;
        diry = 1;
    }
    else if (ball_y <= -12.8 && ball_x < (px - x / 3) && ball_x > (px - x * 2 / 3) && start == 1)
    {
        dirx = -1;
        diry = 1;
    }
    else if (ball_y <= -12.8 && ball_x < (px + (x + 0.3)) && ball_x > (px + x / 3) && start == 1)
    {
        dirx = 1.5;
        diry = 0.8;
    }
    else if (ball_y <= -12.8 && ball_x < (px - (x * 2 / 3)) && ball_x > (px - (x + 0.3)) && start == 1)
    {
        dirx = -1.5;
        diry = 0.8;
    }
    else if (ball_y < -15)
    {
        start = 0;
        ball_y = -12.8;
        ball_x = 0;
        dirx = 0;
        diry = 0;
        px = 0;
        v = 0;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Breakout");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);
    glutIdleFunc(game);
    glutKeyboardFunc(hotkeys);
    glutPassiveMotionFunc(mouse);

    glutMainLoop();
    return 0;
}
