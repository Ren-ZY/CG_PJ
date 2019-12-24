#include<windows.h>
#include <GL/glut.h>
#include <stdio.h>

GLfloat d = 0.1;
GLfloat translateX = 0, translateY = 0;
int halfLength = 70;
GLfloat ratio;
GLfloat sun2Earth = 40.0;
GLfloat earth2Moon = 10.0;
GLfloat earthAngle = 0.0, moonAngle = 0.0;
GLfloat sunSize = 15;
GLfloat earthSize = 5;
GLfloat moonSize = 2;
GLfloat sunColor[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat earthColor[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat moonColor[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat whiteLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };



class Point{

public:
	GLfloat x, y, z;
	Point(GLfloat x = 0.0, GLfloat y = 0.0, GLfloat z = 0.0){
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

typedef Point Color;

void init(){

	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
}

void drawCoord(){

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-halfLength, 0.0);
	glVertex2f(halfLength, 0.0);
	glVertex2f(0.0, -halfLength);
	glVertex2f(0.0, halfLength);
	glEnd();
}

void changeSize(GLsizei w, GLsizei h){

	glViewport(0.0, 0.0, w, h);
	if (h == 0)
		h = 1;
	ratio = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w < h)
		glOrtho(-halfLength, halfLength, -halfLength / ratio, halfLength / ratio, -halfLength, halfLength);

	//        glFrustum(-halfLength, halfLength, -halfLength / ratio, halfLength /ratio, -10 * halfLength, 0.0);
	else
		glOrtho(-halfLength * ratio, halfLength * ratio, -halfLength, halfLength, -halfLength, halfLength);

	//        glFrustum(-halfLength * ratio, halfLength * ratio, -halfLength, halfLength, -10 * halfLength, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void renderScene(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glRotatef(80.0, 1.0, 1.0, 1.0);

	//    drawCoord();

	glColor3fv(sunColor);
	glDisable(GL_LIGHTING);
	glutSolidSphere(sunSize, 50, 50);
	glEnable(GL_LIGHTING);
	glRotatef(earthAngle, 0.0, 0.0, 1.0);
	glTranslatef(sun2Earth, 0.0, 0.0);
	glColor3fv(earthColor);
	glutSolidSphere(earthSize, 50, 50);
	glRotatef(moonAngle, 0.0, 0.0, 1.0);
	glTranslatef(earth2Moon, 0.0, 0.0);
	glColor3fv(moonColor);
	glutSolidSphere(moonSize, 50, 50);
	glLoadIdentity();
	earthAngle += d;
	moonAngle += 12 * d;
	glutSwapBuffers();
	glutPostRedisplay();
}



void mySpecialKeyFunc(int key, int x, int y){

	switch (key){
	case GLUT_KEY_UP:

		d += 0.01;

		break;

	case GLUT_KEY_DOWN:

		d -= 0.01;

		break;

	default:;

	}

}

void myKeyboardFunc(unsigned char key, int x, int y){

	if (key == 'q'){
		exit(0);
	}

}

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("template");
	init();
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutSpecialFunc(mySpecialKeyFunc);
	glutKeyboardFunc(myKeyboardFunc);
	glutMainLoop();
	return 0;
}
