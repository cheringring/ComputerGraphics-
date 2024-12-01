#include <stdio.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>


//하령 

int startTime = 0;
bool isOrange = false;

bool yellowSquareVisible = true; // 초기에 노란색 네모가 보이도록 설정

int sceneIndex = 0;
float headOffset = 0.0; // 머리의 y 축 오프셋 값
int flag = 0;

float transX = 50.0f;
float transY = -10.0f;


//체은 


int windowWidth = 1280;
int windowHeight = 720;

float carX = 0.0;

bool isScene1 = true;


// 구름의 정보를 담는 구조체
struct Cloud {
    float x, y; // 구름의 현재 위치
    float speed; // 구름의 이동 속도
};


struct Egg {
    float x, y; // 알의 현재 위치
    float angle; // 알의 흔들림의 진폭

};


struct Chicken {
    float x;
    float y;
    float scale;
    bool visible;
};


Chicken chick;

const int numClouds = 8; // 구름의 갯수
Cloud clouds[numClouds]; // 구름 배열


const int numEggs = 3; // 알의 갯수
Egg eggs[numEggs]; // 알 배열



float angleX = 0.0f;
float angleY = 0.0f;
float wingAngle = 0.0f;

float flowerX = 0.0;  // 꽃의 초기 x 좌표
float flowerY = 400.0;  // 꽃의 초기 y 좌표
float scaleFactor = 1.0;


GLfloat sunRadius = 20.0;  // 해의 반지름
GLfloat sunSpeed = 0.6;  // 해가 이동하는 속도
GLfloat sunX = 0.0f;
GLfloat sunY = 0.0f;





//하령 
void toggleWindow(int value) {
    flag++;
    glutPostRedisplay(); // 화면 다시 그리기 요청
    glutTimerFunc(500, toggleWindow, 0); // 0.5초 간격으로 자기 자신을 호출하여 반복
}//장면2의 파란 모니터 깜빡거림






//체은

void angletimer(int value) {

    wingAngle = 30.0f * sin(angleY * 3.1415926 / 180.0); // 날개 각도를 sin 함수를 사용하여 변경

    angleX += 2.0f;
    angleY += 1.0f;
    glutPostRedisplay(); // 화면 갱신 요청
    glutTimerFunc(16, angletimer, 0); // 16 밀리초마다 타이머 호출
}


// OpenGL 초기화 함수
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
    glColor3f(1.0, 1.0, 0.0);  // 노란색
    glScalef(3.0, 3.0, 1.0);  // 크기를 조절할 매개변수 scale 적용

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
    static GLfloat startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0; // 초 단위로 변환
    GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0; // 초 단위로 변환
    GLfloat elapsedTime = currentTime - startTime;

    // 10초 동안 움직임
    if (elapsedTime <= 10.0) {
        GLfloat sunX = sunSpeed * elapsedTime * 40;
        GLfloat sunY = glutGet(GLUT_WINDOW_HEIGHT) / 2.0 - 0.1 * sunSpeed * elapsedTime * elapsedTime;

        // 해 그리기
        drawSun(sunX, sunY);
    }
}


void drawCar(float x, float y) {
 

    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(40.0,30.0, 1.0);  // 크기를 조절할 매개변수 scale 적용

    // 차체
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0); // 빨간색
    glVertex2f(0.0, 0.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(2.5, 1.0);
    glVertex2f(2.5, 2.0);
    glVertex2f(0.0, 2.0);
    glEnd();

    // 바퀴
    glColor3f(0.0, 0.0, 0.0); // 검은색
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


//새싹
void drawSprout(float x, float y){


    glPushMatrix();

    // 특정 위치로 이동 적용
    glTranslatef(x, y, 0.0);
    // 줄기 그리긔
    glLineWidth(5.0f);  // 라인의 두께 설정
    glColor3f(0.5f, 0.8f, 0.5f);  // 연두색
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);  // 시작점
    glVertex2f(0.0, -50.0);     // 끝점
    glEnd();



    // 왼쪽 잎

    glColor3f(0.5, 0.8, 0.5);  // 연두색
 
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-30.0, 50.0);
    glVertex2f(-35.0, 30.0);
    glEnd();

    // 오른쪽 잎

    glColor3f(0.5, 0.8, 0.5);  // 연두
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

    // 줄기 그리기
    glColor3f(0.5f, 0.3f, 0.1f);  // 갈색
    glBegin(GL_POLYGON);
    glVertex2f(60.0, 0.0);
    glVertex2f(84.0, 0.0);
    glVertex2f(84.0, 120.0);
    glVertex2f(60.0, 120.0);
    glEnd();

    // 잎 그리기
    glColor3f(0.0, 0.5, 0.0); // 잎색
    glBegin(GL_POLYGON);
    glVertex2f(24.0, 120.0);
    glVertex2f(120.0, 120.0);
    glVertex2f(72.0, 240.0);
    glEnd();

    glPopMatrix();
}

