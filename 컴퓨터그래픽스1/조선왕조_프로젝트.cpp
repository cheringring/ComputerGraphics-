#include <stdio.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>


//�Ϸ� 

int startTime = 0;
bool isOrange = false;

bool yellowSquareVisible = true; // �ʱ⿡ ����� �׸� ���̵��� ����

int sceneIndex = 0;
float headOffset = 0.0; // �Ӹ��� y �� ������ ��
int flag = 0;

float transX = 50.0f;
float transY = -10.0f;


//ü�� 


int windowWidth = 1280;
int windowHeight = 720;

float carX = 0.0;

bool isScene1 = true;


// ������ ������ ��� ����ü
struct Cloud {
    float x, y; // ������ ���� ��ġ
    float speed; // ������ �̵� �ӵ�
};


struct Egg {
    float x, y; // ���� ���� ��ġ
    float angle; // ���� ��鸲�� ����

};


struct Chicken {
    float x;
    float y;
    float scale;
    bool visible;
};


Chicken chick;

const int numClouds = 8; // ������ ����
Cloud clouds[numClouds]; // ���� �迭


const int numEggs = 3; // ���� ����
Egg eggs[numEggs]; // �� �迭



float angleX = 0.0f;
float angleY = 0.0f;
float wingAngle = 0.0f;

float flowerX = 0.0;  // ���� �ʱ� x ��ǥ
float flowerY = 400.0;  // ���� �ʱ� y ��ǥ
float scaleFactor = 1.0;


GLfloat sunRadius = 20.0;  // ���� ������
GLfloat sunSpeed = 0.6;  // �ذ� �̵��ϴ� �ӵ�
GLfloat sunX = 0.0f;
GLfloat sunY = 0.0f;





//�Ϸ� 
void toggleWindow(int value) {
    flag++;
    glutPostRedisplay(); // ȭ�� �ٽ� �׸��� ��û
    glutTimerFunc(500, toggleWindow, 0); // 0.5�� �������� �ڱ� �ڽ��� ȣ���Ͽ� �ݺ�
}//���2�� �Ķ� ����� �����Ÿ�






//ü��

void angletimer(int value) {

    wingAngle = 30.0f * sin(angleY * 3.1415926 / 180.0); // ���� ������ sin �Լ��� ����Ͽ� ����

    angleX += 2.0f;
    angleY += 1.0f;
    glutPostRedisplay(); // ȭ�� ���� ��û
    glutTimerFunc(16, angletimer, 0); // 16 �и��ʸ��� Ÿ�̸� ȣ��
}


// OpenGL �ʱ�ȭ �Լ�
void initOpenGL() {

    glClearColor(0.7, 0.9, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void drawSun(GLfloat x, GLfloat y) {

    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glColor3f(1.0, 1.0, 0.0);  // �����
    glScalef(3.0, 3.0, 1.0);  // ũ�⸦ ������ �Ű����� scale ����

    sunX += sunSpeed;
    sunY = 0.2f * sin(sunX);

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i+=10) {
        float angle = static_cast<float>(i) * (3.14159f / 180.0f);
        GLfloat xPos = sunX+sunRadius * cos(angle);
        GLfloat yPos = sunY+sunRadius * sin(angle);

        glVertex2f(xPos, yPos);
    }
    glEnd();

    glPopMatrix();
}

void updateSunPosition() {
    static GLfloat startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0; // �� ������ ��ȯ
    GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0; // �� ������ ��ȯ
    GLfloat elapsedTime = currentTime - startTime;

    // 10�� ���� ������
    if (elapsedTime <= 10.0) {
        GLfloat sunX = sunSpeed * elapsedTime * 40;
        GLfloat sunY = glutGet(GLUT_WINDOW_HEIGHT) / 2.0 - 0.1 * sunSpeed * elapsedTime * elapsedTime;

        // �� �׸���
        drawSun(sunX, sunY);
    }
}


void drawCar(float x, float y) {
 

    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(40.0,30.0, 1.0);  // ũ�⸦ ������ �Ű����� scale ����

    // ��ü
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0); // ������
    glVertex2f(0.0, 0.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(2.5, 1.0);
    glVertex2f(2.5, 2.0);
    glVertex2f(0.0, 2.0);
    glEnd();

    // ����
    glColor3f(0.0, 0.0, 0.0); // ������
    glBegin(GL_TRIANGLE_FAN);
    float radius = 0.3;
    glVertex2f(0.5, -0.5);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159265 / 180.0;
        float x = 0.5 + radius * cos(angle);
        float y = -0.5 + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(1.5, -0.5);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159265 / 180.0;
        float x = 1.5 + radius * cos(angle);
        float y = -0.5 + radius * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
    glPopMatrix();
}


//����
void drawSprout(float x, float y){


    glPushMatrix();

    // Ư�� ��ġ�� �̵� ����
    glTranslatef(x, y, 0.0);
    // �ٱ� �׸���
    glLineWidth(5.0f);  // ������ �β� ����
    glColor3f(0.5f, 0.8f, 0.5f);  // ���λ�
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);  // ������
    glVertex2f(0.0, -50.0);     // ����
    glEnd();



    // ���� ��

    glColor3f(0.5, 0.8, 0.5);  // ���λ�
 
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-30.0, 50.0);
    glVertex2f(-35.0, 30.0);
    glEnd();

    // ������ ��

    glColor3f(0.5, 0.8, 0.5);  // ����
    glBegin(GL_POLYGON);
    glVertex2f(0.0, 0.0);
    glVertex2f(30.0, 50.0);
    glVertex2f(35.0, 30.0);
    glEnd();

    glPopMatrix();
}



void drawTree(float x, float y) {

    glPushMatrix();
    glTranslatef(x, y, 0.0);

    // �ٱ� �׸���
    glColor3f(0.5f, 0.3f, 0.1f);  // ����
    glBegin(GL_POLYGON);
    glVertex2f(60.0, 0.0);
    glVertex2f(84.0, 0.0);
    glVertex2f(84.0, 120.0);
    glVertex2f(60.0, 120.0);
    glEnd();

    // �� �׸���
    glColor3f(0.0, 0.5, 0.0); // �ٻ�
    glBegin(GL_POLYGON);
    glVertex2f(24.0, 120.0);
    glVertex2f(120.0, 120.0);
    glVertex2f(72.0, 240.0);
    glEnd();

    glPopMatrix();
}

