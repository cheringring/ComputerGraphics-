#include <GL/glut.h>
#include <cmath>
#include <ctime>




bool isScene1 = true;
int sceneIndex = 0; // ���� ��� �ε���


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
float flowerY = 500.0;  // ���� �ʱ� y ��ǥ
float flowerRotation = 0.0;  // ���� ȸ�� ����



void angletimer(int value) {

    wingAngle = 30.0f * sin(angleY * 3.1415926 / 180.0); // ���� ������ sin �Լ��� ����Ͽ� ����

    angleX += 2.0f;
    angleY += 1.0f;
    glutPostRedisplay(); // ȭ�� ���� ��û
    glutTimerFunc(16, angletimer, 0); // 16 �и��ʸ��� Ÿ�̸� ȣ��
}



/*void drawPetal(float x, float y, float length) { //���ٱ׸�������
    glBegin(GL_POLYGON);

    for (int i = 0; i < 360; i += 45) {
        float angle = i * 3.14159 / 180.0;
        float dx = length * cos(angle);
        float dy = length * sin(angle);
        glVertex2f(x + dx, y + dy);
    }

    glEnd();
}

void drawFlower(float x, float y) {
    // �� �׸��� �ڵ�
    glColor3f(1.0, 0.0, 0.0);  // ������ ����
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(flowerRotation, 0.0, 0.0, 1.0);  // ���� ȸ��
    // ���� �׸���
    drawPetal(0.0, 20.0, 30.0);  // ���� ��, ������ ��ġ�� ���̸� �����ϼ���
    drawPetal(0.0, 20.0, 30.0);
    drawPetal(0.0, 20.0, 30.0);

    glPopMatrix();
}*/



void drawFirework(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0);

    int numLines = 16;
    int maxSegments = 15;

    for (int i = 0; i < numLines; ++i) {
        float angle = i * 3.1415926 / 8.0;
        float length = 50.0 + rand() % 50;
        float x1 = 0.0;
        float y1 = 0.0;
        float x2 = length * cos(angle);
        float y2 = length * sin(angle);

        // ������ �� ����
        glColor3f((rand() % 256) / 255.0, (rand() % 256) / 255.0, (rand() % 256) / 255.0);

        glBegin(GL_LINE_STRIP);

        // ���� ���׸�Ʈ�� ������ ���� �� �ε巴�� ����
        for (int j = 0; j <= maxSegments; ++j) {
            float t = j / static_cast<float>(maxSegments);
            float tx = (1 - t) * x1 + t * x2;
            float ty = (1 - t) * y1 + t * y2;

            // ������ �� �β�
            glLineWidth((rand() % 3) + 1.0);

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


void drawEyeTouch(float x, float y, float scale) {
  
}



void drawCursor() {



    glTranslatef(0.0, -20.0, 0.0);  // �Ʒ��� �̵�
    glRotatef(20.0, 0.0, 0.0, 1.0);  // �������� 20�� ȸ��

    glLineWidth(3.0);

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

    // �� �׸���
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[0].x, eggs[0].y, 15.0 * sin(eggs[0].angle), 1.0, 1.0, 0.0); // �����
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // ����ȫ��
        drawEgg(eggs[2].x, eggs[2].y, 15.0 * sin(eggs[2].angle), 0.6, 0.4, 0.8); // �������);
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


    // �� �׸���
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[0].x, eggs[0].y, 15.0 * sin(eggs[0].angle), 1.0, 1.0, 0.0); // �����
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // ����ȫ��
        drawEgg(eggs[2].x, eggs[2].y, 15.0 * sin(eggs[2].angle), 0.6, 0.4, 0.8); // �������);
        eggs[i].angle += 0.1; // ��鸲 ���� ������Ʈ
    }
    // ���콺 Ŀ�� �׸���

    float cursorX = 640.0; // ���÷� 640.0���� ����
    float cursorY = 300.0; // ���÷� 300.0���� ����
    glPushMatrix();
    glTranslatef(cursorX, cursorY, 0.0);
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

    // �� �׸���
    for (int i = 0; i < numEggs; ++i) {
        eggs[i].y += 1.0; // ���� ���� �̵�
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // ����ȫ��
    }

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }


    glPopMatrix(); // �� �� �� ������ ��鿡 ������ ��.

}









