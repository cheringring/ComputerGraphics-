#include <GL/glut.h>
#include <cmath>
float cloud1_pos = -0.5f;
float cloud2_pos = 0.0f;
float cloud3_pos = 0.5f;




// OpenGL 초기화 함수
void initOpenGL() {
	glClearColor(0.7, 0.9, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h); // 뷰포트 설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void updateClouds(int value) {
	// 구름 위치 업데이트
	cloud1_pos += 0.001f;
	cloud2_pos += 0.002f;
	cloud3_pos += 0.003f;
	if (cloud1_pos > 1.5) cloud1_pos = -1.5;
	if (cloud2_pos > 1.5) cloud2_pos = -1.5;
	if (cloud3_pos > 1.5) cloud3_pos = -1.5;
	glutPostRedisplay();
	glutTimerFunc(16, updateClouds, 0);
}
void drawCloud(float x) {
	glPushMatrix();
	glTranslatef(x, 0.7f, -0.5f);
	// 구름 모양 그리기 (간단히 원을 이용한 예시)
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f); // 흰색
	float angle;
	for (int i = 0; i < 360; i += 20) {
		angle = i * 3.14159f / 180;
		glVertex2f(0.1f * cos(angle), 0.05f * sin(angle));
	}
	glEnd();
	glPopMatrix();
}


void renderBitmapString(float x, float y, void* font, const char* string) {
	glColor3f(0.0f, 0.0f, 0.0f); // 검은색
	glRasterPos2f(x, y); // 출력 위치 설정
	while (*string) {
		glutBitmapCharacter(font, *string);
		string++;
	}
}

void drawStartText() {
	glPushMatrix();
	glTranslatef(-0.1f, 0.0f, -5.0f); // gluLookAt을 기반으로 z축에서의 이동을 조정합니다.
	glColor3f(1.0f, 1.0f, 0.0f); // 노란색
	glRectf(-0.1f, -0.05f, 0.2f, 0.05f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.1f, 0.0f, -5.0f); // gluLookAt을 기반으로 z축에서의 이동을 조정합니다.
	// "Start" 텍스트 출력
	glColor3f(0.0f, 0.0f, 0.0f); // 검은색
	glRasterPos2f(-0.3f, 0.0f);
	const char* text = "시작";
	while (*text) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text); // 고정 크기 글꼴 사용
		++text;
	}
	glPopMatrix();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	// 배경 색상 설정
	glClearColor(0.0f, 0.6f, 1.0f, 1.0f); // 하늘색 배경
	glBegin(GL_QUADS); // 초록색과 하늘색 배경 그리기
	// 초록색 배경
	glColor3f(0.0f, 0.6f, 1.0f); //하늘색
	glVertex2f(-1.0f, -0.2f);
	glVertex2f(1.0f, -0.2f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd(); // 초록색 배경 그리기 종료
	// 하늘색 배경
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);//초록색
	glVertex2f(-5.0f, -1.0f);
	glVertex2f(5.0f, -1.0f);
	glVertex2f(5.0f, -0.2f);
	glVertex2f(-5.0f, -0.2f);
	glEnd(); // 하늘색 배경 그리기 종료
	// 구름 그리기
	drawCloud(cloud1_pos);
	drawCloud(cloud2_pos);
	drawCloud(cloud3_pos);
	// "Start" 텍스트와 네모 그리기
	drawStartText();
	renderBitmapString(-0.1f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Start");
	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Start Screen");


	// 좌표 시스템 설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	// 초기화 함수 호출
	initOpenGL();

	glutDisplayFunc(display);
	glutTimerFunc(0, updateClouds, 0);
	glutMainLoop();
	return 0;
}