//����
void drawsakuraTree(float x, float y,float scale) {



    glPushMatrix();
    glTranslatef(x, y, 0.0);
   glScalef(scale, scale, 1.0);  // ũ�⸦ ������ �Ű����� scale ����



    glColor3f(0.5, 0.5, 0.5); // ��ȸ��
    glBegin(GL_POLYGON);
    glVertex2f(60.0, 0.0);
    glVertex2f(84.0, 0.0);
    glVertex2f(84.0, 120.0);
    glVertex2f(60.0, 120.0);
    glEnd();

    // �� �׸���
    glColor3f(1.0f, 0.6f, 0.8f);  // ���� ��ȫ��
    glBegin(GL_POLYGON);
    glVertex2f(24.0, 120.0);
    glVertex2f(120.0, 120.0);
    glVertex2f(72.0, 240.0);
    glEnd();

    glPopMatrix();

}


void flowerCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * std::cos(theta);
        float y = r * std::sin(theta);

        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawFlower(float x, float y, float flowerSize) {
  
    
    
    // �߽� ��
    flowerCircle(0.0, 0.0, flowerSize, 30);
    glColor3f(1.0, 1.0, 0.0);  // �����

    // ���� �׸���
    for (int i = 0; i < 5; ++i) {
        glColor3f(1.0, 0.6, 0.8);
        float angle = i * (360.0f / 5);
        float petalX = flowerSize * 0.5f * std::cos(angle * 3.1415926f / 180.0);
        float petalY = flowerSize * 0.5f * std::sin(angle * 3.1415926f / 180.0);

        glPushMatrix();
        glTranslatef(x, y, 0.0);
        glTranslatef(petalX, petalY, 0.0);
        glRotatef(30.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.002), 0, 0, 1); // �߰��� �������� ȿ��
        flowerCircle(0.0, 0.0, flowerSize * 0.3, 100);
        glPopMatrix();

    }
}

  


void drawFirework(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0);

    int numLines = 50;
    int maxSegments = 50;

    for (int i = 0; i < numLines; ++i) {
        float angle = i * 3.1415926 / 20.0;
        float length = 60.0 + rand() % 100;
        float x1 = 0.0;
        float y1 = 0.0;
        float x2 = length * cos(angle);
        float y2 = length * sin(angle);


        glBegin(GL_LINE_STRIP);

        // ���� ���׸�Ʈ�� ������ ���� �� �ε巴�� ����
        for (int j = 0; j <= maxSegments; ++j) {
            float t = j / static_cast<float>(maxSegments);
            float tx = (1 - t) * x1 + t * x2;
            float ty = (1 - t) * y1 + t * y2;

            // ������ �� �β�
            glLineWidth((rand() % 5) + 2.0);
            // ������ �� ����
            glColor3f((rand() % 256) / 255.0, (rand() % 256) / 255.0, (rand() % 256) / 255.0);

            glVertex2f(tx, ty);
        }

        glEnd();
    }

    glPopMatrix();
}

void drawCircle(float x, float y, float radius, int Segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < Segments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / Segments;

        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);

        glVertex2f(x + dx, y + dy);
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
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


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
    // ���Ƹ� �ʱ� ��ġ �� ũ�� ����
    chick.x = 640.0;
    chick.y = 300.0;
    chick.scale = 400.0;
    chick.visible = true;

}