void drawScene4() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // ù ��° ����� ������ ���⿡ ����
    // �� �׸���
    drawGround(windowWidth, windowHeight);

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    for (int i = 0; i < numEggs; ++i) {
        eggs[i].y += 1.0; // ���� ���� �̵�

        // ���� �� �Ʒ��� �򸮵��� �׸���
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // ����ȫ��
        if (eggs[1].y < 400.0) {
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


    // ���Ƹ� �׸���
    glPushMatrix();
    drawChick();
    glPopMatrix();

    // 0.5�� ���� ���� �׸���

    static int fireworksTimer = 0;


    if (fireworksTimer < 15) {
        for (int i = 0; i < 5; ++i) {
            float xpos = chick.x; // ���Ƹ��� ��ġ�� ����
            float ypos = chick.y;

            drawFirework(xpos, ypos);
        }
        fireworksTimer++;
    }


    // ����ȫ�� ���� ���������� ����
    eggs[1].y = 1000.0; // ���Ƿ� ���� ȭ�� ������ �̵�

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }
}





void drawScene6() {

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // ���� �ĴڰŸ��� �ִϸ��̼�
    wingAngle = 800.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 0.0174533; // �������� ��ȯ5); // * �� �κ��� �ĴڰŸ��°���
    // sin ���� �� �� ���� �Ĵ�

    // �� �׸���
    drawGround(windowWidth, windowHeight);


    // ���Ƹ� �׸���
    glPushMatrix();
    glTranslatef(chick.x, chick.y, 0.0);
    glScalef(chick.scale, chick.scale, 1.0);
    drawChicken(0.0, 0.0, 1.0, wingAngle);  // wingAngle�� drawChicken �Լ��� ����
    drawEyeTouch(chick.x,chick.y,chick.scale);  // �� �ؿ� ����ġ �׸���
 

    // ���� �׸���
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
        // �̷��� ���Ƹ��� ������ �������� �ʴ´�
    }
   //drawFlower(flowerX, flowerY);
    glPopMatrix(); // �� �� �� ������ ��鿡 ������ ��.

    }




void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // ����Ʈ ����
    glViewport(0, 0, windowWidth, windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    switch (sceneIndex) {

    case 0:
        drawScene1();
        break;
    case 1:
        drawScene2();
        break;
        // �߰����� case ���� ���� �ٸ� ���鿡 ���� ó�� �߰�
        // case 2:
        //     drawScene3();
        //     break;
        // ...
     // ���� ��� ����


    case 2:
        drawScene3();
        break;

    case 3:
        drawScene4();
        break;
    case 4:
        drawScene5();
        break;
    case 5:
        drawScene6();
        break;

    default:
        break;
    }

    glutSwapBuffers();
}





void timer(int value) {
    // ���� �ð��� ���� ������ ��� ��ȯ
    sceneIndex = (sceneIndex + 1) % 8; // ����� �� ����
    // ��� ����� ����� ��� ó�� ������� ���ư���
    if (sceneIndex == 0) {
        glutPostRedisplay(); // ȭ���� �ٽ� �׸����� ��û
    }
    else {
        glutTimerFunc(1000, timer, 0);  // 1�� �Ŀ� ���� ������� ��ȯ
    }
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
       
        
        // ���� �������� �ִϸ��̼�
     //flowerY -= 1.0;

        // ���� ���ۺ��� ���� �ִϸ��̼�
    // flowerRotation += 1.0;


        glutPostRedisplay();
        glutTimerFunc(30, update, 0); // 30ms���� ������Ʈ ȣ��
    }
}






int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Cloud Animation");


    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // �������� �ݹ� ���
    glutTimerFunc(25, update, 0); // 25ms���� ������Ʈ ȣ��
    glutTimerFunc(1000, timer, 0);  // �ʱ⿡ Ÿ�̸� ȣ��


    glutMainLoop();
    return 0;
}