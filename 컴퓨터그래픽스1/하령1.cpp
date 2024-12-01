#include <stdio.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>

int sceneIndex;
float x, y;
float headOffset = 0.0; // 머리의 y 축 오프셋 값
int flag = 0;
int currentScene = 1; // 현재 장면을 나타내는 변수
float cloud1_pos = -0.5f;
float cloud2_pos = 0.0f;
float cloud3_pos = 0.5f;
bool arrowVisible = false;
bool arrowDrawn = false;






void changeColor(int value) {
	if (!arrowDrawn) {
		arrowDrawn = true;
		glutPostRedisplay();
	}
}//스타트 버튼 색깔 변경

void hideArrow(int value) {
	arrowVisible = false;
	glutPostRedisplay();
}//화살표 숨기는 코드


void toggleArrowVisibility(int value) {
	arrowVisible = true;
	glutPostRedisplay();
	glutTimerFunc(2000, hideArrow, 0);
	glutTimerFunc(2000, changeColor, 0);
}//화살표 숨김과 동시에 스타트 버튼 색깔 변경하는 코드





void drawCloud(float x, float scale) {
	float y = 1.25f;
	glPushMatrix();
	glTranslatef(x, y, 0.8f);
	glScalef(scale, scale, 5.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	float angle;
	for (int i = 0; i < 360; i += 20) {
		angle = i * 3.14159f / 180;
		glVertex2f(0.22f * cos(angle), 0.09f * sin(angle));
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 360; i += 20) {
		angle = i * 3.14159f / 180;
		glVertex2f(0.2f * cos(angle), 0.08f * sin(angle));
	}
	glEnd();
	glPopMatrix();
}//구름 만드는 코드

void updateClouds(int value) {
	cloud1_pos += 0.005f;
	cloud2_pos += 0.001f;
	cloud3_pos += 0.007f;
	if (cloud1_pos > 1.3) cloud1_pos = -1.3;
	if (cloud2_pos > 1.3) cloud2_pos = -1.3;
	if (cloud3_pos > 1.3) cloud3_pos = -1.3;

	drawCloud(cloud1_pos, 0.8f);
	drawCloud(cloud2_pos, 0.9f);
	drawCloud(cloud3_pos, 1.0f);

	glutPostRedisplay();
	glutTimerFunc(32, updateClouds, 0);
}//구름을 움직이는 애니메이션

void renderBitmapString(float x, float y, void* font, const char* string) {
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);
	while (*string) {
		glutBitmapCharacter(font, *string);
		string++;
	}

}
void drawArrow(float x, float y, float red, float green, float blue) {
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(red, green, blue);
	glVertex2f(-0.05f, -0.4f);
	glVertex2f(-0.05f, -0.5f);
	glVertex2f(0.05f, -0.5f);
	glVertex2f(0.05f, -0.4f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(red, green, blue);
	glVertex2f(0.0f, -0.25f);
	glVertex2f(-0.1f, -0.4f);
	glVertex2f(0.1f, -0.4f);
	glEnd();

	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.05f, -0.4f);
	glVertex2f(-0.05f, -0.5f);
	glVertex2f(0.05f, -0.5f);
	glVertex2f(0.05f, -0.4f);
	glVertex2f(0.1f, -0.4f);
	glVertex2f(0.0f, -0.25f);
	glVertex2f(-0.1f, -0.4f);
	glEnd();

	glPopMatrix();
}//화살표 만드는 코드