void drawChicken(float x, float y, float scale, float wingAngle) {

    // ��ǥ�� ����ϰų� �α׿� �����
    printf("���Ƹ� ��ǥ: (%f, %f)\n", x, y);

    // Ư�� ��ġ������ ��ȯ�� �����ϱ� ���� Push Matrix
    glPushMatrix();



    // Ư�� ��ġ�� �̵� �� ȸ�� ����
    glTranslatef(x, y, 0.0);
    glScalef(scale, scale, 1.0); // �̰� �ù� ���� ã�Ҵ� �̰Ŷ����� ���Ƹ� �Ⱥ�����.





    // ��
    glColor3f(1.0, 1.0, 0.5);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        float px = 0.25 * cos(angle);
        float py = 0.2 * sin(angle);
        glVertex2f(px, py);
    }
    glEnd();



    // �ϴû� ��  (����) 
    glColor3f(0.529, 0.808, 0.922);
    glPushMatrix();
    glTranslatef(-0.05, 0.12, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        float x = 0.03 * cos(angle);
        float y = 0.025 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // �� (����)
    glColor3f(1.0, 1.0, 1.0); // ���
    drawCircle(-0.057, 0.13, 0.008, 480);

    // �ϴû� �� (������)
    glColor3f(0.529, 0.808, 0.922);
    glPushMatrix();
    glTranslatef(0.06, 0.12, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        float x = 0.03 * cos(angle);
        float y = 0.025 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // �� (������)
    glColor3f(1.0, 1.0, 1.0); // ���
    drawCircle(0.044, 0.13, 0.008, 480); // �׹��� ���� ���� ���� , ����°�� ũ��


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
    glColor3f(1.0, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(-0.18, 0.044, 0.0);
    glTranslatef(0.0, 0.025, 0.0);
    glScalef(1.2, 1.2, 1.0);
    glRotatef(86.0 + wingAngle, 0.0, 0.0, 1.0); // ���� ���� �߰�
    glBegin(GL_POLYGON);
    glVertex2f(-0.15, 0.02);
    glVertex2f(-0.1, 0.14);
    glVertex2f(-0.05, 0.02);
    glEnd();
    glPopMatrix();


    // ���� (������)
    glColor3f(1.0, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(0.18, 0.044, 0.0);
    glTranslatef(0.0, 0.025, 0.0);
    glScalef(1.2, 1.2, 1.0);
    glRotatef(-86.0 - wingAngle, 0.0, 0.0, 1.0); // ���� ���� �߰�
    glBegin(GL_POLYGON);
    glVertex2f(0.15, 0.02);
    glVertex2f(0.1, 0.14);
    glVertex2f(0.05, 0.02);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

// �μ��ΰ� �ޱ� ^^)
void drawChick() {
    drawChicken(chick.x, chick.y, chick.scale, wingAngle);
}


//�Ϸ��� �ߴµ� �� �� �ڵ�
void drawChickenFoot(float x, float y, float toeLength) {

    glColor3f(1.0, 1.0, 0.0);

    // ���� ũ�� Ű���
    glLineWidth(30.0);
    glBegin(GL_LINES);

    glVertex2f(x, y);
    glVertex2f(x + toeLength * cos(45.0 * 3.1415926 / 180.0), y + toeLength * sin(45.0 * 3.1415926 / 180.0));


    glVertex2f(x, y);
    glVertex2f(x + toeLength * cos(90.0 * 3.1415926 / 180.0), y + toeLength * sin(90.0 * 3.1415926 / 180.0));

    glVertex2f(x, y);
    glVertex2f(x + toeLength * cos(135.0 * 3.1415926 / 180.0), y + toeLength * sin(135.0 * 3.1415926 / 180.0));

    glEnd();
    // ���� ũ�� ����
 
}


void drawCursor() {


    glPushMatrix();  // ���� ��ȯ ���� ����
    glTranslatef(0.0, -20.0, 0.0);  // �Ʒ��� �̵�
    glRotatef(30.0, 0.0, 0.0, 1.0);  // �������� 20�� ȸ��

    glLineWidth(10.0);

    // �ﰢ�� �׵θ� �׸��� (������)
    glColor3f(0.0, 0.0, 0.0);  // ������ �׵θ�
    glBegin(GL_LINE_LOOP);
    glVertex2f(-15.0, -15.0);  // ���� �Ʒ�
    glVertex2f(0.0, 40.0);      // ���� ������
    glVertex2f(15.0, -15.0);   // ������ �Ʒ�
    glEnd();

    // �簢�� �׵θ� �׸��� (������)
    glBegin(GL_LINE_LOOP);
    glVertex2f(-5.0, -40.0);
    glVertex2f(5.0, -40.0);
    glVertex2f(5.0, 0.0);
    glVertex2f(-5.0, 0.0);
    glEnd();

    // �ﰢ�� ���� ������� �׸���
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);  // ���
    glVertex2f(0.0, 40.0);      // ���� ������
    glVertex2f(-15.0, -15.0);  // ���� �Ʒ�
    glVertex2f(15.0, -15.0);   // ������ �Ʒ�
    glEnd();

    // �簢�� ���� ������� �׸���
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);  // ���
    glVertex2f(-5.0, -40.0);
    glVertex2f(5.0, -40.0);
    glVertex2f(5.0, 0.0);
    glVertex2f(-5.0, 0.0);
    glEnd();

    glPopMatrix();  // ��ȯ ���� ���·� ����

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

    // ��ǥ�� ����ϰų� �α׿� �����
    printf("�� ��ǥ: (%f, %f)\n", x, y);

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

    // ������ �׵θ��� �׸��� ���� �������� ���� Ű��� �ٽ� �� �׸���
    glColor3f(0.0, 0.0, 0.0); // ������ �׵θ�
    glBegin(GL_LINE_LOOP);
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


//�Ϸ� 

void hadrawScene1() {


    // ���� ���� üũ
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "�Ϸ����1 �߻�: %s\n", gluErrorString(error));
    }
    printf("�Ϸ� Draw Scene 1\n");  // ������� ���� �α�


    float x, y;
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT); // ���� �����
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //(0,0,0)���� (0,0, -1)�� ���ڴ�.
    glLoadIdentity();
    // ��Ȳ�� ���� �׸��� (���η� 1/5 �κ�)
    glColor3f(1.0, 0.5, 0.0); // ��Ȳ��
    glRectf(0, 0, 1280, 720 / 5); // �������� ���� ���� 1/5 �κ�
    // ����� ���� �׸��� (������ �κ�)
    glColor3f(1.0, 1.0, 0.0); // �����
    glRectf(0, 720 / 5, 1280, 720); // �������� ���� ���� ������ �κ�
    // ���� �漮 �׸��� (���簢��)
    glColor3f(0.545, 0.271, 0.075); // ����
    glBegin(GL_POLYGON);
    glVertex2f(200, 228); // ��ġ ����
    glVertex2f(300, 228); // ��ġ ����
    glVertex2f(300, 188); // ��ġ ����
    glVertex2f(200, 188); // ��ġ ����
    glEnd();
    // ���� �ٸ� �����(1)
    glColor3f(0.545, 0.271, 0.075); // ����
    glBegin(GL_POLYGON);
    glVertex2f(300, 128); // ��ġ ����
    glVertex2f(300, 188); // ��ġ ����
    glVertex2f(280, 188); // ��ġ ����
    glVertex2f(280, 128); // ��ġ ����
    glEnd();
    // ���� �ٸ� �����(2)
    glColor3f(0.545, 0.271, 0.075); // ����
    glBegin(GL_POLYGON);
    glVertex2f(200, 128); // ��ġ ����
    glVertex2f(200, 188); // ��ġ ����
    glVertex2f(220, 188); // ��ġ ����
    glVertex2f(220, 128); // ��ġ ����
    glEnd();
    // ���� ����� �׸��� (Ÿ���� �ٻ�)
    glColor3f(0.545, 0.271, 0.075); // ����
    glBegin(GL_POLYGON);
    float radiusX = 40; // Ÿ���� ������ ����
    float radiusY = 80;
    for (float angle = 1.0; angle < 360.0; angle += 1.0) {
        x = 200 + radiusX * cos(angle * 3.14159265 / 180.0);
        y = 260 + radiusY * sin(angle * 3.14159265 / 180.0);
        glVertex2f(x, y);
    }
    glEnd();
    // ��� ��ü �׸��� (���� ���簢��)
    glColor3f(0.0, 0.0, 0.0); // ������
    // �Ӹ� (��)
    glBegin(GL_POLYGON);
    float headRadius = 40; // �Ӹ��� ������ ���� (�� ��� Ű��)
    for (float angle = 1.0; angle < 360.0; angle += 1.0) {
        x = 280 + headRadius * cos(angle * 3.14159265 / 180.0);
        y = 330 + headRadius * sin(angle * 3.14159265 / 180.0) + headOffset;
        glVertex2f(x, y);
    }
    glEnd();
    // ���� (���簢��)
    glBegin(GL_POLYGON);
    glVertex2f(242, 300); // ��ġ ����
    glVertex2f(268, 300); // ��ġ ����
    glVertex2f(268, 200); // ��ġ ����
    glVertex2f(242, 200); // ��ġ ����
    glEnd();
    //�� (���簢��)
    glBegin(GL_POLYGON);
    glVertex2f(350, 250); // ��ġ ����
    glVertex2f(268, 270); // ��ġ ����
    glVertex2f(268, 250); // ��ġ ����
    glVertex2f(350, 270); // ��ġ ����
    glEnd();
    //�ٸ�(1)
    glBegin(GL_POLYGON);
    glVertex2f(310, 200); // ��ġ ����
    glVertex2f(268, 200); // ��ġ ����
    glVertex2f(268, 220); // ��ġ ����
    glVertex2f(310, 220); // ��ġ ����
    glEnd();
    //�ٸ�(2)
    glBegin(GL_POLYGON);
    glVertex2f(310, 150); // ��ġ ����
    glVertex2f(298, 150); // ��ġ ����
    glVertex2f(298, 220); // ��ġ ����
    glVertex2f(310, 220); // ��ġ ����
    glEnd();
    // ������ â�� �׸���
    glColor3f(0.529, 0.808, 0.922); // �Ķ���
    glBegin(GL_POLYGON);
    glVertex2f(800, 660);
    glVertex2f(1120, 660);
    glVertex2f(1120, 420);
    glVertex2f(800, 420);
    glEnd();
    // ...
    glColor3f(0.545, 0.271, 0.075); // ����
    glLineWidth(5); // �� �β� ����
    glBegin(GL_LINE_LOOP);
    glVertex2f(800, 660);
    glVertex2f(1120, 660);
    glVertex2f(1120, 420);
    glVertex2f(800, 420);
    glEnd();
    // å�� �׸���
    glColor3f(0.529, 0.808, 0.922);
    glBegin(GL_POLYGON);
    glVertex2f(330, 225);
    glVertex2f(430, 225);
    glVertex2f(430, 240);
    glVertex2f(330, 240);
    glEnd();
    // ...
    glColor3f(0.545, 0.271, 0.075); // ����
    glBegin(GL_POLYGON);
    glVertex2f(370, 225);
    glVertex2f(410, 225);
    glVertex2f(410, 128);
    glVertex2f(370, 128);
    glEnd();
    //���콺
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(325, 250);
    glVertex2f(345, 250);
    glVertex2f(345, 240);
    glVertex2f(325, 240);
    glEnd();
    //��ǻ��
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(395, 245);
    glVertex2f(425, 245);
    glVertex2f(425, 240);
    glVertex2f(395, 240);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(405, 255);
    glVertex2f(415, 255);
    glVertex2f(415, 240);
    glVertex2f(405, 240);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(385, 255);
    glVertex2f(425, 255);
    glVertex2f(425, 350);
    glVertex2f(385, 350);
    glEnd();
    // ħ�� �׸���
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(1625, 245);
    glVertex2f(825, 245);
    glVertex2f(925, 100);
    glVertex2f(1625, 100);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(1625, 50);
    glVertex2f(925, 50);
    glVertex2f(825, 245);
    glVertex2f(825, 155);
    glVertex2f(925, 50);
    glEnd();
    glColor3f(0.0, 0.0, 0.0); // ������
    glLineWidth(3); // �� �β� ����
    glBegin(GL_LINE_LOOP);
    glVertex2f(1625, 245);
    glVertex2f(825, 245);
    glVertex2f(925, 120);
    glVertex2f(1625, 100);
    glEnd();
    glColor3f(0.0, 0.0, 0.0); // ������
    glLineWidth(3); // �� �β� ����
    glBegin(GL_LINE_LOOP);
    glVertex2f(1625, 50);
    glVertex2f(1625, 50);
    glVertex2f(1625, 50);
    glVertex2f(825, 245);
    glVertex2f(825, 155);
    glVertex2f(925, 50);
    glEnd();
    // ...
    glFlush(); // ȭ�鿡 ���
    glPopMatrix();

}

