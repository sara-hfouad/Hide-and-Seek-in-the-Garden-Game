#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <time.h>
#include <ctime>
#include <string.h>
#include <string>
#include<iostream>
#include<windows.h>

#define DEG2RAD(a) (a * 0.0174532925)


class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 0.0f, float eyeY = 1.5f, float eyeZ = 4.5f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, 
		float upY = 1.0f, float upZ = 0.0f) 
	{
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		eye.x = eye.x + d;
	}

	void moveY(float d) {
		eye.y = eye.y + d;
	}

	void moveZ(float d) {
		eye.z = eye.z +  d;
	}

	void set(float x, float y, float z) {
		eye.x = x;
		eye.y = y;
		eye.z = z;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z);
	}
};

Camera camera;

float timer = 6;
float fx = 0;
float fy = 0;
float fz = 0;
float xplayer = 0;
float zplayer=0;
float gx = 0;
float gz = 0;


float t = 0;
float tr = 0.5;
float sf = 1;
float sg = 0;
float ts = 0;

bool backsound = false;
bool fencesound = true;
bool grasssound = true;
bool umbsound = true;
bool treesound = true;
bool benchsound = true;
bool swingsound = true;
bool losesound = false;
bool winsound = false;
bool bump = false;
bool won = false;
bool timesup = false;
bool setGoal = false;
bool rotUmb = false;
bool transBench = false;
bool transTree = false;
bool scaleFence = false;
bool scalegrass = false;
bool transSwing = false;
bool inct = true;
bool incb = true;
bool incf = true;
bool rotu = true;
bool scg = true;
bool incs = true;

float rotAng=0;

void Anim() {
	if (rotAng > 180) {
		rotAng = 0;
		rotu = !rotu;
	}
	rotAng += 5;

	glutPostRedisplay();
}

void drawCircle(float x, float y,float z, float r) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(-90, 1, 0, 0);	
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

void draw_cylinder(GLfloat radius, GLfloat height, float xt,float yt, float zt)
{
	GLfloat x = 0.0;
	GLfloat z = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	glPushMatrix();
	glTranslatef(xt,yt, zt);

	/** Draw the tube */
	glColor3f(0.4f, 0.2f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * 3.14159) {
		x = radius * cos(angle);
		z = radius * sin(angle);
		glVertex3f(x, height, z);
		glVertex3f(x, 0.0, z);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, height, 0.0);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();
	glPopMatrix();
}

void drawTrees() {
	
	if (transTree) {
		if (inct) {
			tr = tr +0.05;
			if (tr > 0.7) 
				inct = false;	
		}
		 if (!inct) {
			tr = tr-0.05;
			if (tr < -1)
				inct = true;
		}
		
	}
	else {
		tr = 0;
	}
	

	draw_cylinder(0.06, 0.75, 1.0, -1, -1.0);
	draw_cylinder(0.06, 0.75, -1.18, -1, -0.5);
	draw_cylinder(0.06, 0.75, 1.15, -1, 0.5+tr);

	glColor3f(0.0f, 0.3f, 0.0f);

	////////////////////////right corner/////////////////
	glPushMatrix();
	glTranslatef(1.0, 0, -1.0);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.1, -0.15, -1.0);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, -0.15, -1.0);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	////////////////////////left///////////////////////
	glPushMatrix();
	glTranslatef(-1.18, 0, -0.5);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.28, -0.15, -0.5);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.08, -0.15, -0.5);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	//////////////////////////right//////////////////////////
	glPushMatrix();
	glTranslatef(1.15, 0, 0.5+tr);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.25, -0.15, 0.5+tr);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.05, -0.15, 0.5+tr);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();
}

