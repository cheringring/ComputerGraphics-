#include <GL/glut.h>
#include <cmath>
#include <ctime>



bool isScene1 = true;  // ���� ��� ���� (��� 1���� ����)

// ������ ������ ��� ����ü
struct Cloud {
    float x, y; // ������ ���� ��ġ
    float speed; // ������ �̵� �ӵ�
};


struct Egg {
    float x, y; // ���� ���� ��ġ
    float angle; // ���� ��鸲�� ����

};

struct Tree {
    float x, y; // ������ ��ġ
    float height; // ������ ����
};




const int numClouds = 8; // ������ ����
Cloud clouds[numClouds]; // ���� �迭


const int numEggs = 3; // ���� ����
Egg eggs[numEggs]; // �� �迭


const int numTrees = 2; // ������ ����
Tree trees[numTrees]; // ���� �迭




void init() {
    glClearColor(0.7, 0.9, 1.0, 1.0); // �ϴû� ���

    // ���� �ʱ� ��ġ �� ���� ����
    trees[0].x = 200.0;
    trees[0].y = 200.0;
    trees[0].height = 150.0;

    trees[1].x = 800.0;
    trees[1].y = 180.0;
    trees[1].height = 130.0;


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

void drawTree(float x, float y, float height) {
    glColor3f(0.6, 0.3, 0.0); // ���� ������

    // ���� �׸���
    glBegin(GL_QUADS);
    glVertex2f(x - 10.0, y);
    glVertex2f(x + 10.0, y);
    glVertex2f(x + 10.0, y + height);
    glVertex2f(x - 10.0, y + height);
    glEnd();
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




void drawScene1() {
    // ù ��° ��� �׸��� �ڵ�� ���⿡ �ۼ�
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // �� �׸���
    drawGround(windowWidth, windowHeight);

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    // ���� �׸���
    for (int i = 0; i < numTrees; ++i) {
        drawTree(trees[i].x, trees[i].y, trees[i].height);
    }

    // �� �׸���
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[i].x, eggs[i].y, 15.0 * sin(eggs[i].angle), 1.0, 0.0, 0.5); // ����ȫ��
        eggs[i].angle += 0.1; // ��鸲 ���� ������Ʈ
    }
}


void drawScene2() {
    // �� ��° ��� �׸��� �ڵ�� ���⿡ �ۼ�
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // ù ��° ����� ������ ���⿡ ����

        // �� �׸���
    drawGround(windowWidth, windowHeight);

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    // ���� �׸���
    for (int i = 0; i < numTrees; ++i) {
        drawTree(trees[i].x, trees[i].y, trees[i].height);
    }

    // �� �׸���
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[i].x, eggs[i].y, 15.0 * sin(eggs[i].angle), 1.0, 0.0, 0.5); // ����ȫ��
        eggs[i].angle += 0.1; // ��鸲 ���� ������Ʈ
    }

    // ���콺 Ŀ�� �׸���
    drawCursor();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (isScene1) {
        drawScene1();
    }
    else {
        drawScene2();
    }

    glutSwapBuffers();
}


    glutSwapBuffers();
}
 

void timer(int value) {
    // ���� �ð��� ���� ������ ��� ��ȯ
    isScene1 = !isScene1;
    glutPostRedisplay();
    glutTimerFunc(5000, timer, 0);  // 5000ms (5��) �Ŀ� �ٽ� Ÿ�̸� ȣ��
}



void reshape(int w, int h) {
    glViewport(0, 0, w, h); // ����Ʈ ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h); // ������Ʈ�� �� ����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
    glutTimerFunc(5000, timer, 0);  // �ʱ⿡ Ÿ�̸� ȣ��

    init();

    glutMainLoop();
    return 0;
}