void hadrawScene2() {


    // ���� ���� üũ
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "�Ϸ� ���2 �߻�: %s\n", gluErrorString(error));
    }
    printf("�Ϸ� Draw Scene 2\n");  // ������� ���� �α�


    float x, y;
    glClear(GL_COLOR_BUFFER_BIT); // ���� �����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // ��������� ��ü ������ ä���
    glColor3f(1.0, 1.0, 0.0); // �����
    glRectf(0, 0, 1280, 720); // ��ü ������ ũ��� �簢�� �׸���
    // �����
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(320, 200);
    glVertex2f(950, 200);
    glVertex2f(950, 610);
    glVertex2f(320, 610);
    glEnd();
    // ȭ��â
    if (flag % 2 == 0) {
        glColor3f(0.0, 0.0, 1.0); // �Ķ���
    }
    else {
        glColor3f(1.0, 1.0, 1.0); // ���
    }
    glBegin(GL_POLYGON);
    glVertex2f(330, 210);
    glVertex2f(940, 210);
    glVertex2f(940, 590);
    glVertex2f(330, 590);
    glEnd();
    // ������ �� �׸���
    glColor3f(0.0, 0.0, 0.0); // ������
    glBegin(GL_POLYGON);
    float blackCircleRadius = 80; // ���� ������ ����
    int segments = 100; // ���� �󸶳� �Ų����� �׸��� �����ϴ� ���׸�Ʈ ��
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float cx = 620 + blackCircleRadius * cosf(theta);
        float cy = 250 + blackCircleRadius * sinf(theta);
        glVertex2f(cx, cy);
    }
    glEnd();
    // ���� Ÿ���� �׸���
    glColor3f(0.545, 0.271, 0.075); // ����
    glBegin(GL_POLYGON);
    float radiusX = 160; // Ÿ���� ������ ����
    float radiusY = 200;
    for (float angle = 1.0; angle < 360.0; angle += 1.0) {
        x = 620 + radiusX * cos(angle * 3.14159265 / 180.0);
        y = 00 + radiusY * sin(angle * 3.14159265 / 180.0);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush(); // ȭ�鿡 ���
}