//벚꽃
void drawsakuraTree(float x, float y,float scale) {



    glPushMatrix();
    glTranslatef(x, y, 0.0);
   glScalef(scale, scale, 1.0);  // 크기를 조절할 매개변수 scale 적용



    glColor3f(0.5, 0.5, 0.5); // 연회색
    glBegin(GL_POLYGON);
    glVertex2f(60.0, 0.0);
    glVertex2f(84.0, 0.0);
    glVertex2f(84.0, 120.0);
    glVertex2f(60.0, 120.0);
    glEnd();

    // 잎 그리기
    glColor3f(1.0f, 0.6f, 0.8f);  // 연한 분홍색
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
  
    
    
    // 중심 원
    flowerCircle(0.0, 0.0, flowerSize, 30);
    glColor3f(1.0, 1.0, 0.0);  // 노란색

    // 꽃잎 그리기
    for (int i = 0; i < 5; ++i) {
        glColor3f(1.0, 0.6, 0.8);
        float angle = i * (360.0f / 5);
        float petalX = flowerSize * 0.5f * std::cos(angle * 3.1415926f / 180.0);
        float petalY = flowerSize * 0.5f * std::sin(angle * 3.1415926f / 180.0);

        glPushMatrix();
        glTranslatef(x, y, 0.0);
        glTranslatef(petalX, petalY, 0.0);
        glRotatef(30.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.002), 0, 0, 1); // 추가된 떨어지는 효과
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

        // 여러 세그먼트로 나누어 선을 더 부드럽게 만듦
        for (int j = 0; j <= maxSegments; ++j) {
            float t = j / static_cast<float>(maxSegments);
            float tx = (1 - t) * x1 + t * x2;
            float ty = (1 - t) * y1 + t * y2;

            // 랜덤한 선 두께
            glLineWidth((rand() % 5) + 2.0);
            // 랜덤한 선 색상
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
    glClearColor(0.7, 0.9, 1.0, 1.0); // 하늘색 배경
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


    // 각 구름의 초기 위치와 속도 설정
    for (int i = 0; i < numClouds; ++i) {
        clouds[i].x = static_cast<float>(rand() % 1280);
        clouds[i].y = static_cast<float>(rand() % 360 + 300);
        clouds[i].speed = static_cast<float>(rand() % 5 + 1) * 0.1;
    }
    // 각 알의 초기 위치, 속도, 흔들림 설정

    eggs[0].x = 400.0;
    eggs[1].x = 640.0;
    eggs[2].x = 880.0;

    for (int i = 0; i < numEggs; ++i) {
        eggs[i].y = 300.0; // 땅 바로 위에 위치
        eggs[i].angle = static_cast<float>(rand() % 360);


    }
    // 병아리 초기 위치 및 크기 설정
    chick.x = 640.0;
    chick.y = 300.0;
    chick.scale = 400.0;
    chick.visible = true;

}





void drawChicken(float x, float y, float scale, float wingAngle) {

    // 좌표를 출력하거나 로그에 남기기
    printf("병아리 좌표: (%f, %f)\n", x, y);

    // 특정 위치에서만 변환을 적용하기 위해 Push Matrix
    glPushMatrix();



    // 특정 위치로 이동 및 회전 적용
    glTranslatef(x, y, 0.0);
    glScalef(scale, scale, 1.0); // 이거 시발 드디어 찾았다 이거때문에 병아리 안보였다.





    // 몸
    glColor3f(1.0, 1.0, 0.5);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.1415926 / 180.0;
        float px = 0.25 * cos(angle);
        float py = 0.2 * sin(angle);
        glVertex2f(px, py);
    }
    glEnd();



    // 하늘색 눈  (왼쪽) 
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

    // 눈 (왼쪽)
    glColor3f(1.0, 1.0, 1.0); // 흰색
    drawCircle(-0.057, 0.13, 0.008, 480);

    // 하늘색 눈 (오른쪽)
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

    // 눈 (오른쪽)
    glColor3f(1.0, 1.0, 1.0); // 흰색
    drawCircle(0.044, 0.13, 0.008, 480); // 네번지 인자 가로 길이 , 세번째는 크기


    // 부리
    glColor3f(1.0, 0.5, 0.0); // 주황색
    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.02, 0.0);
    glVertex2f(-0.02, 0.0);
    glVertex2f(0.0, -0.05);
    glEnd();
    glPopMatrix();

    // 날개 (왼쪽)
    glColor3f(1.0, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(-0.18, 0.044, 0.0);
    glTranslatef(0.0, 0.025, 0.0);
    glScalef(1.2, 1.2, 1.0);
    glRotatef(86.0 + wingAngle, 0.0, 0.0, 1.0); // 날개 각도 추가
    glBegin(GL_POLYGON);
    glVertex2f(-0.15, 0.02);
    glVertex2f(-0.1, 0.14);
    glVertex2f(-0.05, 0.02);
    glEnd();
    glPopMatrix();


    // 날개 (오른쪽)
    glColor3f(1.0, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(0.18, 0.044, 0.0);
    glTranslatef(0.0, 0.025, 0.0);
    glScalef(1.2, 1.2, 1.0);
    glRotatef(-86.0 - wingAngle, 0.0, 0.0, 1.0); // 날개 각도 추가
    glBegin(GL_POLYGON);
    glVertex2f(0.15, 0.02);
    glVertex2f(0.1, 0.14);
    glVertex2f(0.05, 0.02);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

// 인수인계 받기 ^^)
void drawChick() {
    drawChicken(chick.x, chick.y, chick.scale, wingAngle);
}


//하려고 했는데 못 쓴 코드
void drawChickenFoot(float x, float y, float toeLength) {

    glColor3f(1.0, 1.0, 0.0);

    // 라인 크기 키우기
    glLineWidth(30.0);
    glBegin(GL_LINES);

    glVertex2f(x, y);
    glVertex2f(x + toeLength * cos(45.0 * 3.1415926 / 180.0), y + toeLength * sin(45.0 * 3.1415926 / 180.0));


    glVertex2f(x, y);
    glVertex2f(x + toeLength * cos(90.0 * 3.1415926 / 180.0), y + toeLength * sin(90.0 * 3.1415926 / 180.0));

    glVertex2f(x, y);
    glVertex2f(x + toeLength * cos(135.0 * 3.1415926 / 180.0), y + toeLength * sin(135.0 * 3.1415926 / 180.0));

    glEnd();
    // 라인 크기 복원
 
}


void drawCursor() {


    glPushMatrix();  // 현재 변환 상태 저장
    glTranslatef(0.0, -20.0, 0.0);  // 아래로 이동
    glRotatef(30.0, 0.0, 0.0, 1.0);  // 왼쪽으로 20도 회전

    glLineWidth(10.0);

    // 삼각형 테두리 그리기 (검은색)
    glColor3f(0.0, 0.0, 0.0);  // 검은색 테두리
    glBegin(GL_LINE_LOOP);
    glVertex2f(-15.0, -15.0);  // 왼쪽 아래
    glVertex2f(0.0, 40.0);      // 위쪽 꼭지점
    glVertex2f(15.0, -15.0);   // 오른쪽 아래
    glEnd();

    // 사각형 테두리 그리기 (검은색)
    glBegin(GL_LINE_LOOP);
    glVertex2f(-5.0, -40.0);
    glVertex2f(5.0, -40.0);
    glVertex2f(5.0, 0.0);
    glVertex2f(-5.0, 0.0);
    glEnd();

    // 삼각형 내부 흰색으로 그리기
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);  // 흰색
    glVertex2f(0.0, 40.0);      // 위쪽 꼭지점
    glVertex2f(-15.0, -15.0);  // 왼쪽 아래
    glVertex2f(15.0, -15.0);   // 오른쪽 아래
    glEnd();

    // 사각형 내부 흰색으로 그리기
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);  // 흰색
    glVertex2f(-5.0, -40.0);
    glVertex2f(5.0, -40.0);
    glVertex2f(5.0, 0.0);
    glVertex2f(-5.0, 0.0);
    glEnd();

    glPopMatrix();  // 변환 이전 상태로 복구

}


