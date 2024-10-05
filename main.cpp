#include <windows.h>
#include <cmath>
#include <GL/glut.h>
#include <stdlib.h>

float carX = -100.0f; // Initial x-position of the car
float carSpeed = 0.5f; // Increased speed for faster movement

void drawCar() {
    // Draw the car body
    glColor3f(0.0f, 0.0f, 1.0f); // Blue car body
    glBegin(GL_POLYGON);
    glVertex2f(carX - 15, -20);
    glVertex2f(carX + 15, -20);
    glVertex2f(carX + 15, -10);
    glVertex2f(carX - 15, -10);
    glEnd();

    // Draw the car roof
    glColor3f(0.0f, 0.5f, 1.0f); // Lighter blue for roof
    glBegin(GL_POLYGON);
    glVertex2f(carX - 10, -10);
    glVertex2f(carX + 10, -10);
    glVertex2f(carX + 5, -5);
    glVertex2f(carX - 5, -5);
    glEnd();

    // Draw the wheels
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for wheels
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float theta = (2.0f * 3.14159f * float(i)) / 100.0f;
        float x = 3 * cos(theta);
        float y = 3 * sin(theta);
        glVertex2f(carX - 10 + x, -22 + y); // Left wheel
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float theta = (2.0f * 3.14159f * float(i)) / 100.0f;
        float x = 3 * cos(theta);
        float y = 3 * sin(theta);
        glVertex2f(carX + 10 + x, -22 + y); // Right wheel
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw ground
    glColor3f(0.0f, 1.0f, 0.0f); // Green ground
    glBegin(GL_POLYGON);
    glVertex2f(-100, -25);
    glVertex2f(100, -25);
    glVertex2f(100, -100);
    glVertex2f(-100, -100);
    glEnd();

    drawCar();

    glFlush();
    glutSwapBuffers();
}

void update(int value) {
    // Move the car
    carX += carSpeed;

    // Reset car position when it moves off-screen
    if (carX > 100.0f) {
        carX = -100.0f;
    }

    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(16, update, 0); // Call update again after 16 ms (~60 FPS)
}

void init() {
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f); // Light blue sky
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Moving Car Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0); // Start the timer for animation
    glutMainLoop();
    return 0;
}
