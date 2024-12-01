#include <GL/glut.h>
#include <cmath>
#include <ctime>



bool isScene1 = true;  // 현재 장면 상태 (장면 1인지 여부)

// 구름의 정보를 담는 구조체
struct Cloud {
    float x, y; // 구름의 현재 위치
    float speed; // 구름의 이동 속도
};


struct Egg {
    float x, y; // 알의 현재 위치
    float angle; // 알의 흔들림의 진폭

};

struct Tree {
    float x, y; // 나무의 위치
    float height; // 나무의 높이
};




const int numClouds = 8; // 구름의 갯수
Cloud clouds[numClouds]; // 구름 배열


const int numEggs = 3; // 알의 갯수
Egg eggs[numEggs]; // 알 배열


const int numTrees = 2; // 나무의 갯수
Tree trees[numTrees]; // 나무 배열




void init() {
    glClearColor(0.7, 0.9, 1.0, 1.0); // 하늘색 배경

    // 나무 초기 위치 및 높이 설정
    trees[0].x = 200.0;
    trees[0].y = 200.0;
    trees[0].height = 150.0;

    trees[1].x = 800.0;
    trees[1].y = 180.0;
    trees[1].height = 130.0;


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
}


void drawCursor() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);  // 흰색
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
    glColor3f(1.0, 1.0, 1.0);  // 흰색
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

void drawTree(float x, float y, float height) {
    glColor3f(0.6, 0.3, 0.0); // 갈색 나무색

    // 나무 그리기
    glBegin(GL_QUADS);
    glVertex2f(x - 10.0, y);
    glVertex2f(x + 10.0, y);
    glVertex2f(x + 10.0, y + height);
    glVertex2f(x - 10.0, y + height);
    glEnd();
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
    }


    glutPostRedisplay();
    glutTimerFunc(30, update, 0); // 30ms마다 업데이트 호출
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

    // 나무 그리기
    for (int i = 0; i < numTrees; ++i) {
        drawTree(trees[i].x, trees[i].y, trees[i].height);
    }

    // 알 그리기
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[i].x, eggs[i].y, 15.0 * sin(eggs[i].angle), 1.0, 0.0, 0.5); // 연분홍색
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

    // 나무 그리기
    for (int i = 0; i < numTrees; ++i) {
        drawTree(trees[i].x, trees[i].y, trees[i].height);
    }

    // 알 그리기
    for (int i = 0; i < numEggs; ++i) {
        drawEgg(eggs[i].x, eggs[i].y, 15.0 * sin(eggs[i].angle), 1.0, 0.0, 0.5); // 연분홍색
        eggs[i].angle += 0.1; // 흔들림 각도 업데이트
    }

    // 마우스 커서 그리기
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
    // 일정 시간이 지날 때마다 장면 전환
    isScene1 = !isScene1;
    glutPostRedisplay();
    glutTimerFunc(5000, timer, 0);  // 5000ms (5초) 후에 다시 타이머 호출
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
    srand(static_cast<unsigned>(time(NULL)));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Cloud Animation");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // 리셰이프 콜백 등록
    glutTimerFunc(25, update, 0); // 25ms마다 업데이트 호출
    glutTimerFunc(5000, timer, 0);  // 초기에 타이머 호출

    init();

    glutMainLoop();
    return 0;
}