void drawGround(int windowWidth, int windowHeight) {
    glColor3f(0.6, 0.4, 0.2); // 갈색 땅색
    glBegin(GL_QUADS);
    glVertex2f(0.0, 0.0);
    glVertex2f(windowWidth, 0.0);
    glVertex2f(windowWidth, windowHeight / 3); // 땅의 높이는 창의 1/3로 설정
    glVertex2f(0.0, windowHeight / 3);
    glEnd();
}



void drawEgg(float x, float y, float angle, float r, float g, float b) {

    // 좌표를 출력하거나 로그에 남기기
    printf("알 좌표: (%f, %f)\n", x, y);

    glColor3f(r, g, b); // 알 색상



    // 특정 위치에서만 변환을 적용하기 위해 Push Matrix
    glPushMatrix();



    // 특정 위치로 이동 및 회전 적용
    glTranslatef(x, y, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);


    glBegin(GL_POLYGON);
    // 원 모양의 알 그리기
    for (int i = 0; i < 360; i += 10) {
        float currentAngle = i * 3.141592 / 180.0;
        float xpos = 50.0 * cos(currentAngle);
        float ypos = 60.0 * sin(currentAngle);
        glVertex2f(xpos, ypos);
    }

    glEnd();

    // 검은색 테두리를 그리기 위해 반지름을 조금 키우고 다시 원 그리기
    glColor3f(0.0, 0.0, 0.0); // 검은색 테두리
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 10) {
        float currentAngle = i * 3.141592 / 180.0;
        float xpos = 50.0 * cos(currentAngle);
        float ypos = 60.0 * sin(currentAngle);
        glVertex2f(xpos, ypos);
    }
    glEnd();


    // 변환 이전 상태로 복구하기 위해 Pop Matrix
    glPopMatrix();

}