void hadrawScene3() {


    // ���� ���� üũ
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "�Ϸ� ���3 �߻�: %s\n", gluErrorString(error));
    }
    printf(" �Ϸ� Draw Scene 1\n");  // ������� ���� �α�


    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT); // ���� �����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // �ʷϻ� ���� �׸��� (���η� 1/5 �κ�)
    glColor3f(0.0, 1.0, 0.0); // �ʷϻ�
    glRectf(0, 0, windowWidth, windowHeight / 5); // �������� ���� ���� 1/5 �κ�

    // �Ķ��� ���� �׸��� (������ �κ�)
    glColor3f(0.529, 0.808, 0.922); // �Ķ���
    glRectf(0, windowHeight / 5, windowWidth, windowHeight); // �������� ���� ���� ������ �κ�
    // �ʷϻ��� �Ķ��� ��迡 ���� �� �׸���
    glColor3f(0.0, 0.0, 0.0); // ������
    glLineWidth(2.0); // �� �β� ����

    // ���� ��輱
    glBegin(GL_LINES);
    glVertex2f(0, windowHeight / 5);
    glVertex2f(windowWidth, windowHeight / 5);
    glEnd();


    // �߾ӿ� ����� ���簢�� �׸���
    glColor3f(1.0, 1.0, 0.0); // �����
    int squareWidth = 200; // �׸� ���� ����
    int squareHeight = 100; // �׸� ���� ����
    int squareX = (windowWidth - squareWidth) / 2; // �߾� X ��ġ ���
    int squareY = (windowHeight - squareHeight) / 2; // �߾� Y ��ġ ���

    // �׵θ� �׸���
    glLineWidth(2.0); // �׵θ� �β� ����
    glColor3f(0.0, 0.0, 0.0); // ������ �׵θ�
    glBegin(GL_LINE_LOOP); // �簢�� �׵θ� ����
    glVertex2f(squareX, squareY); // �»��
    glVertex2f(squareX + squareWidth, squareY); // ����
    glVertex2f(squareX + squareWidth, squareY + squareHeight); // ���ϴ�
    glVertex2f(squareX, squareY + squareHeight); // ���ϴ�
    glEnd(); // �簢�� �׵θ� ����

    int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    if (startTime == 0) {
        startTime = elapsedTime;
    }

    int timeDiff = elapsedTime - startTime;
    int orangeSwitchInterval = 2000; // 2��

    if (timeDiff > orangeSwitchInterval) {
        isOrange = !isOrange;
        startTime = elapsedTime;
    }

    // ���� ��ĥ�ϱ�
    glColor3f(1.0, 1.0, 0.0); // �����
    glBegin(GL_QUADS); // �簢�� ����
    glVertex2f(squareX, squareY); // �»��
    glVertex2f(squareX + squareWidth, squareY); // ����
    glVertex2f(squareX + squareWidth, squareY + squareHeight); // ���ϴ�
    glVertex2f(squareX, squareY + squareHeight); // ���ϴ�
    glEnd(); // �簢�� ����
    if (isOrange) {
        glColor3f(1.0, 0.5, 0.0); // ��Ȳ��
    }
    else {
        glColor3f(1.0, 1.0, 0.0); // �����
    }
    glBegin(GL_QUADS); // �簢�� ����
    glVertex2f(squareX, squareY);
    glVertex2f(squareX + squareWidth, squareY);
    glVertex2f(squareX + squareWidth, squareY + squareHeight);
    glVertex2f(squareX, squareY + squareHeight);
    glEnd(); // �簢�� ����

    // "Start" �ؽ�Ʈ ���
    glColor3f(0.0, 0.0, 0.0); // ������
    glRasterPos2i(squareX + squareWidth / 2 - 25, squareY + squareHeight / 2); // �ؽ�Ʈ ��ġ ����
    void* font = GLUT_BITMAP_HELVETICA_18; // �۲ð� ũ�� ����
    const char* text = "Start"; // �ؽ�Ʈ
    for (int i = 0; text[i] != '\0'; ++i) {
        glutBitmapCharacter(font, text[i]); // ���� �ϳ��� ���
    }

    // ... (�ﰢ��, ȭ��ǥ �׸���)
    glColor3f(0.0, 0.0, 0.0); // ������
    glBegin(GL_LINE_LOOP);
    glVertex2f(windowWidth / 2 + transX, windowHeight / 2 + 23 + transY); // ��� ������
    glVertex2f(windowWidth / 2 - 17 + transX, windowHeight / 2 - 28 + transY); // ���ϴ�
    glVertex2f(windowWidth / 2 + 17 + transX, windowHeight / 2 - 28 + transY); // ���ϴ�
    glEnd();

    // ȭ��ǥ �׸�
    glColor3f(0.0, 0.0, 0.0); // ������
    glBegin(GL_LINE_LOOP);
    glVertex2f(windowWidth / 2 - 10 + transX, windowHeight / 2 - 28 + transY); // �»��
    glVertex2f(windowWidth / 2 + 10 + transX, windowHeight / 2 - 28 + transY); // ����
    glVertex2f(windowWidth / 2 + 10 + transX, windowHeight / 2 - 48 + transY); // ���ϴ�
    glVertex2f(windowWidth / 2 - 10 + transX, windowHeight / 2 - 48 + transY); // ���ϴ�
    glEnd();

    glColor3f(1.0, 1.0, 1.0); // ���
    glBegin(GL_TRIANGLES);
    glVertex2f(windowWidth / 2 + transX, windowHeight / 2 + 23 + transY); // ��� ������
    glVertex2f(windowWidth / 2 - 17 + transX, windowHeight / 2 - 28 + transY); // ���ϴ�
    glVertex2f(windowWidth / 2 + 17 + transX, windowHeight / 2 - 28 + transY); // ���ϴ�
    glEnd();//ȭ��ǥ �ڵ�
    glColor3f(1.0, 1.0, 1.0); // ���
    glBegin(GL_QUADS);
    glVertex2f(windowWidth / 2 - 10 + transX, windowHeight / 2 - 28 + transY); // �»��
    glVertex2f(windowWidth / 2 + 10 + transX, windowHeight / 2 - 28 + transY); // ����
    glVertex2f(windowWidth / 2 + 10 + transX, windowHeight / 2 - 48 + transY); // ���ϴ�
    glVertex2f(windowWidth / 2 - 10 + transX, windowHeight / 2 - 48 + transY); // ���ϴ�
    glEnd();
    glPopMatrix();
}



