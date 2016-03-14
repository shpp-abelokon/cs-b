/*
 *  Created by Alex Belokon on 14.03.16.
 *  Draw the fractal Sierpinski
 *  I use Glut library of utilities for OpenGL applications under
 *  I use the library descriptionI use the library description Glut
 *  https://www.opengl.org/documentation/specs/glut/spec3/spec3.html
 */
#include <GL/glut.h>

int x = 100, y = 100; // The initial coordinates of the first point

void move(int *x, int *y, int sX, int sY);

void display();


int main(int argc, char **argv) {
    glutInit(&argc, argv); // initialize glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // use one buffer type and color RGB (three components)
    glutInitWindowSize(600, 600); // sets the size of 600x600 window
    glutInitWindowPosition(300, 50); // window opening position
    glutCreateWindow("a4-fractals-Sierpinski"); // create a window with the name "a4-fractals-Sierpinski"
    glClearColor(0, 0, 0, 1.0); // window background color
    glMatrixMode(GL_PROJECTION); // it sets the matrix mode, define a matrix of projections
    glLoadIdentity(); // Clean sensor, replaces the current matrix with a single
    glOrtho(0, 600, 600, 0, -1, 1); // we define the dimensions of the grid
//    gluOrtho2D(0, 600, 0, 600); // do not get hooked up correctly :(
    glutDisplayFunc(display); // given function Sierpinski fractal
    glutMainLoop(); // we enter the main loop GLUT
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // clear buffer
    glBegin(GL_POINTS); // start drawing point

    for (int j = 0; j < 100000; ++j) {
        glColor3f(255, 255, 255); // we set the color that will "draw" - white
        glVertex2f(x, y); // draw a point at the coordinates
        int r = 1 + rand() % 600; //get a random number from 1 to 600
        /* We determine the range of the triangle apex to a random point.*/
        (r < 200) ? move(&x, &y, 0, 600) : ((r < 400) ? move(&x, &y, 600, 600) : move(&x, &y, 300, 80));
    }
    glEnd(); // Done Drawing
    glutSwapBuffers(); // exchanging buffer, displaying the whole window after it has already formed
}

/* Move the point on the middle ground between a random point and one of the vertices of the triangle */
void move(int *x, int *y, int sX, int sY) {
    *x = (*x + sX) / 2;
    *y = (*y + sY) / 2;
}