void drawCloud(float x, float y) {
    glColor3f(1.0, 1.0, 1.0); // 흰색 구름색

    // 세 개의 동그라미를 간격을 두고 그리기
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


//하령 

void hadrawScene1() {


    // 먼저 에러 체크
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "하령장면1 발생: %s\n", gluErrorString(error));
    }
    printf("하령 Draw Scene 1\n");  // 디버깅을 위한 로그


    float x, y;
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT); // 버퍼 지우기
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //(0,0,0)에서 (0,0, -1)를 보겠다.
    glLoadIdentity();
    // 주황색 영역 그리기 (세로로 1/5 부분)
    glColor3f(1.0, 0.5, 0.0); // 주황색
    glRectf(0, 0, 1280, 720 / 5); // 윈도우의 세로 방향 1/5 부분
    // 노란색 영역 그리기 (나머지 부분)
    glColor3f(1.0, 1.0, 0.0); // 노란색
    glRectf(0, 720 / 5, 1280, 720); // 윈도우의 세로 방향 나머지 부분
    // 의자 방석 그리기 (직사각형)
    glColor3f(0.545, 0.271, 0.075); // 갈색
    glBegin(GL_POLYGON);
    glVertex2f(200, 228); // 위치 수정
    glVertex2f(300, 228); // 위치 수정
    glVertex2f(300, 188); // 위치 수정
    glVertex2f(200, 188); // 위치 수정
    glEnd();
    // 의자 다리 만들기(1)
    glColor3f(0.545, 0.271, 0.075); // 갈색
    glBegin(GL_POLYGON);
    glVertex2f(300, 128); // 위치 수정
    glVertex2f(300, 188); // 위치 수정
    glVertex2f(280, 188); // 위치 수정
    glVertex2f(280, 128); // 위치 수정
    glEnd();
    // 의자 다리 만들기(2)
    glColor3f(0.545, 0.271, 0.075); // 갈색
    glBegin(GL_POLYGON);
    glVertex2f(200, 128); // 위치 수정
    glVertex2f(200, 188); // 위치 수정
    glVertex2f(220, 188); // 위치 수정
    glVertex2f(220, 128); // 위치 수정
    glEnd();
    // 의자 등받이 그리기 (타원형 근사)
    glColor3f(0.545, 0.271, 0.075); // 갈색
    glBegin(GL_POLYGON);
    float radiusX = 40; // 타원의 반지름 설정
    float radiusY = 80;
    for (float angle = 1.0; angle < 360.0; angle += 1.0) {
        x = 200 + radiusX * cos(angle * 3.14159265 / 180.0);
        y = 260 + radiusY * sin(angle * 3.14159265 / 180.0);
        glVertex2f(x, y);
    }
    glEnd();
    // 사람 상체 그리기 (원과 직사각형)
    glColor3f(0.0, 0.0, 0.0); // 검은색
    // 머리 (원)
    glBegin(GL_POLYGON);
    float headRadius = 40; // 머리의 반지름 설정 (두 배로 키움)
    for (float angle = 1.0; angle < 360.0; angle += 1.0) {
        x = 280 + headRadius * cos(angle * 3.14159265 / 180.0);
        y = 330 + headRadius * sin(angle * 3.14159265 / 180.0) + headOffset;
        glVertex2f(x, y);
    }
    glEnd();
    // 몸통 (직사각형)
    glBegin(GL_POLYGON);
    glVertex2f(242, 300); // 위치 수정
    glVertex2f(268, 300); // 위치 수정
    glVertex2f(268, 200); // 위치 수정
    glVertex2f(242, 200); // 위치 수정
    glEnd();
    //팔 (직사각형)
    glBegin(GL_POLYGON);
    glVertex2f(350, 250); // 위치 수정
    glVertex2f(268, 270); // 위치 수정
    glVertex2f(268, 250); // 위치 수정
    glVertex2f(350, 270); // 위치 수정
    glEnd();
    //다리(1)
    glBegin(GL_POLYGON);
    glVertex2f(310, 200); // 위치 수정
    glVertex2f(268, 200); // 위치 수정
    glVertex2f(268, 220); // 위치 수정
    glVertex2f(310, 220); // 위치 수정
    glEnd();
    //다리(2)
    glBegin(GL_POLYGON);
    glVertex2f(310, 150); // 위치 수정
    glVertex2f(298, 150); // 위치 수정
    glVertex2f(298, 220); // 위치 수정
    glVertex2f(310, 220); // 위치 수정
    glEnd();
    // 오른쪽 창문 그리기
    glColor3f(0.529, 0.808, 0.922); // 파란색
    glBegin(GL_POLYGON);
    glVertex2f(800, 660);
    glVertex2f(1120, 660);
    glVertex2f(1120, 420);
    glVertex2f(800, 420);
    glEnd();
    // ...
    glColor3f(0.545, 0.271, 0.075); // 갈색
    glLineWidth(5); // 선 두께 설정
    glBegin(GL_LINE_LOOP);
    glVertex2f(800, 660);
    glVertex2f(1120, 660);
    glVertex2f(1120, 420);
    glVertex2f(800, 420);
    glEnd();
    // 책상 그리기
    glColor3f(0.529, 0.808, 0.922);
    glBegin(GL_POLYGON);
    glVertex2f(330, 225);
    glVertex2f(430, 225);
    glVertex2f(430, 240);
    glVertex2f(330, 240);
    glEnd();
    // ...
    glColor3f(0.545, 0.271, 0.075); // 갈색
    glBegin(GL_POLYGON);
    glVertex2f(370, 225);
    glVertex2f(410, 225);
    glVertex2f(410, 128);
    glVertex2f(370, 128);
    glEnd();
    //마우스
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(325, 250);
    glVertex2f(345, 250);
    glVertex2f(345, 240);
    glVertex2f(325, 240);
    glEnd();
    //컴퓨터
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
    // 침대 그리기
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
    glColor3f(0.0, 0.0, 0.0); // 검은색
    glLineWidth(3); // 선 두께 설정
    glBegin(GL_LINE_LOOP);
    glVertex2f(1625, 245);
    glVertex2f(825, 245);
    glVertex2f(925, 120);
    glVertex2f(1625, 100);
    glEnd();
    glColor3f(0.0, 0.0, 0.0); // 검은색
    glLineWidth(3); // 선 두께 설정
    glBegin(GL_LINE_LOOP);
    glVertex2f(1625, 50);
    glVertex2f(1625, 50);
    glVertex2f(1625, 50);
    glVertex2f(825, 245);
    glVertex2f(825, 155);
    glVertex2f(925, 50);
    glEnd();
    // ...
    glFlush(); // 화면에 출력
    glPopMatrix();

}

void hadrawScene2() {


    // 먼저 에러 체크
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "하령 장면2 발생: %s\n", gluErrorString(error));
    }
    printf("하령 Draw Scene 2\n");  // 디버깅을 위한 로그


    float x, y;
    glClear(GL_COLOR_BUFFER_BIT); // 버퍼 지우기
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // 노란색으로 전체 윈도우 채우기
    glColor3f(1.0, 1.0, 0.0); // 노란색
    glRectf(0, 0, 1280, 720); // 전체 윈도우 크기로 사각형 그리기
    // 모니터
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(320, 200);
    glVertex2f(950, 200);
    glVertex2f(950, 610);
    glVertex2f(320, 610);
    glEnd();
    // 화면창
    if (flag % 2 == 0) {
        glColor3f(0.0, 0.0, 1.0); // 파란색
    }
    else {
        glColor3f(1.0, 1.0, 1.0); // 흰색
    }
    glBegin(GL_POLYGON);
    glVertex2f(330, 210);
    glVertex2f(940, 210);
    glVertex2f(940, 590);
    glVertex2f(330, 590);
    glEnd();
    // 검은색 원 그리기
    glColor3f(0.0, 0.0, 0.0); // 검은색
    glBegin(GL_POLYGON);
    float blackCircleRadius = 80; // 원의 반지름 설정
    int segments = 100; // 원을 얼마나 매끄럽게 그릴지 결정하는 세그먼트 수
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float cx = 620 + blackCircleRadius * cosf(theta);
        float cy = 250 + blackCircleRadius * sinf(theta);
        glVertex2f(cx, cy);
    }
    glEnd();
    // 갈색 타원형 그리기
    glColor3f(0.545, 0.271, 0.075); // 갈색
    glBegin(GL_POLYGON);
    float radiusX = 160; // 타원의 반지름 설정
    float radiusY = 200;
    for (float angle = 1.0; angle < 360.0; angle += 1.0) {
        x = 620 + radiusX * cos(angle * 3.14159265 / 180.0);
        y = 00 + radiusY * sin(angle * 3.14159265 / 180.0);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush(); // 화면에 출력
}