//ü��
void drawScene1() {
    // ù ��° ��� �׸��� �ڵ�� ���⿡ �ۼ�
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);


    // ���� ���� üũ
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "���1 �߻�: %s\n", gluErrorString(error));
    }
    printf("Draw Scene 1\n");  // ������� ���� �α�




    // �� �׸���
    drawGround(windowWidth, windowHeight);

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }



    float groundHeight = windowHeight / 3 + 30.0;  // ���� ���� (1/3�� ����)
    float sproutSpacing = 250.0f;  // ���� ����


    // ���� �׸���
    for (int i = 0; i < 4; ++i) {
        float sproutX = 640.0 + (i - 1.5) * sproutSpacing;  // �� ��ǥ�� �������� �߾� ���ĵǵ��� ����
        float sproutY = groundHeight;


        drawSprout(sproutX, sproutY);
    }

    // �� �׸���
    // ���� ��ġ �迭 ����


    for (int i = 0; i < numEggs; ++i) {

        drawEgg(eggs[0].x, eggs[0].y, 15.0 * sin(eggs[0].angle), 1.0, 1.0, 0.0); // ���
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // ����ȫ��
        drawEgg(eggs[2].x, eggs[2].y, 15.0 * sin(eggs[2].angle), 0.6, 0.4, 0.8); // �������);
        eggs[i].angle += 0.1; // ��鸲 ���� ������Ʈ
    }
    glPopMatrix();
}
    


void drawScene2() {
 
    // �� ��° ��� �׸��� �ڵ�� ���⿡ �ۼ�
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);


    // ���� ���� üũ
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "���2 �߻�: %s\n", gluErrorString(error));
    }
    printf("Draw Scene 2\n");  // ������� ���� �α�



    // �� �׸���
    drawGround(windowWidth, windowHeight);

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    //���� �׸���
    float groundHeight = windowHeight / 3 + 30.0;  // ���� ���� (1/3�� ����)
    float sproutSpacing = 250.0f;  // ���� ����


    // ���� �׸���
    for (int i = 0; i < 4; ++i) {
        float sproutX = 640.0 + (i - 1.5) * sproutSpacing;  // �� ��ǥ�� �������� �߾� ���ĵǵ��� ����
        float sproutY = groundHeight;


        drawSprout(sproutX, sproutY);
    }


    // �� �׸���
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[0].x, eggs[0].y, 15.0 * sin(eggs[0].angle), 1.0, 1.0, 0.0); // �����
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // ����ȫ��
        drawEgg(eggs[2].x, eggs[2].y, 15.0 * sin(eggs[2].angle), 0.6, 0.4, 0.8); // �������);
        eggs[i].angle += 0.2; // ��鸲 ���� ������Ʈ
    }

    // ���콺 Ŀ�� �׸���

    float cursorX = 640.0; // ���÷� 640.0���� ����
    float cursorY = 300.0; // ���÷� 300.0���� ����
    glPushMatrix();
    glTranslatef(cursorX, cursorY, 0.0);
    glScalef(scaleFactor, scaleFactor, 1.0);  // ũ�� ����
    drawCursor();
    glPopMatrix();

}


void drawScene3() {

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // ù ��° ����� ������ ���⿡ ����
    // 
    // 
    // 
    // �� �׸���
    drawGround(windowWidth, windowHeight);

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }
    //���� �׸���
    float groundHeight = windowHeight / 3 + 30.0;  // ���� ���� (1/3�� ����)
    float sproutSpacing = 250.0f;  // ���� ����


    // ���� �׸���
    for (int i = 0; i < 4; ++i) {
        float sproutX = 640.0 + (i - 1.5) * sproutSpacing;  // �� ��ǥ�� �������� �߾� ���ĵǵ��� ����
        float sproutY = groundHeight;


        drawSprout(sproutX, sproutY);
    }

    // �� �׸���
    for (int i = 0; i < numEggs; ++i) {
        eggs[i].y += 1.0; // ���� ���� �̵�
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // ����ȫ��
    }

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    
}









void drawScene4() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // ���� ���� üũ
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "ü�� ���4 �߻�: %s\n", gluErrorString(error));
    }
    printf("ü�� Draw Scene 4 \n");  // ������� ���� �α�


    // ù ��° ����� ������ ���⿡ ����
    // �� �׸���
    drawGround(windowWidth, windowHeight);

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    //���� �׸���
    float groundHeight = windowHeight / 3 + 30.0;  // ���� ���� (1/3�� ����)
    float sproutSpacing = 250.0f;  // ���� ����


    // ���� �׸���
    for (int i = 0; i < 4; ++i) {
        float sproutX = 640.0 + (i - 1.5) * sproutSpacing;  // �� ��ǥ�� �������� �߾� ���ĵǵ��� ����
        float sproutY = groundHeight;


        drawSprout(sproutX, sproutY);
    }

    for (int i = 0; i < numEggs; ++i) {
        eggs[i].y += 1.0; // ���� ���� �̵�

        // ���� �� �Ʒ��� �򸮵��� �׸���

        if (eggs[1].y < 400.0) {
            drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // ����ȫ��

            for (int j = 0; j < 5; ++j) {
                float xpos = eggs[1].x;
                float ypos = eggs[1].y;


                    drawFirework(xpos, ypos);
                }
            }
        }
    }
   





    void drawScene5() {
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

        // �� �׸���
        drawGround(windowWidth, windowHeight);

        // ���� �׸���
        for (int i = 0; i < numClouds; ++i) {
            drawCloud(clouds[i].x, clouds[i].y);
        }

        //���� �׸��� 
        float groundHeight = windowHeight / 3 ;  // ���� ���� (1/3�� ����)
        float objectSpacing = 300.0f;  // ����

        
        for (int i = 0; i < 4; ++i) {
            float TreeX = 640.0 + (i - 1.7) * objectSpacing;  // �� ��ǥ�� �������� �߾� ���ĵǵ��� ����
            float TreeY = groundHeight;

            drawTree(TreeX, TreeY); 

        }

        // ���Ƹ� �׸���
        glPushMatrix();
        drawChick();
        glPopMatrix();

        // 0.5�� ���� ���� �׸���

        static int fireworksTimer = 0;


        if (fireworksTimer < 20) {
            for (int i = 0; i < 12; ++i) {
                float xpos = chick.x; // ���Ƹ��� ��ġ�� ����
                float ypos = chick.y;

                drawFirework(xpos, ypos);
            }
            fireworksTimer++;
        }


        // ���� �׸���
        for (int i = 0; i < numClouds; ++i) {
            drawCloud(clouds[i].x, clouds[i].y);
        }
    }





