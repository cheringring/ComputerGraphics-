#include <GL/glut.h>
#include <cmath>
#include <ctime>




bool isScene1 = true;
int sceneIndex = 0; // 현재 장면 인덱스


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
float flowerY = 500.0;  // 꽃의 초기 y 좌표
float flowerRotation = 0.0;  // 꽃의 회전 각도



void angletimer(int value) {

    wingAngle = 30.0f * sin(angleY * 3.1415926 / 180.0); // 날개 각도를 sin 함수를 사용하여 변경

    angleX += 2.0f;
    angleY += 1.0f;
    glutPostRedisplay(); // 화면 갱신 요청
    glutTimerFunc(16, angletimer, 0); // 16 밀리초마다 타이머 호출
}



/*void drawPetal(float x, float y, float length) { //꽃잎그리기위함
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
    // 꽃 그리기 코드
    glColor3f(1.0, 0.0, 0.0);  // 빨간색 꽃잎
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(flowerRotation, 0.0, 0.0, 1.0);  // 꽃을 회전
    // 꽃잎 그리기
    drawPetal(0.0, 20.0, 30.0);  // 예시 값, 적절한 위치와 길이를 설정하세요
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

        // 랜덤한 선 색상
        glColor3f((rand() % 256) / 255.0, (rand() % 256) / 255.0, (rand() % 256) / 255.0);

        glBegin(GL_LINE_STRIP);

        // 여러 세그먼트로 나누어 선을 더 부드럽게 만듦
        for (int j = 0; j <= maxSegments; ++j) {
            float t = j / static_cast<float>(maxSegments);
            float tx = (1 - t) * x1 + t * x2;
            float ty = (1 - t) * y1 + t * y2;

            // 랜덤한 선 두께
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


void drawEyeTouch(float x, float y, float scale) {
  
}



void drawCursor() {



    glTranslatef(0.0, -20.0, 0.0);  // 아래로 이동
    glRotatef(20.0, 0.0, 0.0, 1.0);  // 왼쪽으로 20도 회전

    glLineWidth(3.0);

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



void drawScene1() {
    // 첫 번째 장면 그리기 코드는 여기에 작성
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);



    // 땅 그리기
    drawGround(windowWidth, windowHeight);

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    // 알 그리기
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[0].x, eggs[0].y, 15.0 * sin(eggs[0].angle), 1.0, 1.0, 0.0); // 노란색
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // 연분홍색
        drawEgg(eggs[2].x, eggs[2].y, 15.0 * sin(eggs[2].angle), 0.6, 0.4, 0.8); // 연보라색);
        eggs[i].angle += 0.1; // 흔들림 각도 업데이트
    }

}

void drawScene2() {
    // 두 번째 장면 그리기 코드는 여기에 작성
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);


    // 첫 번째 장면의 내용을 여기에 복사
    // 땅 그리기
    drawGround(windowWidth, windowHeight);

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }


    // 알 그리기
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[0].x, eggs[0].y, 15.0 * sin(eggs[0].angle), 1.0, 1.0, 0.0); // 노란색
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // 연분홍색
        drawEgg(eggs[2].x, eggs[2].y, 15.0 * sin(eggs[2].angle), 0.6, 0.4, 0.8); // 연보라색);
        eggs[i].angle += 0.1; // 흔들림 각도 업데이트
    }
    // 마우스 커서 그리기

    float cursorX = 640.0; // 예시로 640.0으로 지정
    float cursorY = 300.0; // 예시로 300.0으로 지정
    glPushMatrix();
    glTranslatef(cursorX, cursorY, 0.0);
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

    // 알 그리기
    for (int i = 0; i < numEggs; ++i) {
        eggs[i].y += 1.0; // 알을 위로 이동
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // 연분홍색
    }

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }


    glPopMatrix(); // 이 네 줄 마지막 장면에 넣으면 됨.

}









void drawScene4() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 첫 번째 장면의 내용을 여기에 복사
    // 땅 그리기
    drawGround(windowWidth, windowHeight);

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }

    for (int i = 0; i < numEggs; ++i) {
        eggs[i].y += 1.0; // 알을 위로 이동

        // 폭죽 알 아래로 깔리도록 그리기
        drawEgg(eggs[1].x, eggs[1].y, 15.0 * sin(eggs[1].angle), 1.0, 0.0, 0.5); // 연분홍색
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

    // 땅 그리기
    drawGround(windowWidth, windowHeight);

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }


    // 병아리 그리기
    glPushMatrix();
    drawChick();
    glPopMatrix();

    // 0.5초 동안 폭죽 그리기

    static int fireworksTimer = 0;


    if (fireworksTimer < 15) {
        for (int i = 0; i < 5; ++i) {
            float xpos = chick.x; // 병아리의 위치로 지정
            float ypos = chick.y;

            drawFirework(xpos, ypos);
        }
        fireworksTimer++;
    }


    // 연분홍색 알이 없어지도록 설정
    eggs[1].y = 1000.0; // 임의로 알을 화면 밖으로 이동

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
    }
}





void drawScene6() {

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 날개 파닥거리기 애니메이션
    wingAngle = 800.0 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 0.0174533; // 라디안으로 변환5); // * 뒤 부분이 파닥거리는각도
    // sin 앞이 좀 더 빨리 파닥

    // 땅 그리기
    drawGround(windowWidth, windowHeight);


    // 병아리 그리기
    glPushMatrix();
    glTranslatef(chick.x, chick.y, 0.0);
    glScalef(chick.scale, chick.scale, 1.0);
    drawChicken(0.0, 0.0, 1.0, wingAngle);  // wingAngle을 drawChicken 함수에 전달
    drawEyeTouch(chick.x,chick.y,chick.scale);  // 눈 밑에 볼터치 그리기
 

    // 구름 그리기
    for (int i = 0; i < numClouds; ++i) {
        drawCloud(clouds[i].x, clouds[i].y);
        // 이러면 병아리가 구름에 가려지지 않는다
    }
   //drawFlower(flowerX, flowerY);
    glPopMatrix(); // 이 네 줄 마지막 장면에 넣으면 됨.

    }




void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 뷰포트 설정
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
        // 추가적인 case 문을 통해 다른 장면들에 대한 처리 추가
        // case 2:
        //     drawScene3();
        //     break;
        // ...
     // 투영 행렬 설정


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
    // 일정 시간이 지날 때마다 장면 전환
    sceneIndex = (sceneIndex + 1) % 8; // 장면의 총 갯수
    // 모든 장면을 재생한 경우 처음 장면으로 돌아가기
    if (sceneIndex == 0) {
        glutPostRedisplay(); // 화면을 다시 그리도록 요청
    }
    else {
        glutTimerFunc(1000, timer, 0);  // 1초 후에 다음 장면으로 전환
    }
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h); // 뷰포트 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h); // 오쏘노메트릭 뷰 설정
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void update(int value) {

    // 구름 이동 업데이트
    for (int i = 0; i < numClouds; ++i) {
        clouds[i].x += clouds[i].speed;
        if (clouds[i].x > glutGet(GLUT_WINDOW_WIDTH)) {
            clouds[i].x = -50.0; // 화면 왼쪽으로 나가면 다시 오른쪽에서 시작
            clouds[i].y = static_cast<float>(rand() % 360 + 300); // 높이는 임의로 변경
        }
    }
    for (int i = 0; i < numEggs; ++i) {
        if (eggs[i].x > glutGet(GLUT_WINDOW_WIDTH)) {
            eggs[i].x = -50.0; // 화면 왼쪽으로 나가면 다시 오른쪽에서 시작
        }
       
        
        // 꽃이 떨어지는 애니메이션
     //flowerY -= 1.0;

        // 꽃이 빙글빙글 도는 애니메이션
    // flowerRotation += 1.0;


        glutPostRedisplay();
        glutTimerFunc(30, update, 0); // 30ms마다 업데이트 호출
    }
}






int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Cloud Animation");


    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // 리셰이프 콜백 등록
    glutTimerFunc(25, update, 0); // 25ms마다 업데이트 호출
    glutTimerFunc(1000, timer, 0);  // 초기에 타이머 호출


    glutMainLoop();
    return 0;
}