void hadrawScene3() {


    // 먼저 에러 체크
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "하령 장면3 발생: %s\n", gluErrorString(error));
    }
    printf(" 하령 Draw Scene 1\n");  // 디버깅을 위한 로그


    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT); // 버퍼 지우기
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 초록색 영역 그리기 (세로로 1/5 부분)
    glColor3f(0.0, 1.0, 0.0); // 초록색
    glRectf(0, 0, windowWidth, windowHeight / 5); // 윈도우의 세로 방향 1/5 부분

    // 파란색 영역 그리기 (나머지 부분)
    glColor3f(0.529, 0.808, 0.922); // 파란색
    glRectf(0, windowHeight / 5, windowWidth, windowHeight); // 윈도우의 세로 방향 나머지 부분
    // 초록색과 파란색 경계에 검은 선 그리기
    glColor3f(0.0, 0.0, 0.0); // 검은색
    glLineWidth(2.0); // 선 두께 설정

    // 위쪽 경계선
    glBegin(GL_LINES);
    glVertex2f(0, windowHeight / 5);
    glVertex2f(windowWidth, windowHeight / 5);
    glEnd();


    // 중앙에 노란색 직사각형 그리기
    glColor3f(1.0, 1.0, 0.0); // 노란색
    int squareWidth = 200; // 네모 가로 길이
    int squareHeight = 100; // 네모 세로 길이
    int squareX = (windowWidth - squareWidth) / 2; // 중앙 X 위치 계산
    int squareY = (windowHeight - squareHeight) / 2; // 중앙 Y 위치 계산

    // 테두리 그리기
    glLineWidth(2.0); // 테두리 두께 설정
    glColor3f(0.0, 0.0, 0.0); // 검은색 테두리
    glBegin(GL_LINE_LOOP); // 사각형 테두리 시작
    glVertex2f(squareX, squareY); // 좌상단
    glVertex2f(squareX + squareWidth, squareY); // 우상단
    glVertex2f(squareX + squareWidth, squareY + squareHeight); // 우하단
    glVertex2f(squareX, squareY + squareHeight); // 좌하단
    glEnd(); // 사각형 테두리 종료

    int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    if (startTime == 0) {
        startTime = elapsedTime;
    }

    int timeDiff = elapsedTime - startTime;
    int orangeSwitchInterval = 2000; // 2초

    if (timeDiff > orangeSwitchInterval) {
        isOrange = !isOrange;
        startTime = elapsedTime;
    }

    // 내부 색칠하기
    glColor3f(1.0, 1.0, 0.0); // 노란색
    glBegin(GL_QUADS); // 사각형 시작
    glVertex2f(squareX, squareY); // 좌상단
    glVertex2f(squareX + squareWidth, squareY); // 우상단
    glVertex2f(squareX + squareWidth, squareY + squareHeight); // 우하단
    glVertex2f(squareX, squareY + squareHeight); // 좌하단
    glEnd(); // 사각형 종료
    if (isOrange) {
        glColor3f(1.0, 0.5, 0.0); // 주황색
    }
    else {
        glColor3f(1.0, 1.0, 0.0); // 노란색
    }
    glBegin(GL_QUADS); // 사각형 시작
    glVertex2f(squareX, squareY);
    glVertex2f(squareX + squareWidth, squareY);
    glVertex2f(squareX + squareWidth, squareY + squareHeight);
    glVertex2f(squareX, squareY + squareHeight);
    glEnd(); // 사각형 종료

    // "Start" 텍스트 출력
    glColor3f(0.0, 0.0, 0.0); // 검은색
    glRasterPos2i(squareX + squareWidth / 2 - 25, squareY + squareHeight / 2); // 텍스트 위치 조정
    void* font = GLUT_BITMAP_HELVETICA_18; // 글꼴과 크기 선택
    const char* text = "Start"; // 텍스트
    for (int i = 0; text[i] != '\0'; ++i) {
        glutBitmapCharacter(font, text[i]); // 글자 하나씩 출력
    }

    // ... (삼각형, 화살표 그리기)
    glColor3f(0.0, 0.0, 0.0); // 검은색
    glBegin(GL_LINE_LOOP);
    glVertex2f(windowWidth / 2 + transX, windowHeight / 2 + 23 + transY); // 상단 꼭지점
    glVertex2f(windowWidth / 2 - 17 + transX, windowHeight / 2 - 28 + transY); // 좌하단
    glVertex2f(windowWidth / 2 + 17 + transX, windowHeight / 2 - 28 + transY); // 우하단
    glEnd();

    // 화살표 네모
    glColor3f(0.0, 0.0, 0.0); // 검은색
    glBegin(GL_LINE_LOOP);
    glVertex2f(windowWidth / 2 - 10 + transX, windowHeight / 2 - 28 + transY); // 좌상단
    glVertex2f(windowWidth / 2 + 10 + transX, windowHeight / 2 - 28 + transY); // 우상단
    glVertex2f(windowWidth / 2 + 10 + transX, windowHeight / 2 - 48 + transY); // 우하단
    glVertex2f(windowWidth / 2 - 10 + transX, windowHeight / 2 - 48 + transY); // 좌하단
    glEnd();

    glColor3f(1.0, 1.0, 1.0); // 흰색
    glBegin(GL_TRIANGLES);
    glVertex2f(windowWidth / 2 + transX, windowHeight / 2 + 23 + transY); // 상단 꼭지점
    glVertex2f(windowWidth / 2 - 17 + transX, windowHeight / 2 - 28 + transY); // 좌하단
    glVertex2f(windowWidth / 2 + 17 + transX, windowHeight / 2 - 28 + transY); // 우하단
    glEnd();//화살표 코드
    glColor3f(1.0, 1.0, 1.0); // 흰색
    glBegin(GL_QUADS);
    glVertex2f(windowWidth / 2 - 10 + transX, windowHeight / 2 - 28 + transY); // 좌상단
    glVertex2f(windowWidth / 2 + 10 + transX, windowHeight / 2 - 28 + transY); // 우상단
    glVertex2f(windowWidth / 2 + 10 + transX, windowHeight / 2 - 48 + transY); // 우하단
    glVertex2f(windowWidth / 2 - 10 + transX, windowHeight / 2 - 48 + transY); // 좌하단
    glEnd();
    glPopMatrix();
}