void drawFence() {

	if (scaleFence) {
		if (incf) {
			sf += 0.1;
			if (sf > 2)
				incf = false;
		}
		if (!incf) {
			sf -= 0.1;
			if (sf < 0.1)
				incf = true;
		}
	}
	else {
		sf = 1;
	}

	glPushMatrix();

	glScalef(1, sf, 1);

	glBegin(GL_QUADS);

	////////////////////////////////start of front face////////////////////////////////

	glColor3f(fx, fy, fz); // Yellow

	glVertex3f(1.25f, -1.0f, -1.5f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glVertex3f(1.0f, 0.5f, -1.5f);
	glVertex3f(1.25f, 0.5f, -1.5f);

	glVertex3f(0.5f, -1.0f, -1.5f);
	glVertex3f(0.25f, -1.0f, -1.5f);
	glVertex3f(0.25f, 0.5f, -1.5f);
	glVertex3f(0.5f, 0.5f, -1.5f);
	
	glVertex3f(-0.5f, -1.0f, -1.5f);
	glVertex3f(-0.25f, -1.0f, -1.5f);
	glVertex3f(-0.25f, 0.5f, -1.5f);
	glVertex3f(-0.5f, 0.5f, -1.5f);
	
	glVertex3f(-1.25f, -1.0f, -1.5f);
	glVertex3f(-1.0f, -1.0f, -1.5f);
	glVertex3f(-1.0f, 0.5f, -1.5f);
	glVertex3f(-1.25f, 0.5f, -1.5f);


	glVertex3f(-1.5f, 0.5f, -1.5f);
	glVertex3f(-1.5f, 0.25f, -1.5f);
	glVertex3f(1.5f, 0.25f, -1.5f);
	glVertex3f(1.5f, 0.5f, -1.5f);

	glVertex3f(-1.5f, -0.25f, -1.5f);
	glVertex3f(-1.5f, -0.5f, -1.5f);
	glVertex3f(1.5f, -0.5f, -1.5f);
	glVertex3f(1.5f, -0.25f, -1.5f);
	////////////////////////////////end of front face////////////////////////////////

	////////////////////////////////start of right face////////////////////////////////

//	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta

	glVertex3f(1.5f, 0.5f, 1.25f);
	glVertex3f(1.5f, 0.5f, 1.0f);
	glVertex3f(1.5f, -1.0f, 1.0f);
	glVertex3f(1.5f, -1.0f, 1.25f);

	glVertex3f(1.5f, 0.5f, 0.25f);
	glVertex3f(1.5f, 0.5f, 0.5f);
	glVertex3f(1.5f, -1.0f, 0.5f);
	glVertex3f(1.5f, -1.0f, 0.25f);

	glVertex3f(1.5f, 0.5f, -0.25f);
	glVertex3f(1.5f, 0.5f, -0.5f);
	glVertex3f(1.5f, -1.0f, -0.5f);
	glVertex3f(1.5f, -1.0f, -0.25f);
	
	glVertex3f(1.5f, 0.5f, -1.25f);
	glVertex3f(1.5f, 0.5f, -1.0f);
	glVertex3f(1.5f, -1.0f, -1.0f);
	glVertex3f(1.5f, -1.0f, -1.25f);
	
	glVertex3f(1.5f, 0.5f, -1.5f);
	glVertex3f(1.5f, 0.25f, -1.5f);
	glVertex3f(1.5f, 0.25f, 1.5f);
	glVertex3f(1.5f, 0.5f, 1.5f);
	
	glVertex3f(1.5f, -0.5f, -1.5f);
	glVertex3f(1.5f, -0.25f, -1.5f);
	glVertex3f(1.5f,-0.25f, 1.5f);
	glVertex3f(1.5f, -0.5f, 1.5f);
	////////////////////////////////end of right face////////////////////////////////

	////////////////////////////////start of left face////////////////////////////////

//	glColor3f(0.0f, 0.0f, 1.0f);     // Blue

	glVertex3f(-1.5f, 0.5f, 1.25f);
	glVertex3f(-1.5f, 0.5f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.25f);

	glVertex3f(-1.5f, 0.5f, 0.25f);
	glVertex3f(-1.5f, 0.5f, 0.5f);
	glVertex3f(-1.5f, -1.0f, 0.5f);
	glVertex3f(-1.5f, -1.0f, 0.25f);

	glVertex3f(-1.5f, 0.5f, -0.25f);
	glVertex3f(-1.5f, 0.5f, -0.5f);
	glVertex3f(-1.5f, -1.0f, -0.5f);
	glVertex3f(-1.5f, -1.0f, -0.25f);

	glVertex3f(-1.5f, 0.5f, -1.25f);
	glVertex3f(-1.5f, 0.5f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.25f);

	glVertex3f(-1.5f, 0.5f, -1.5f);
	glVertex3f(-1.5f, 0.25f, -1.5f);
	glVertex3f(-1.5f, 0.25f, 1.5f);
	glVertex3f(-1.5f, 0.5f, 1.5f);

	glVertex3f(-1.5f, -0.5f, -1.5f);
	glVertex3f(-1.5f, -0.25f, -1.5f);
	glVertex3f(-1.5f, -0.25f, 1.5f);
	glVertex3f(-1.5f, -0.5f, 1.5f);
	////////////////////////////////end of left face////////////////////////////////

	glEnd();
	
	glPopMatrix();

}

void drawGrass() {

	if (scalegrass) {
		if (scg) {
			sg += 0.01;
			if (sg > 0.1)
				scg = false;
		}
		if (!scg) {
			sg -= 0.01;
			if (sg < -0.02)
				scg = true;
		}
	}
	else {
		sg = 0;
	}

	glBegin(GL_QUADS);
	// Bottom face (y = -1.0f)
	glColor3f(0.0f, 0.6f, 0.1f);     
	glVertex3f(1.5f, -1.0f, 1.5f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	glVertex3f(1.5f, -1.0f, -1.5f);
	glEnd(); 

	glColor3f(0.0f, 0.4f, 0.1f);
	for (float i = -1.5;i < 1.5;i += 0.015) {
		for (float j = -1.5;j < 1.5;j += 0.015) {
			glBegin(GL_QUADS);
			glVertex3f(i, -1.0f, j);
			glVertex3f(i, -1.0f, j + 0.01);
			glVertex3f(i + 0.01, -1.0f, j + 0.01);
			glVertex3f(i + 0.01, -1.0f, j);
			glEnd();

			glPushMatrix();
			glBegin(GL_TRIANGLES);
			glVertex3f(i, -1.0f, j);
			glVertex3f(i, -0.95+sg, j);
			glVertex3f(i + 0.025, -1.0f, j);
			glEnd();
			glPopMatrix();

			glBegin(GL_LINES);
			glVertex3f(1, -1, j);
			glVertex3f(-1, -1, j);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(i, -1, 1);
			glVertex3f(i, -1,-1);
			glEnd();

		}
	}
}

void drawBench() {

	if (transBench) {
		if (incb) {
			t += 0.05;
			if (t > 0.3)
				incb = false;
		}
		if (!incb) {
			t -= 0.05;
			if (t < -0.4)
				incb = true;
		}
	}
	else {
		t = 0;
	}
	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.4f, 0.1f);
	glVertex3f(-0.3 + t, -0.9f, -1.3f);
	glVertex3f(-0.3 + t, -0.9f, -1.1f);
	glVertex3f(0.7 + t, -0.9f, -1.1f);
	glVertex3f(0.7 + t, -0.9f, -1.3f);

	glVertex3f(-0.3 + t, -0.85f, -1.3f);
	glVertex3f(-0.3 + t, -0.8f, -1.3f);
	glVertex3f(0.7 + t, -0.8f, -1.3f);
	glVertex3f(0.7 + t, -0.85f, -1.3f);

	glVertex3f(-0.3 + t, -0.78f, -1.3f);
	glVertex3f(-0.3 + t, -0.73f, -1.3f);
	glVertex3f(0.7 + t, -0.73f, -1.3f);
	glVertex3f(0.7 + t, -0.78f, -1.3f);

	glVertex3f(-0.3 + t, -0.71f, -1.3f);
	glVertex3f(-0.3 + t, -0.66f, -1.3f);
	glVertex3f(0.7 + t, -0.66f, -1.3f);
	glVertex3f(0.7 + t, -0.71f, -1.3f);
	glEnd();

	glColor3f(0.5, 0.5f, 0.5f);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(-0.3 + t, -0.9, -1.3);
	glVertex3f(-0.3 + t, -1, -1.3);
	glVertex3f(-0.3 + t, -0.9, -1.1);
	glVertex3f(-0.3 + t, -1, -1.1);
	glVertex3f(0.7 + t, -0.9, -1.3);
	glVertex3f(0.7 + t, -1, -1.3);
	glVertex3f(0.7 + t, -0.9, -1.1);
	glVertex3f(0.7 + t, -1, -1.1);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(-0.3 + t, -0.9, -1.31);
	glVertex3f(-0.3 + t, -0.63, -1.31);
	glVertex3f(0.7 + t, -0.9, -1.31);
	glVertex3f(0.7 + t, -0.63, -1.31);
	glEnd();

}

void drawUmbrella() {


	glPushMatrix();
	glTranslatef(-0.5, -0.2, -0.9);
	glRotatef(-90, 1, 0, 0);
	glRotatef(-10, 0,1, 0);
	if (rotUmb) {
		if (rotu) {
			glRotatef(rotAng, 0, 0, 1);
			glRotatef(10, 1, 0, 0);
		}
		else {
			glRotatef(-rotAng, 0, 0, 1);
			glRotatef(-10, 1, 0, 0);
		}
	}

	glColor3f(1.0f, 0.6f, 0.5f);
	glutWireCone(0.45, 0.2, 500, 30);
	glPopMatrix();
	
	glLineWidth(4);
	glColor3f(0.7f, 0.6f, 0.3f);
	glBegin(GL_LINES);
	glVertex3f(-0.5, -0.05, -0.9);
	glVertex3f(-0.4, -1, -1.0);
	glEnd();

	glPushMatrix();
	glTranslatef(-0.42, -1, -1.0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.1, 0.1, 20, 20);
	glPopMatrix();

	GLUquadricObj* p = gluNewQuadric();
	glColor3f(0.5f, 0.5f, 0.5f);
	glPushMatrix();
	glTranslatef(-0.5, -0.3, -0.92);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(p, 0.01, 0.01, 0.05, 20, 20);
	glPopMatrix();

}

void drawGoal() {

	if (!setGoal) {
		srand(time(0));
		gx = (rand() % 4) - 1.5;
		gz = (rand() % 4) - 1.5;
		setGoal = true;

		if (gx == 1.5)
			gx = 1.3;
		else if (gx == -1.5)
			gx = -1.3;
		if (gz == 1.5)
			gz = 1.3;
		else if (gz == -1.5)
			gz = -1.3;

	}

	glColor3f(0.5f, 0.5f, 0.5f);
	drawCircle(gx, -0.95, gz, 0.06);

	GLUquadricObj* p = gluNewQuadric();
	glColor3f(0.6f, 0.6f, 0.6f);
	glPushMatrix();
	glTranslatef(gx, -0.95, gz);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(p, 0.02, 0.01, 1.1, 20, 20);
	glPopMatrix();

	glLineWidth(1);
	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glTranslatef(gx, 0.2, gz);
	glRotatef(-90, 1, 0, 0);
	glScalef(1, 1, 1.15);
	glutWireSphere(0.06, 5, 5);
	glPopMatrix();

	glLineWidth(1);
	glColor3f(1, 1, 0.2);
	glPushMatrix();
	glTranslatef(gx, 0.2, gz);
	glRotatef(-90, 1, 0, 0);
	glScalef(1, 1, 2);
	glutSolidSphere(0.03, 20, 20);
	glPopMatrix();

}

void drawPlayer() {

	if (((xplayer > gx-0.05) && (xplayer<gx+0.05)) && ((zplayer > gz-0.05) && (zplayer<gz+0.05))) {
		won = true;
	}

	glColor3f(0.8, 0.5f, 0.2f);
	glColor3f(0.6, 0.3f, 0.0f);

	glPushMatrix();
	glTranslatef(xplayer, -0.8, zplayer);
	glScalef(1.4, 0.8, 1);
	glutSolidSphere(0.1, 20, 20);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(xplayer-0.12, -0.71, zplayer);
	glScalef(1, 1.2, 1);
	glutSolidSphere(0.06, 20, 20);
	glPopMatrix();

//	glColor3f(0.5, 0.2f, 0.0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(xplayer-0.05, -0.85, zplayer-0.05);
	glVertex3f(xplayer-0.05, -1, zplayer - 0.05);

	glVertex3f(xplayer-0.05, -0.85, zplayer + 0.05);
	glVertex3f(xplayer-0.05, -1, zplayer + 0.05);

	glVertex3f(xplayer+0.05, -0.85, zplayer - 0.05);
	glVertex3f(xplayer+0.05, -1, zplayer - 0.05);

	glVertex3f(xplayer+0.05, -0.85, zplayer + 0.05);
	glVertex3f(xplayer+0.05, -1, zplayer + 0.05);
	glEnd();

	glColor3f(1.0, 1.0f, 1.0);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex3f(xplayer - 0.172, -0.7, zplayer - 0.03);
	glVertex3f(xplayer - 0.172, -0.7, zplayer + 0.03);
	glEnd();


}

void drawSwing() {

	if (transSwing) {
		if (incs) {
			ts += 0.05;
			if (ts > 1)
				incs = false;
		}
		if (!incs) {
			ts -= 0.05;
			if (ts < -0.19)
				incs = true;
		}
	}
	else {
		ts = 0;
	}

	glColor3f(0.6 , 0.6f, 0.6f);
	glLineWidth(3);
	glBegin(GL_LINES);
//	glColor3f(1.0f, 0.8f, 0.5f);
	glVertex3f(-1.3 + ts, -1, 1.1);
	glVertex3f(-1.1 + ts, 0, 1.1);
	glVertex3f(-1.1 + ts, 0, 1.1);
	glVertex3f(-0.9 + ts, -1, 1.1);
	glVertex3f(-1.3 + ts, -1, 0.5);
	glVertex3f(-1.1 + ts, 0, 0.5);
	glVertex3f(-1.1 + ts, 0, 0.5);
	glVertex3f(-0.9 + ts, -1, 0.5);

	glVertex3f(-1.1 + ts, 0, 0.5);
	glVertex3f(-1.1 + ts, 0, 1.1);

	glColor3f(0.8f, 0.9f, 0.2f);
	glVertex3f(-1.1 + ts, 0, 1);
	glVertex3f(-1.1 + ts, -0.7, 1);
	glVertex3f(-1.1 + ts, 0, 0.6);
	glVertex3f(-1.1 + ts, -0.7, 0.6);

	glEnd();

//	glColor3f(0.3f, 0.7f, 0.7f);
	glColor3f(0.0f, 0.3f, 0.5f);
	glPushMatrix();
	glTranslatef(-1.1 + ts, -0.7, 0.8);
	glScalef(1, 0.2, 2);
	glutSolidCube(0.2);
	glPopMatrix();

}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 500 / 500, 0.1f, 300.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void printGameover(float x, float y, float z,char* string) {
	int len, i;
	glRasterPos3f(x, y, z);
	len = (int)strlen(string);
	glColor3f(1.0f, 0.6f, 0.5f);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}

}