void drawStartText() {
	glPushMatrix();
	glTranslatef(-0.1f, 0.0f, -5.0f);

	glLineWidth(5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.1f);
	glVertex2f(0.2f, -0.1f);
	glVertex2f(0.2f, 0.4f);
	glVertex2f(-0.4f, 0.4f);
	glEnd(); //시작버튼의 네모 그리는 코드

	if (arrowVisible) {
		glColor3f(1.0f, 0.5f, 0.0f);
	}
	else {
		glColor3f(1.0f, 1.0f, 0.0f);
	} //arrowVisible의 변수에 따라 색상이 바뀌는 함수
	glRectf(-0.4f, -0.1f, 0.2f, 0.4f);

	if (arrowVisible) {
		drawArrow(0.06f, 0.23f, 1.0f, 1.0f, 1.0f);
	}
	glPopMatrix();

	renderBitmapString(-0.15f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Start");
}//시작텍스트와 함께 화살표를 그리는 함수

//void drawBackground() {
//	glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
//	glBegin(GL_QUADS);
//	glColor3f(0.0f, 0.6f, 1.0f);
//	glVertex2f(-1.0f, -0.2f);
//	glVertex2f(1.0f, -0.2f);
//	glVertex2f(1.0f, 1.0f);
//	glVertex2f(-1.0f, 1.0f);
//	glEnd();
//
//	glBegin(GL_QUADS);
//	glColor3f(0.0f, 1.0f, 0.0f);
//	glVertex2f(-5.0f, -50.0f);
//	glVertex2f(5.0f, -1.0f);
//	glVertex2f(5.0f, -0.2f);
//	glVertex2f(-5.0f, -0.2f);
//	glEnd();
//
//	glLineWidth(2.0f);
//	glBegin(GL_LINES);
//	glColor3f(0.0f, 0.0f, 0.0f);
//	glVertex2f(-10.0f, -0.2f);
//	glVertex2f(10.0f, -0.2f);
//	glEnd();
//
//}//배경 그리는 코드

void drawTree(float xOffset) {
	glLineWidth(3.0f);
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.1f + xOffset, -0.3f);
	glVertex2f(-0.1f + xOffset, 0.0f);
	glVertex2f(0.1f + xOffset, 0.0f);
	glVertex2f(0.1f + xOffset, -0.3f);
	glEnd();

	glColor3f(0.4f, 0.2f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-0.1f + xOffset, -0.3f);
	glVertex2f(-0.1f + xOffset, 0.0f);
	glVertex2f(0.1f + xOffset, 0.0f);
	glVertex2f(0.1f + xOffset, -0.3f);
	glEnd();

	glColor3f(0.0f, 0.5f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f + xOffset, 0.4f);
	glVertex2f(-0.25f + xOffset, -0.1f);
	glVertex2f(0.25f + xOffset, -0.1f);
	glEnd();

	glColor3f(0.0f, 0.6f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f + xOffset, 0.5f);
	glVertex2f(-0.25f + xOffset, 0.2f);
	glVertex2f(0.25f + xOffset, 0.2f);
	glEnd();
}//나무 그리는 코드


void drawScene1() {
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

void toggleWindow(int value) {
	flag++;
	glutPostRedisplay(); // 화면 다시 그리기 요청
	glutTimerFunc(500, toggleWindow, 0); // 0.5초 간격으로 자기 자신을 호출하여 반복
}//장면2의 파란 모니터 깜빡거림



void drawScene2() {
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
	glPopMatrix();
}


void drawScene3() {
	int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glPolygonOffset;

	// Draw clouds for Scene1
	drawCloud(cloud1_pos, 0.8f);
	drawCloud(cloud2_pos, 0.9f);
	drawCloud(cloud3_pos, 1.0f);

	// 나무
	glPushMatrix();
	glTranslatef(-2.8f, -0.1f, -5.0f);
	drawTree(0.0f); // First tree
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8f, -0.1f, -5.0f);
	drawTree(2.0f); // Third tree
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.8f, -0.1f, -5.0f);
	drawTree(3.0f); // Fourth tree
	glPopMatrix();

	// Draw the start text and arrow for Scene1
	drawStartText();

	glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.6f, 1.0f);
	glVertex2f(-1.0f, -0.2f);
	glVertex2f(1.0f, -0.2f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-5.0f, -50.0f);
	glVertex2f(5.0f, -1.0f);
	glVertex2f(5.0f, -0.2f);
	glVertex2f(-5.0f, -0.2f);
	glEnd();

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-10.0f, -0.2f);
	glVertex2f(10.0f, -0.2f);
	glEnd();

	glutSwapBuffers();
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
	case 2:
		drawScene3();
		break;

	default:
		break;
	}


	glutSwapBuffers();
}

void timer(int value) {
	// 일정 시간이 지날 때마다 장면 전환
	sceneIndex = (sceneIndex + 1) % 6; // 장면의 총 갯수
	// 모든 장면을 재생한 경우 처음 장면으로 돌아가기
	if (sceneIndex == 0) {
		glutPostRedisplay(); // 화면을 다시 그리도록 요청
	}
	else {
		glutTimerFunc(2000, timer, 0);  // 1초 후에 다음 장면으로 전환
	}
}
void init() {
	// 초기화 코드...
	glClearColor(1.0, 1.0, 1.0, 1.0); // 배경색 설정 (흰색)
	glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 720); // 윈도우 좌표 설정
	glutTimerFunc(500, toggleWindow, 0); // 0.5초 간격으로 toggleWindow 함수 호출
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
	// 기존의 메인 함수 코드...
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("opengl 애니메이션");
	glutDisplayFunc(display); // drawScene1() 함수를 디스플레이 함수로 사용
	init();
	glutReshapeFunc(reshape);
	glutTimerFunc(32, updateClouds, 0);
	glutTimerFunc(2000, timer, 0);

	glutMainLoop();
	return 0;
}