//체은
void drawScene1() {
    // 첫 번째 장면 그리기 코드는 여기에 작성
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);


    // 먼저 에러 체크
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "장면1 발생: %s\n", gluErrorString(error));
    }
    printf("Draw Scene 1\n");  // 디버깅을 위한 로그




    // 땅 그리기
    drawGround(windowWidth, windowHeight);

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }



    float groundHeight = windowHeight / 3 + 30.0;  // 땅의 높이 (1/3로 변경)
    float sproutSpacing = 250.0f;  // 새싹 간격


    // 새싹 그리기
    for (int i = 0; i < 4; ++i) {
        float sproutX = 640.0 + (i - 1.5) * sproutSpacing;  // 알 좌표를 기준으로 중앙 정렬되도록 변경
        float sproutY = groundHeight;


        drawSprout(sproutX, sproutY);
    }

    // 알 그리기
    // 알의 위치 배열 정의


    for (int i = 0; i < numEggs; ++i) {

        drawEgg(eggs[0].x, eggs[0].y, 15.0 * sin(eggs[0].angle), 1.0, 1.0, 0.0); // 노란
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // 연분홍색
        drawEgg(eggs[2].x, eggs[2].y, 15.0 * sin(eggs[2].angle), 0.6, 0.4, 0.8); // 연보라색);
        eggs[i].angle += 0.1; // 흔들림 각도 업데이트
    }
    glPopMatrix();
}
    


void drawScene2() {
 
    // 두 번째 장면 그리기 코드는 여기에 작성
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);


    // 먼저 에러 체크
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "장면2 발생: %s\n", gluErrorString(error));
    }
    printf("Draw Scene 2\n");  // 디버깅을 위한 로그



    // 땅 그리기
    drawGround(windowWidth, windowHeight);

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    //새싹 그리기
    float groundHeight = windowHeight / 3 + 30.0;  // 땅의 높이 (1/3로 변경)
    float sproutSpacing = 250.0f;  // 새싹 간격


    // 새싹 그리기
    for (int i = 0; i < 4; ++i) {
        float sproutX = 640.0 + (i - 1.5) * sproutSpacing;  // 알 좌표를 기준으로 중앙 정렬되도록 변경
        float sproutY = groundHeight;


        drawSprout(sproutX, sproutY);
    }


    // 알 그리기
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[0].x, eggs[0].y, 15.0 * sin(eggs[0].angle), 1.0, 1.0, 0.0); // 노란색
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // 연분홍색
        drawEgg(eggs[2].x, eggs[2].y, 15.0 * sin(eggs[2].angle), 0.6, 0.4, 0.8); // 연보라색);
        eggs[i].angle += 0.2; // 흔들림 각도 업데이트
    }

    // 마우스 커서 그리기

    float cursorX = 640.0; // 예시로 640.0으로 지정
    float cursorY = 300.0; // 예시로 300.0으로 지정
    glPushMatrix();
    glTranslatef(cursorX, cursorY, 0.0);
    glScalef(scaleFactor, scaleFactor, 1.0);  // 크기 변경
    drawCursor();
    glPopMatrix();

}


void drawScene3() {

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 첫 번째 장면의 내용을 여기에 복사
    // 
    // 
    // 
    // 땅 그리기
    drawGround(windowWidth, windowHeight);

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }
    //새싹 그리기
    float groundHeight = windowHeight / 3 + 30.0;  // 땅의 높이 (1/3로 변경)
    float sproutSpacing = 250.0f;  // 새싹 간격


    // 새싹 그리기
    for (int i = 0; i < 4; ++i) {
        float sproutX = 640.0 + (i - 1.5) * sproutSpacing;  // 알 좌표를 기준으로 중앙 정렬되도록 변경
        float sproutY = groundHeight;


        drawSprout(sproutX, sproutY);
    }

    // 알 그리기
    for (int i = 0; i < numEggs; ++i) {
        eggs[i].y += 1.0; // 알을 위로 이동
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // 연분홍색
    }

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    
}









void drawScene4() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 먼저 에러 체크
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "체은 장면4 발생: %s\n", gluErrorString(error));
    }
    printf("체은 Draw Scene 4 \n");  // 디버깅을 위한 로그


    // 첫 번째 장면의 내용을 여기에 복사
    // 땅 그리기
    drawGround(windowWidth, windowHeight);

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    //새싹 그리기
    float groundHeight = windowHeight / 3 + 30.0;  // 땅의 높이 (1/3로 변경)
    float sproutSpacing = 250.0f;  // 새싹 간격


    // 새싹 그리기
    for (int i = 0; i < 4; ++i) {
        float sproutX = 640.0 + (i - 1.5) * sproutSpacing;  // 알 좌표를 기준으로 중앙 정렬되도록 변경
        float sproutY = groundHeight;


        drawSprout(sproutX, sproutY);
    }

    for (int i = 0; i < numEggs; ++i) {
        eggs[i].y += 1.0; // 알을 위로 이동

        // 폭죽 알 아래로 깔리도록 그리기

        if (eggs[1].y < 400.0) {
            drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // 연분홍색

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

        // 땅 그리기
        drawGround(windowWidth, windowHeight);

        // 구름 그리기
        for (int i = 0; i < numClouds; ++i) {
            drawCloud(clouds[i].x, clouds[i].y);
        }

        //나무 그리기 
        float groundHeight = windowHeight / 3 ;  // 땅의 높이 (1/3로 변경)
        float objectSpacing = 300.0f;  // 간격

        
        for (int i = 0; i < 4; ++i) {
            float TreeX = 640.0 + (i - 1.7) * objectSpacing;  // 알 좌표를 기준으로 중앙 정렬되도록 변경
            float TreeY = groundHeight;

            drawTree(TreeX, TreeY); 

        }

        // 병아리 그리기
        glPushMatrix();
        drawChick();
        glPopMatrix();

        // 0.5초 동안 폭죽 그리기

        static int fireworksTimer = 0;


        if (fireworksTimer < 20) {
            for (int i = 0; i < 12; ++i) {
                float xpos = chick.x; // 병아리의 위치로 지정
                float ypos = chick.y;

                drawFirework(xpos, ypos);
            }
            fireworksTimer++;
        }


        // 구름 그리기
        for (int i = 0; i < numClouds; ++i) {
            drawCloud(clouds[i].x, clouds[i].y);
        }
    }





void drawScene6() {

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 날개 파닥거리기 애니메이션
    wingAngle = 700.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 0.0174533; // 라디안으로 변환5); // * 뒤 부분이 파닥거리는각도
    // sin 앞이 좀 더 빨리 파닥

     // 땅 그리기
    drawGround(windowWidth, windowHeight);


    //나무 그리기 
    float groundHeight = windowHeight / 3;  // 땅의 높이 (1/3로 변경)
    float objectSpacing = 300.0f;  // 간격


    for (int i = 0; i < 4; ++i) {
        float TreeX = 640.0 + (i - 1.7) * objectSpacing;  // 알 좌표를 기준으로 중앙 정렬되도록 변경
        float TreeY = groundHeight;

        drawTree(TreeX, TreeY);

    }
    // 병아리 그리기
    glPushMatrix();
    glTranslatef(chick.x, chick.y, 0.0);
    glScalef(chick.scale, chick.scale, 1.0);
    drawChicken(0.0, 0.0, 1.0, wingAngle);  // wingAngle을 drawChicken 함수에 전달
    glPopMatrix();





    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
        // 이러면 병아리가 구름에 가려지지 않는다
    }
}


  


