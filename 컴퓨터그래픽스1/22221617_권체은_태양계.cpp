

#include <GL/glut.h>
#include <string>
#include <iostream>
bool animationStarted = false;
bool nextScene = false;
float cloudX = 0.0;
float groundY = -0.5;
float mouseX = -1.0; // 초기값을 -1.0으로 설정
int currentScene = 0; // 현재 그림의 인덱스
int switchInterval = 1000;

void drawCloud() {
	// 구름 그리는 코드
	glPushMatrix();
	glTranslatef(cloudX, 0.2, 0.0);
	glColor3f(1, 0.980392, 0.980392);
	glutSolidSphere(0.1, 20, 20);
	glPopMatrix();
}

void drawGround() {
	// 땅 그리는 코드
	glColor3f(0.803922, 0.360784, 0.360784);  // 갈색
	glBegin(GL_POLYGON);
	glVertex2f(-1.0, groundY);
	glVertex2f(1.0, groundY);
	glVertex2f(1.0, -1.0);
	glVertex2f(-1.0, -1.0);
	glEnd();
}

void drawCircle(GLfloat x, GLfloat y, GLfloat radius, int numSegments) {
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= numSegments; ++i) {
		GLfloat angle = static_cast<GLfloat>(i) * 2.0 * 3.14159265358979323846 / numSegments;
		GLfloat xPos = x + radius * cos(angle);
		GLfloat yPos = y + radius * sin(angle);
		glVertex2f(xPos, yPos);
	}
	glEnd();
}
void drawEggs() {
	// 첫 번째 알 그리기
	glColor3f(1.0, 0.5, 0.5); // 연분홍색
	drawCircle(80, 200, 30, 360);
	// 두 번째 알 그리기
	glColor3f(0.7, 0.5, 0.9); // 연보라색
	drawCircle(200, 200, 30, 360);
	// 세 번째 알 그리기
	glColor3f(1.0, 1.0, 0.0); // 노란색
	drawCircle(320, 200, 30, 360);
}
void drawChick() {

	
		// 몸통
	glColor3f(1.0, 1.0, 0.5); // 연노란색
	drawCircle(200, 200, 50, 360);
	// 머리
	glColor3f(1.0, 1.0, 0.5); // 연노란색
	drawCircle(200, 240, 15, 360);
	// 눈
	glColor3f(0.0, 0.0, 0.0); // 검은색
	drawCircle(190, 245, 2, 360);
	drawCircle(205, 245, 2, 360);
	// 부리
	glColor3f(1.0, 0.5, 0.0); // 주황색
	glBegin(GL_TRIANGLES);
	glVertex2f(202, 235);
	glVertex2f(207, 238);
	glVertex2f(202, 240);
	glEnd();



}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);


		// 현재 그림 그리기
		drawGround();
	drawCloud();

	if (currentScene == 0) {
		drawEggs();
	}
	else if (currentScene == 1) {
		drawChick();
	}
	else if (currentScene == 2) {
		// 세 번째 장면 그리기
	}

	glutSwapBuffers();



}

void switchScene(int value) {
	// 그림 전환
	currentScene = (currentScene + 1) % 4;
	glutPostRedisplay();
	glutTimerFunc(switchInterval, switchScene, 0);
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Chick Animation");
	glutInitWindowSize(600, 500);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glClearColor(0.529412, 0.807843, 0.980392, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

		// 타이머 함수등록하기.

		glutTimerFunc(switchInterval, switchScene, 0);
	glutMainLoop();
	return 0;


}