void Display(void) {

	if (won) {
		glClearColor(0.0f, 0.4f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0f, 0.6f, 0.5f);
		printGameover(-0.4, 0.5, 0, "You Won");
		if (!winsound) {
			PlaySound(TEXT("win.wav"), NULL, SND_ASYNC | SND_LOOP);
			winsound = true;
	}

	}
	else if (timesup) {
		glClearColor(0.0f, 0.4f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0f, 0.6f, 0.5f);
		printGameover(-0.4, 0.5, 0, "Game Over");
		if (!losesound) {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("lose.wav"), NULL, SND_ASYNC | SND_LOOP);
			losesound = true;
		}
	}
	
	else {

		if (!backsound) {
			PlaySound(TEXT("background.wav"), NULL, SND_ASYNC | SND_LOOP | SND_NOSTOP);
			backsound = true;
		}

		setupCamera();


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawFence();
		drawGrass();
		drawTrees();
		drawBench();
		drawUmbrella();
		drawGoal();
		drawPlayer();
		drawSwing();
	}
		glFlush();

}

void key(unsigned char k, int x, int y)
{

	if (k == 'd')
		camera.moveX(0.1);

	if (k == 'a')
		camera.moveX(-0.1);

	if (k == 's')
		camera.moveY(-0.1);

	if (k == 'w')
		camera.moveY(0.1);

	if (k == 'z')
		camera.moveZ(-0.1);

	if (k == 'x')
		camera.moveZ(0.1);

	if (k == 't')
		camera.set(0, 5, 2);

	if (k == 'r')
		camera.set(5, 1, 2.5);

	if (k == 'l')
		camera.set(-5, 1, 2.5);

	if (k == 'f')
		camera.set(0, 1.5, 4.5);

	if (k == 'u') {
		rotUmb = true;
		if (umbsound) {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("umb.wav"), NULL, SND_ASYNC | SND_LOOP);
			umbsound = false;
		}
	}

	if (k == 'b') {
		transBench = true;
		if (benchsound) {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("bench.wav"), NULL, SND_ASYNC | SND_LOOP);
			benchsound = false;
		}
	}

	if (k == 'm') {
		transTree = true;
		if (treesound) {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("tree.wav"), NULL, SND_ASYNC | SND_LOOP);
			treesound = false;
		}
	}

	if (k == 'n') {
		scaleFence = true;
		if (fencesound) {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("fence.wav"), NULL, SND_ASYNC | SND_LOOP);
			fencesound = false;
		}
	}
	
	if (k == 'g') {
		scalegrass = true;
		if (grasssound) {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("grass.wav"), NULL, SND_ASYNC | SND_LOOP);
			grasssound = false;
		}
	}
	
	if (k == 'v') {
		transSwing = true;
		if (swingsound) {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("swing.wav"), NULL, SND_ASYNC | SND_LOOP);
			swingsound = false;
		}
	}
	glutPostRedisplay();//redisplay to update the screen with the changes
}