void drawScene6() {

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // ���� �ĴڰŸ��� �ִϸ��̼�
    wingAngle = 700.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 0.0174533; // �������� ��ȯ5); // * �� �κ��� �ĴڰŸ��°���
    // sin ���� �� �� ���� �Ĵ�

     // �� �׸���
    drawGround(windowWidth, windowHeight);


    //���� �׸��� 
    float groundHeight = windowHeight / 3;  // ���� ���� (1/3�� ����)
    float objectSpacing = 300.0f;  // ����


    for (int i = 0; i < 4; ++i) {
        float TreeX = 640.0 + (i - 1.7) * objectSpacing;  // �� ��ǥ�� �������� �߾� ���ĵǵ��� ����
        float TreeY = groundHeight;

        drawTree(TreeX, TreeY);

    }
    // ���Ƹ� �׸���
    glPushMatrix();
    glTranslatef(chick.x, chick.y, 0.0);
    glScalef(chick.scale, chick.scale, 1.0);
    drawChicken(0.0, 0.0, 1.0, wingAngle);  // wingAngle�� drawChicken �Լ��� ����
    glPopMatrix();





    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
        // �̷��� ���Ƹ��� ������ �������� �ʴ´�
    }
}


  


void drawScene7() {


    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // ���� �ĴڰŸ��� �ִϸ��̼�
    wingAngle = 700.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 0.0174533; // �������� ��ȯ5); // * �� �κ��� �ĴڰŸ��°���
    // sin ���� �� �� ���� �Ĵ�

     // �� �׸���
    drawGround(windowWidth, windowHeight);


    //���� �׸��� 
    float groundHeight = windowHeight / 3;  // ���� ���� (1/3�� ����)
    float objectSpacing = 300.0f;  // ����



 
    //�����׸��� 
        for (int i = 0; i < 4; ++i) {
            float TreeX = 640.0 + (i - 1.7) * objectSpacing;  // �� ��ǥ�� �������� �߾� ���ĵǵ��� ����
            float TreeY = groundHeight;

            drawTree(TreeX, TreeY);

        }

        // ���Ƹ� �׸���
        glPushMatrix();
        glTranslatef(chick.x, chick.y, 0.0);
        glScalef(chick.scale, chick.scale, 1.0);
        drawChicken(0.0, 0.0, 1.0, wingAngle);  // wingAngle�� drawChicken �Լ��� ����
        glPopMatrix();



        // ���� �׸���
        for (int i = 0; i < numClouds; ++i) {
            drawCloud(clouds[i].x, clouds[i].y);
            // �̷��� ���Ƹ��� ������ �������� �ʴ´�
        }

        // ���� �������� ��ġ ����
        for (int i = 0; i < 60; ++i) {
            float flowerX = static_cast<float>(rand() % (2 * windowWidth) - windowWidth);
            float flowerY = static_cast<float>(rand() % (2 * windowHeight) - windowHeight);
            float rotationAngle = static_cast<float>(rand() % 360);
            float flowerSize = 40.0;


            float deltaTime = 0.0000001;  // �ð��� ���� �̵����� �����ϴ� ����

            // ���� �������� �ӵ� ����
            flowerY -= deltaTime * 0.00000001;  // ���⼭ �� ���� ����
            drawFlower(flowerX, flowerY, flowerSize);



    }
}



void drawScene8() {

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);


    // �� �׸���
    drawGround(windowWidth, windowHeight);




        // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
        // �̷��� ���Ƹ��� ������ �������� �ʴ´�
    }


    //���� �׸��� 
    float groundHeight = windowHeight / 3;  // ���� ���� (1/3�� ����)
    float objectSpacing = 300.0f;  // ����


    for (int i = 0; i < 4; ++i) {
        float TreeX = 640.0 + (i - 1.8) * objectSpacing;  // �� ��ǥ�� �������� �߾� ���ĵǵ��� ����
        float TreeY = groundHeight;

        drawsakuraTree(TreeX, TreeY,1.5);
    }

    // ���� �ĴڰŸ��� �ִϸ��̼�
    wingAngle = 700.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 0.0174533; // �������� ��ȯ5); // * �� �κ��� �ĴڰŸ��°���
    // sin ���� �� �� ���� �Ĵ�
    float elapsedTime = glutGet(GLUT_ELAPSED_TIME) * 0.001;  // �� ������ ��ȯ
    float verticalOffset = 60.0 * sin(elapsedTime * 0.5);  // ���Ʒ��� �����̴� offset

    glPushMatrix();
    // ���Ƹ� �׸���
    glTranslatef(chick.x, chick.y + verticalOffset, 0.0);
    glScalef(chick.scale, chick.scale, 1.0);
    drawChicken(0.0, 0.0, 1.0, wingAngle);  // wingAngle�� drawChicken �Լ��� ����
    glPopMatrix();
    glutPostRedisplay();


    }


void drawScene9() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL Error: %s\n", gluErrorString(error));
    }
    // �ð��� ���� ���� ��ġ ���
    GLfloat carAngle = fmod((carX + 1.5) / windowWidth * 360.0, 360.0);

    // �ʱ� ������ ���� ���� ��Ȳ��
    GLfloat initialColor[3] = { 1.0, 0.8, 0.6 };  // ��Ȳ��

    // ���� ��ȭ�� ���� ����
    GLfloat backgroundColor[3];

    if (carAngle <= 85.0) {
        // ���� ��Ȳ��
        backgroundColor[0] = initialColor[0];
        backgroundColor[1] = initialColor[1];
        backgroundColor[2] = initialColor[2];
    }
    else if (carAngle <= 170.0) {
        // �������
        backgroundColor[0] = 0.8;  // Red
        backgroundColor[1] = 0.6;  // Green
        backgroundColor[2] = 1.0;  // Blue
    }
    else {
        // ���� ����
        backgroundColor[0] = 0.0;  // Red
        backgroundColor[1] = 0.0;  // Green
        backgroundColor[2] = 0.4;  // Blue
    }

    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0);

    updateSunPosition();

    // �� �׸���
    drawGround(windowWidth, windowHeight/3.5);




    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
        // �̷��� ���Ƹ��� ������ �������� �ʴ´�
    }


    //���� �׸��� 
    float groundHeight = windowHeight /3.5;  // ���� ���� (1/4�� ����)
    float objectSpacing = 200.0f;  // ����
    int numTrees = 8;

    for (int i = 0; i < numTrees; ++i) {
        float treeX = windowWidth / 2 + (i - numTrees / 2) * objectSpacing;  // �߾� ����
        float treeY = groundHeight;

        // ���� ũ�⸦ ����
        drawsakuraTree(treeX, treeY-138.0, 0.8);
    }



    carX += 1.5;  // �̵� �ӵ� �� ����
    printf("Car X: %f\n", carX);

    // ȭ���� ����� �ʱ�ȭ
    if (carX > windowWidth) {
        carX = -2.5;  // �ʱⰪ �缳��
    }
    // �ڵ��� �̵�
    glPushMatrix();
    glTranslatef(carX, groundHeight , 0.0);
    glPopMatrix();


    drawCar(carX, groundHeight-138.0);


    glutPostRedisplay();
}

