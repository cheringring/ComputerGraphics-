#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

float angle = 0.0f;
float center[3] = { 0.2, 0.2, 0.0 };




void MyDisplay() {


    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 900, 900);
    glColor3f(0.0, 0.0, 1.0); 


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



   
    glTranslatef(center[0], center[1], center[2]);
 
    glRotatef(angle, 0.0, 0.0, 1.0);
 
    glTranslatef(-center[0], -center[1], -center[2]);

    glutSolidSphere(0.1, 25, 25); 


    glFlush();

}



void update(int value) {


    angle += 1.0f; 
    if (angle > 360.0f) {

        angle -= 360.0f;

    }


    glutPostRedisplay();
    glutTimerFunc(12, update, 0);


}

int main(int argc, char** argv) {


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(900, 900);


    glutCreateWindow("파란색원구회전하기");
    glClearColor(1.0, 1.0, 1.0, 1.0);


    glutDisplayFunc(MyDisplay);
    glutTimerFunc(15, update, 0);


    glutMainLoop();



    return 0;
}
