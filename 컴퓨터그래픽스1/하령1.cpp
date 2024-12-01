#include <stdio.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>

int sceneIndex;
float x, y;
float headOffset = 0.0; // �Ӹ��� y �� ������ ��
int flag = 0;
int currentScene = 1; // ���� ����� ��Ÿ���� ����
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
}//��ŸƮ ��ư ���� ����

void hideArrow(int value) {
	arrowVisible = false;
	glutPostRedisplay();
}//ȭ��ǥ ����� �ڵ�


void toggleArrowVisibility(int value) {
	arrowVisible = true;
	glutPostRedisplay();
	glutTimerFunc(2000, hideArrow, 0);
	glutTimerFunc(2000, changeColor, 0);
}//ȭ��ǥ ����� ���ÿ� ��ŸƮ ��ư ���� �����ϴ� �ڵ�





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
}//���� ����� �ڵ�

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
}//������ �����̴� �ִϸ��̼�

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
}//ȭ��ǥ ����� �ڵ�


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
	glEnd(); //���۹�ư�� �׸� �׸��� �ڵ�

	if (arrowVisible) {
		glColor3f(1.0f, 0.5f, 0.0f);
	}
	else {
		glColor3f(1.0f, 1.0f, 0.0f);
	} //arrowVisible�� ������ ���� ������ �ٲ�� �Լ�
	glRectf(-0.4f, -0.1f, 0.2f, 0.4f);

	if (arrowVisible) {
		drawArrow(0.06f, 0.23f, 1.0f, 1.0f, 1.0f);
	}
	glPopMatrix();

	renderBitmapString(-0.15f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Start");
}//�����ؽ�Ʈ�� �Բ� ȭ��ǥ�� �׸��� �Լ�

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
//}//��� �׸��� �ڵ�

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
}//���� �׸��� �ڵ�


void drawScene1() {
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

void toggleWindow(int value) {
	flag++;
	glutPostRedisplay(); // ȭ�� �ٽ� �׸��� ��û
	glutTimerFunc(500, toggleWindow, 0); // 0.5�� �������� �ڱ� �ڽ��� ȣ���Ͽ� �ݺ�
}//���2�� �Ķ� ����� �����Ÿ�



void drawScene2() {
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

	// ����
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
	case 2:
		drawScene3();
		break;

	default:
		break;
	}


	glutSwapBuffers();
}

void timer(int value) {
	// ���� �ð��� ���� ������ ��� ��ȯ
	sceneIndex = (sceneIndex + 1) % 6; // ����� �� ����
	// ��� ����� ����� ��� ó�� ������� ���ư���
	if (sceneIndex == 0) {
		glutPostRedisplay(); // ȭ���� �ٽ� �׸����� ��û
	}
	else {
		glutTimerFunc(2000, timer, 0);  // 1�� �Ŀ� ���� ������� ��ȯ
	}
}
void init() {
	// �ʱ�ȭ �ڵ�...
	glClearColor(1.0, 1.0, 1.0, 1.0); // ���� ���� (���)
	glMatrixMode(GL_PROJECTION); // ���� ��� ����
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 720); // ������ ��ǥ ����
	glutTimerFunc(500, toggleWindow, 0); // 0.5�� �������� toggleWindow �Լ� ȣ��
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
	// ������ ���� �Լ� �ڵ�...
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("opengl �ִϸ��̼�");
	glutDisplayFunc(display); // drawScene1() �Լ��� ���÷��� �Լ��� ���
	init();
	glutReshapeFunc(reshape);
	glutTimerFunc(32, updateClouds, 0);
	glutTimerFunc(2000, timer, 0);

	glutMainLoop();
	return 0;
}