#include <GL/glut.h>
#include <cmath>




void drawCircle(float cx, float cy, float radius, int numSegments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);

        float x = radius * cosf(theta);
        float y = radius * sinf(theta);

        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}



void drawChick() {

    // ��
    glColor3f(1.0, 1.0, 0.5); // ������� ��
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        float x = 0.12 * cos(angle);
        float y = 0.2 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();


    // �� ���׶�� (����)
    glColor3f(0.529, 0.808, 0.922);
    glPushMatrix();
    glTranslatef(-0.04, 0.14, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        float x = 0.02 * cos(angle);
        float y = 0.03 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // �� (����)
    glColor3f(1.0, 1.0, 1.0); // ���
    drawCircle(-0.04, 0.16, 0.008, 480);

    // �� ���׶�� (������)
    glColor3f(0.529, 0.808, 0.922);
    glPushMatrix();
    glTranslatef(0.04, 0.14, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        float x = 0.02 * cos(angle);
        float y = 0.03 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // �� (������)
    glColor3f(1.0, 1.0, 1.0); // ���
    drawCircle(0.04, 0.16, 0.008, 480); // �׹��� ���� ���� ���� , ����°�� ũ��


    // �θ�
    glColor3f(1.0, 0.5, 0.0); // ��Ȳ��
    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.02, 0.0);
    glVertex2f(-0.02, 0.0);
    glVertex2f(0.0, -0.05);
    glEnd();
    glPopMatrix();



    // ���� (����)
    glColor3f(1.0, 1.0, 0.5); // ������� ����
    glBegin(GL_POLYGON);
    glVertex2f(-0.15, 0.02); // ������ �κ� (���θ� Ű��)
    glVertex2f(-0.1, 0.09); // ������ �κ� (ũ�⸦ ũ�� ��)
    glVertex2f(-0.05, 0.02); // ������ �κ� (���θ� Ű��)
    glEnd();


    // ���� (������)
    glColor3f(1.0, 1.0, 0.5); // ������� ����
    glBegin(GL_POLYGON);
    glVertex2f(0.15, 0.02); // ������ �κ� (���θ� Ű��)
    glVertex2f(0.1, 0.09); // ������ �κ� (ũ�⸦ ũ�� ��)
    glVertex2f(0.05, 0.02); // ������ �κ� (���θ� Ű��)
    glEnd();
}


void reshape(int NewWidth, int NewHeight) {
    glViewport(0, 0, NewWidth, NewHeight);
    GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)1280;
    GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)720;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.2 * WidthFactor, 0.2 * WidthFactor, -0.3 * HeightFactor, 0.3 * HeightFactor);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawChick();
    glutSwapBuffers();
    glFlush();
}

int main(int argc, char** argv) {
    glutInitWindowSize(1280, 720);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("OpenGL Chick");


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}