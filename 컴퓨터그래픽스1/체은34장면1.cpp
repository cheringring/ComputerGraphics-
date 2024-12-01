#include <GL/glut.h>
#include <cmath>
#include <ctime>




// ������ ������ ��� ����ü
struct Cloud {
    float x, y; // ������ ���� ��ġ
    float speed; // ������ �̵� �ӵ�
};


struct Egg {
    float x, y; // ���� ���� ��ġ
    float angle; // ���� ��鸲�� ����

};




const int numClouds = 8; // ������ ����
Cloud clouds[numClouds]; // ���� �迭


const int numEggs = 3; // ���� ����
Egg eggs[numEggs]; // �� �迭

bool isScene1 = true;  // ���� ��� ���� (��� 1���� ����)



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


void init() {
    glClearColor(0.7, 0.9, 1.0, 1.0); // �ϴû� ���


    // �� ������ �ʱ� ��ġ�� �ӵ� ����
    for (int i = 0; i < numClouds; ++i) {
        clouds[i].x = static_cast<float>(rand() % 1280);
        clouds[i].y = static_cast<float>(rand() % 360 + 300);
        clouds[i].speed = static_cast<float>(rand() % 5 + 1) * 0.1;
    }
    // �� ���� �ʱ� ��ġ, �ӵ�, ��鸲 ����

    eggs[0].x = 400.0;  
    eggs[1].x = 640.0;  
    eggs[2].x = 880.0;

    for (int i = 0; i < numEggs; ++i) {
        eggs[i].y = 300.0; // �� �ٷ� ���� ��ġ
        eggs[i].angle = static_cast<float>(rand() % 360);

    }
}


void drawChicken() {

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


void drawCursor() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);  // ���
    glVertex2f(0.0, 0.0);
    glVertex2f(20.0, 40.0);
    glVertex2f(-20.0, 40.0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-5.0, -40.0);
    glVertex2f(5.0, -40.0);
    glVertex2f(5.0, 0.0);
    glVertex2f(-5.0, 0.0);
    glEnd();
}


void drawGround(int windowWidth, int windowHeight) {
    glColor3f(0.6, 0.4, 0.2); // ���� ����
    glBegin(GL_QUADS);
    glVertex2f(0.0, 0.0);
    glVertex2f(windowWidth, 0.0);
    glVertex2f(windowWidth, windowHeight / 3); // ���� ���̴� â�� 1/3�� ����
    glVertex2f(0.0, windowHeight / 3);
    glEnd();
}


void drawEgg(float x, float y, float angle, float r, float g, float b) {


    glColor3f(r, g, b); // �� ����



    // Ư�� ��ġ������ ��ȯ�� �����ϱ� ���� Push Matrix
    glPushMatrix();



    // Ư�� ��ġ�� �̵� �� ȸ�� ����
    glTranslatef(x, y, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);

    glBegin(GL_POLYGON);

    // �� ����� �� �׸���
    for (int i = 0; i < 360; i += 10) {
        float currentAngle = i * 3.141592 / 180.0;
        float xpos = 50.0 * cos(currentAngle);
        float ypos = 60.0 * sin(currentAngle);
        glVertex2f(xpos, ypos);
    }

    glEnd();


    // ��ȯ ���� ���·� �����ϱ� ���� Pop Matrix
    glPopMatrix();

}


void drawCloud(float x, float y) {
    glColor3f(1.0, 1.0, 1.0); // ��� ������

    // �� ���� ���׶�̸� ������ �ΰ� �׸���
    for (int i = 0; i < 3; ++i) {
        glBegin(GL_POLYGON);

        for (int j = 0; j < 360; j += 10) {
            float angle = j * 3.141592 / 180.0;
            float xpos = x + (i * 30.0) + 20.0 * cos(angle);
            float ypos = y + 15.0 * sin(angle);
            glVertex2f(xpos, ypos);
        }

        glEnd();
    }
}




void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);


    // �� �׸���
    drawGround(windowWidth, windowHeight);

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }


    // �� �׸���
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[0].x, eggs[0].y, 15.0 * sin(eggs[0].angle), 1.0, 1.0, 0.0); // �����
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // ����ȫ��
        drawEgg(eggs[2].x, eggs[2].y, 15.0 * sin(eggs[2].angle), 0.6, 0.4, 0.8); // �������);
        eggs[i].angle += 0.1; // ��鸲 ���� ������Ʈ

    }


    glutSwapBuffers();
}
 

void reshape(int w, int h) {
    glViewport(0, 0, w, h); // ����Ʈ ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h); // ������Ʈ�� �� ����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void update(int value) {

    // ���� �̵� ������Ʈ
    for (int i = 0; i < numClouds; ++i) {
        clouds[i].x += clouds[i].speed;
        if (clouds[i].x > glutGet(GLUT_WINDOW_WIDTH)) {
            clouds[i].x = -50.0; // ȭ�� �������� ������ �ٽ� �����ʿ��� ����
            clouds[i].y = static_cast<float>(rand() % 360 + 300); // ���̴� ���Ƿ� ����
        }
    }
    for (int i = 0; i < numEggs; ++i) {
        if (eggs[i].x > glutGet(GLUT_WINDOW_WIDTH)) {
            eggs[i].x = -50.0; // ȭ�� �������� ������ �ٽ� �����ʿ��� ����
        }
    }

 
    glutPostRedisplay();
    glutTimerFunc(30, update, 0); // 30ms���� ������Ʈ ȣ��
}






int main(int argc, char** argv) {
    srand(static_cast<unsigned>(time(NULL)));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Cloud Animation");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // �������� �ݹ� ���
    glutTimerFunc(25, update, 0); // 25ms���� ������Ʈ ȣ��

    init();

    glutMainLoop();
    return 0;
}