void drawScene7() {


    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 날개 파닥거리기 애니메이션
    wingAngle = 700.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 0.0174533; // 라디안으로 변환5); // * 뒤 부분이 파닥거리는각도
    // sin 앞이 좀 더 빨리 파닥

     // 땅 그리기
    drawGround(windowWidth, windowHeight);


    //나무 그리기 
    float groundHeight = windowHeight / 3;  // 땅의 높이 (1/3로 변경)
    float objectSpacing = 300.0f;  // 간격



 
    //나무그리기 
        for (int i = 0; i < 4; ++i) {
            float TreeX = 640.0 + (i - 1.7) * objectSpacing;  // 알 좌표를 기준으로 중앙 정렬되도록 변경
            float TreeY = groundHeight;

            drawTree(TreeX, TreeY);

        }

        // 병아리 그리기
        glPushMatrix();
        glTranslatef(chick.x, chick.y, 0.0);
        glScalef(chick.scale, chick.scale, 1.0);
        drawChicken(0.0, 0.0, 1.0, wingAngle);  // wingAngle을 drawChicken 함수에 전달
        glPopMatrix();



        // 구름 그리기
        for (int i = 0; i < numClouds; ++i) {
            drawCloud(clouds[i].x, clouds[i].y);
            // 이러면 병아리가 구름에 가려지지 않는다
        }

        // 꽃이 떨어지는 위치 설정
        for (int i = 0; i < 60; ++i) {
            float flowerX = static_cast<float>(rand() % (2 * windowWidth) - windowWidth);
            float flowerY = static_cast<float>(rand() % (2 * windowHeight) - windowHeight);
            float rotationAngle = static_cast<float>(rand() % 360);
            float flowerSize = 40.0;


            float deltaTime = 0.0000001;  // 시간에 따른 이동량을 결정하는 변수

            // 꽃이 떨어지는 속도 조절
            flowerY -= deltaTime * 0.00000001;  // 여기서 값 조절 가능
            drawFlower(flowerX, flowerY, flowerSize);



    }
}



void drawScene8() {

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);


    // 땅 그리기
    drawGround(windowWidth, windowHeight);




        // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
        // 이러면 병아리가 구름에 가려지지 않는다
    }


    //나무 그리기 
    float groundHeight = windowHeight / 3;  // 땅의 높이 (1/3로 변경)
    float objectSpacing = 300.0f;  // 간격


    for (int i = 0; i < 4; ++i) {
        float TreeX = 640.0 + (i - 1.8) * objectSpacing;  // 알 좌표를 기준으로 중앙 정렬되도록 변경
        float TreeY = groundHeight;

        drawsakuraTree(TreeX, TreeY,1.5);
    }

    // 날개 파닥거리기 애니메이션
    wingAngle = 700.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 0.0174533; // 라디안으로 변환5); // * 뒤 부분이 파닥거리는각도
    // sin 앞이 좀 더 빨리 파닥
    float elapsedTime = glutGet(GLUT_ELAPSED_TIME) * 0.001;  // 초 단위로 변환
    float verticalOffset = 60.0 * sin(elapsedTime * 0.5);  // 위아래로 움직이는 offset

    glPushMatrix();
    // 병아리 그리기
    glTranslatef(chick.x, chick.y + verticalOffset, 0.0);
    glScalef(chick.scale, chick.scale, 1.0);
    drawChicken(0.0, 0.0, 1.0, wingAngle);  // wingAngle을 drawChicken 함수에 전달
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
    // 시간에 따라 차의 위치 계산
    GLfloat carAngle = fmod((carX + 1.5) / windowWidth * 360.0, 360.0);

    // 초기 배경색은 아주 연한 주황색
    GLfloat initialColor[3] = { 1.0, 0.8, 0.6 };  // 주황색

    // 배경색 변화를 위한 변수
    GLfloat backgroundColor[3];

    if (carAngle <= 85.0) {
        // 연한 주황색
        backgroundColor[0] = initialColor[0];
        backgroundColor[1] = initialColor[1];
        backgroundColor[2] = initialColor[2];
    }
    else if (carAngle <= 170.0) {
        // 연보라색
        backgroundColor[0] = 0.8;  // Red
        backgroundColor[1] = 0.6;  // Green
        backgroundColor[2] = 1.0;  // Blue
    }
    else {
        // 진한 남색
        backgroundColor[0] = 0.0;  // Red
        backgroundColor[1] = 0.0;  // Green
        backgroundColor[2] = 0.4;  // Blue
    }

    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0);

    updateSunPosition();

    // 땅 그리기
    drawGround(windowWidth, windowHeight/3.5);




    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
        // 이러면 병아리가 구름에 가려지지 않는다
    }


    //나무 그리기 
    float groundHeight = windowHeight /3.5;  // 땅의 높이 (1/4로 변경)
    float objectSpacing = 200.0f;  // 간격
    int numTrees = 8;

    for (int i = 0; i < numTrees; ++i) {
        float treeX = windowWidth / 2 + (i - numTrees / 2) * objectSpacing;  // 중앙 정렬
        float treeY = groundHeight;

        // 나무 크기를 조절
        drawsakuraTree(treeX, treeY-138.0, 0.8);
    }



    carX += 1.5;  // 이동 속도 및 방향
    printf("Car X: %f\n", carX);

    // 화면을 벗어나면 초기화
    if (carX > windowWidth) {
        carX = -2.5;  // 초기값 재설정
    }
    // 자동차 이동
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


    // 먼저 에러 체크
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "update 에러 발생: %s\n", gluErrorString(error));
    }

    // 여기에서 다른 초기화 및 업데이트 작업 수행

    // 모델뷰 행렬 초기화
    //glLoadIdentity();

    // 프레임을 지우는 작업
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // 구름 이동 업데이트
    for (int i = 0; i < numClouds; ++i) {
        clouds[i].x += clouds[i].speed;
        if (clouds[i].x > glutGet(GLUT_WINDOW_WIDTH)) {
            clouds[i].x = -50.0; // 화면 왼쪽으로 나가면 다시 오른쪽에서 시작
            clouds[i].y = static_cast<float>(rand() % 360 + 300);
        }
    }
    for (int i = 0; i < numEggs; ++i) {
        if (eggs[i].x > glutGet(GLUT_WINDOW_WIDTH)) {
            eggs[i].x = -50.0; // 화면 왼쪽으로 나가면 다시 오른쪽에서 시작
        }
    }

    scaleFactor += 0.01;  // 예시로 0.01씩 증가하도록 설정

    // scaleFactor가 일정 값 이상이 되면 다시 감소하도록 설정
    if (scaleFactor > 1.5) {
        scaleFactor = 1.0;
    }

    // 병아리 날개 파닥거리기 애니메이션
    wingAngle = 800.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 0.0174533;



    //하령 타이머
    headOffset = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01) * 5;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0); // 50ms마다 업데이트 호출


}