void keyUp(unsigned char k, int x, int y)//keyboard up function is called whenever the keyboard key is released
{
	if (k == 'u') {
		PlaySound(NULL, 0, 0);
		rotUmb = false;
		umbsound = true;
		backsound = false;
	}
	if (k == 'b') {
		PlaySound(NULL, 0, 0);
		transBench = false;
		benchsound = true;
		backsound = false;
	}
	if (k == 'm') {
		PlaySound(NULL, 0, 0);
		transTree = false;
		treesound = true;
		backsound = false;
	}
	if (k == 'n') {
		PlaySound(NULL, 0, 0);
		scaleFence = false;
		fencesound = true;
		backsound = false;
	}
	if (k == 'g') {
		PlaySound(NULL, 0, 0);
		scalegrass = false;
		grasssound = true;
		backsound = false;
	}
	if (k == 'v') {
		PlaySound(NULL, 0, 0);
		transSwing = false;
		swingsound = true;
		backsound = false;
	}
	glutPostRedisplay();//redisplay to update the screen with the changed
}

void spe(int k, int x, int y)
{	
	if (k == GLUT_KEY_RIGHT) {
		if (xplayer <= 1.3) {
			xplayer += 0.1;
		}
		else {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("bump.wav"), NULL, SND_SYNC);
			backsound = false;
		}
	}
	if (k == GLUT_KEY_LEFT) {
		if (xplayer >= -1.3) {
			xplayer -= 0.1;
		}
		else {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("bump.wav"), NULL, SND_SYNC);
			backsound = false;
		}
	}
	if (k == GLUT_KEY_UP) {
		if (zplayer >= -1.3) {
			zplayer -= 0.1;
		}
		else {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("bump.wav"), NULL, SND_SYNC);
			backsound = false;
		}
	}
	if (k == GLUT_KEY_DOWN) {
		if (zplayer <= 1.3) {
			zplayer += 0.1;
		}
		else {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("bump.wav"), NULL, SND_SYNC);
			backsound = false;
		}
	}

	glutPostRedisplay();


}

void timeN(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{

	if (fz < 1)
		fz += 0.1;
	else {
		fz = 0;
		if (fy < 1)
			fy += 0.1;
		else {
			fy = 0;
			if (fx < 1)
				fx += 0.1;
			else
				fx = 0;
		}
	}

	if (timer > 0)
		timer -= 0.5;
	else {
		timesup = true;
	}
		//recall the time function after 1000 ms and pass a zero value as an input to the time func.
	
	glutPostRedisplay();
	glutTimerFunc(500, timeN, 0);

}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("OpenGL - 3D Template");
	glutDisplayFunc(Display);


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	glutIdleFunc(Anim);
	glutSpecialFunc(spe);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(0, timeN, 0);

	glutMainLoop();
}
