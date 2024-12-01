#include <GL/glut.h>
#include <cmath>
float cloud1_pos = -0.5f;
float cloud2_pos = 0.0f;
float cloud3_pos = 0.5f;




// OpenGL �ʱ�ȭ �Լ�
void initOpenGL() {
	glClearColor(0.7, 0.9, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h); // ����Ʈ ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void updateClouds(int value) {
	// ���� ��ġ ������Ʈ
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
	// ���� ��� �׸��� (������ ���� �̿��� ����)
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f); // ���
	float angle;
	for (int i = 0; i < 360; i += 20) {
		angle = i * 3.14159f / 180;
		glVertex2f(0.1f * cos(angle), 0.05f * sin(angle));
	}
	glEnd();
	glPopMatrix();
}


void renderBitmapString(float x, float y, void* font, const char* string) {
	glColor3f(0.0f, 0.0f, 0.0f); // ������
	glRasterPos2f(x, y); // ��� ��ġ ����
	while (*string) {
		glutBitmapCharacter(font, *string);
		string++;
	}
}

void drawStartText() {
	glPushMatrix();
	glTranslatef(-0.1f, 0.0f, -5.0f); // gluLookAt�� ������� z�࿡���� �̵��� �����մϴ�.
	glColor3f(1.0f, 1.0f, 0.0f); // �����
	glRectf(-0.1f, -0.05f, 0.2f, 0.05f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.1f, 0.0f, -5.0f); // gluLookAt�� ������� z�࿡���� �̵��� �����մϴ�.
	// "Start" �ؽ�Ʈ ���
	glColor3f(0.0f, 0.0f, 0.0f); // ������
	glRasterPos2f(-0.3f, 0.0f);
	const char* text = "����";
	while (*text) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text); // ���� ũ�� �۲� ���
		++text;
	}
	glPopMatrix();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	// ��� ���� ����
	glClearColor(0.0f, 0.6f, 1.0f, 1.0f); // �ϴû� ���
	glBegin(GL_QUADS); // �ʷϻ��� �ϴû� ��� �׸���
	// �ʷϻ� ���
	glColor3f(0.0f, 0.6f, 1.0f); //�ϴû�
	glVertex2f(-1.0f, -0.2f);
	glVertex2f(1.0f, -0.2f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd(); // �ʷϻ� ��� �׸��� ����
	// �ϴû� ���
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);//�ʷϻ�
	glVertex2f(-5.0f, -1.0f);
	glVertex2f(5.0f, -1.0f);
	glVertex2f(5.0f, -0.2f);
	glVertex2f(-5.0f, -0.2f);
	glEnd(); // �ϴû� ��� �׸��� ����
	// ���� �׸���
	drawCloud(cloud1_pos);
	drawCloud(cloud2_pos);
	drawCloud(cloud3_pos);
	// "Start" �ؽ�Ʈ�� �׸� �׸���
	drawStartText();
	renderBitmapString(-0.1f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Start");
	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Start Screen");


	// ��ǥ �ý��� ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	// �ʱ�ȭ �Լ� ȣ��
	initOpenGL();

	glutDisplayFunc(display);
	glutTimerFunc(0, updateClouds, 0);
	glutMainLoop();
	return 0;
}