void timer(int value) {
    // 일정 시간이 지날 때마다 장면 전환
    sceneIndex = (sceneIndex+1) % 100; // 장면의 총 갯수

    printf("Timer: SceneIndex = %d\n", sceneIndex); // 디버깅을 위한 로그


    // 모든 장면을 재생한 경우 처음 장면으로 돌아가기
    if (sceneIndex ==100 ) {
        glutPostRedisplay(); // 화면을 다시 그리도록 요청
    }
    else {
        int sceneInterval;

       switch (sceneIndex) {
        case 0:
            sceneInterval = 1500;  
            break;
        case 1: //하령1
            sceneInterval = 3000;  
            break;
        case 2://하령2
            sceneInterval = 3000; 
            break;
        case 3://하령3
            sceneInterval = 3000;
            break;
        case 4: //체은1
            sceneInterval = 1500;  
            break;
        case 5: //체은2
            sceneInterval = 1500;  
            break;
        case 6: //체은3
            sceneInterval = 1500; 
            break;
        case 7: //체은4
            sceneInterval = 1500; 
            break;
        case 8:  //체은5
            sceneInterval = 1500;  
            break;
        case 9: //체은6
            sceneInterval = 1500;  
            break;
        case 10: //체은7
            sceneInterval = 1500;
            break;
        case 11: //체은8
            sceneInterval = 1500;
        case 12: //체은9
            sceneInterval = 9000;
     
        }


        glutTimerFunc(sceneInterval, timer, 0);
        glutPostRedisplay();
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    printf("Display: SceneIndex = %d\n", sceneIndex); // 디버깅을 위한 로그

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 뷰포트 설정
    glViewport(0, 0, windowWidth, windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);


    glMatrixMode(GL_MODELVIEW);


    switch (sceneIndex) {

    case 0:
        drawScene100(); // 앞 장면 안나오는 오류로 임시코드 
        break;
    case 1:
        hadrawScene1(); //하령 장면1
        break;
    case 2:
        hadrawScene2(); //하령 장면2
        break;
    case 3:
        hadrawScene3(); //하령 장면3
        break;
    case 4: 
        printf("Display: Calling drawScene1\n"); 
        drawScene1();//체은
        break;
    case 5:
        printf("Display: Calling drawScene2\n");
        drawScene2(); //체은
        break;
    case 6:
        printf("Display: Calling drawScene3\n");
        drawScene3(); //ㅊㅇ
        break;
    case 7:
        drawScene4(); //ㅊㅇ
        break;
    case 8:
        drawScene5(); //ㅊㅇ
        break;
    case 9:
        drawScene6(); //ㅊㅇ
        break;
    case 10:
        drawScene7(); //ㅊㅇ
        break;
    case 11:
        drawScene8();//ㅊㅇ
        break;
    case 12:
        drawScene9(); //ㅊㅇ
    default:
        break;
    }

    glutSwapBuffers();

}




    void reshape(int w, int h) {
        glViewport(0, 0, w, h); // 뷰포트 설정
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, w, 0, h); // 오쏘노메트릭 뷰 설정
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Cloud Animation");

    // 초기 에러 체크
    GLenum initError = glGetError();
    if (initError != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL 초기화 중 에러 발생: %s\n", gluErrorString(initError));
        return -1;
    }

    init();
    initOpenGL(); // OpenGL 초기화 함수

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // 리셰이프 콜백 등록
    glutTimerFunc(25, update, 0); // 25ms마다 업데이트 호출
    glutTimerFunc(0, timer, 0);  // 초기에 타이머 호출
    glutTimerFunc(500, toggleWindow, 0);

    glutMainLoop();
    return 0;
}