void drawScene100() {
    drawChick();
}


void update(int value) {


    // ���� ���� üũ
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "update ���� �߻�: %s\n", gluErrorString(error));
    }

    // ���⿡�� �ٸ� �ʱ�ȭ �� ������Ʈ �۾� ����

    // �𵨺� ��� �ʱ�ȭ
    //glLoadIdentity();

    // �������� ����� �۾�
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // ���� �̵� ������Ʈ
    for (int i = 0; i < numClouds; ++i) {
        clouds[i].x += clouds[i].speed;
        if (clouds[i].x > glutGet(GLUT_WINDOW_WIDTH)) {
            clouds[i].x = -50.0; // ȭ�� �������� ������ �ٽ� �����ʿ��� ����
            clouds[i].y = static_cast<float>(rand() % 360 + 300);
        }
    }
    for (int i = 0; i < numEggs; ++i) {
        if (eggs[i].x > glutGet(GLUT_WINDOW_WIDTH)) {
            eggs[i].x = -50.0; // ȭ�� �������� ������ �ٽ� �����ʿ��� ����
        }
    }

    scaleFactor += 0.01;  // ���÷� 0.01�� �����ϵ��� ����

    // scaleFactor�� ���� �� �̻��� �Ǹ� �ٽ� �����ϵ��� ����
    if (scaleFactor > 1.5) {
        scaleFactor = 1.0;
    }

    // ���Ƹ� ���� �ĴڰŸ��� �ִϸ��̼�
    wingAngle = 800.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 0.0174533;



    //�Ϸ� Ÿ�̸�
    headOffset = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01) * 5;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0); // 50ms���� ������Ʈ ȣ��


}


void timer(int value) {
    // ���� �ð��� ���� ������ ��� ��ȯ
    sceneIndex = (sceneIndex+1) % 100; // ����� �� ����

    printf("Timer: SceneIndex = %d\n", sceneIndex); // ������� ���� �α�


    // ��� ����� ����� ��� ó�� ������� ���ư���
    if (sceneIndex ==100 ) {
        glutPostRedisplay(); // ȭ���� �ٽ� �׸����� ��û
    }
    else {
        int sceneInterval;

       switch (sceneIndex) {
        case 0:
            sceneInterval = 1500;  
            break;
        case 1: //�Ϸ�1
            sceneInterval = 3000;  
            break;
        case 2://�Ϸ�2
            sceneInterval = 3000; 
            break;
        case 3://�Ϸ�3
            sceneInterval = 3000;
            break;
        case 4: //ü��1
            sceneInterval = 1500;  
            break;
        case 5: //ü��2
            sceneInterval = 1500;  
            break;
        case 6: //ü��3
            sceneInterval = 1500; 
            break;
        case 7: //ü��4
            sceneInterval = 1500; 
            break;
        case 8:  //ü��5
            sceneInterval = 1500;  
            break;
        case 9: //ü��6
            sceneInterval = 1500;  
            break;
        case 10: //ü��7
            sceneInterval = 1500;
            break;
        case 11: //ü��8
            sceneInterval = 1500;
        case 12: //ü��9
            sceneInterval = 9000;
     
        }


        glutTimerFunc(sceneInterval, timer, 0);
        glutPostRedisplay();
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    printf("Display: SceneIndex = %d\n", sceneIndex); // ������� ���� �α�

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // ����Ʈ ����
    glViewport(0, 0, windowWidth, windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);


    glMatrixMode(GL_MODELVIEW);


    switch (sceneIndex) {

    case 0:
        drawScene100(); // �� ��� �ȳ����� ������ �ӽ��ڵ� 
        break;
    case 1:
        hadrawScene1(); //�Ϸ� ���1
        break;
    case 2:
        hadrawScene2(); //�Ϸ� ���2
        break;
    case 3:
        hadrawScene3(); //�Ϸ� ���3
        break;
    case 4: 
        printf("Display: Calling drawScene1\n"); 
        drawScene1();//ü��
        break;
    case 5:
        printf("Display: Calling drawScene2\n");
        drawScene2(); //ü��
        break;
    case 6:
        printf("Display: Calling drawScene3\n");
        drawScene3(); //����
        break;
    case 7:
        drawScene4(); //����
        break;
    case 8:
        drawScene5(); //����
        break;
    case 9:
        drawScene6(); //����
        break;
    case 10:
        drawScene7(); //����
        break;
    case 11:
        drawScene8();//����
        break;
    case 12:
        drawScene9(); //����
    default:
        break;
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


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Cloud Animation");

    // �ʱ� ���� üũ
    GLenum initError = glGetError();
    if (initError != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL �ʱ�ȭ �� ���� �߻�: %s\n", gluErrorString(initError));
        return -1;
    }

    init();
    initOpenGL(); // OpenGL �ʱ�ȭ �Լ�

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // �������� �ݹ� ���
    glutTimerFunc(25, update, 0); // 25ms���� ������Ʈ ȣ��
    glutTimerFunc(0, timer, 0);  // �ʱ⿡ Ÿ�̸� ȣ��
    glutTimerFunc(500, toggleWindow, 0);

    glutMainLoop();
    return 0;
}