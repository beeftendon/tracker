#include "stdafx.h"
#include "stimulus.h"
#include "freeglut.h"
#include "timer.h"
#include <math.h>

void change_size(int w, int h)
{
	float ratio;

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void draw_cylinder_bars()
{
	double time_in_ms = get_counter();
	
	glLoadIdentity();
	glFlush();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	double aspect_ratio = 640 / 360;
	double frustum_width = 200;
	//float startpos = Stimulus.spacing; // degrees, where first bar is drawn
	double startpos = 180;
	double startpos_i;
	double width = 1; // degrees
	double direction = -1; // Sign
	double r = 100; // arbitrary radius, doesn't matter for now since everything else is in degrees
	double added; // 090302, added this to get rid of stimrot.mean rotation, not useful for me here...

	glutSetWindow(window1);
	
	gluLookAt(fly_position.x, 0, fly_position.y, 0, 0, -9999999999, 0, 1, 0);
	glFrustum(-frustum_width / 2, frustum_width / 2, -(frustum_width*aspect_ratio) / 2, (frustum_width*aspect_ratio) / 2, 100, 10000.0);

	startpos_i = 0.01 * (time_in_ms)* direction;

	double height = 10 * r; // arbitrary number just to cover the screen

	int spacing_factor = 2;
	
	for (int i = 0; i < 360.1 / (abs(width)*spacing_factor); i++)
	{

		float x1 = r*cos(startpos_i*3.14159 / 180);
		float z1 = -r*sin(startpos_i*3.14159 / 180);
		float x2 = r*cos((startpos_i - width)*3.14159 / 180);
		float z2 = -r*sin((startpos_i - width)*3.14159 / 180);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 1);
		glBegin(GL_QUADS);
		// Draw the vertices in CCW order
		glVertex3f(x1, height / 2, z1); // top left
		glVertex3f(x1, -height / 2, z1); // bottom left
		glVertex3f(x2, -height / 2, z2); // bottom right
		glVertex3f(x2, height / 2, z2); // top right
		glEnd();

		startpos_i -= spacing_factor * width;


		//TrackStim::drawWedge(i*(2 * width) - width / 2 + added, width);
	};

	//glutPostRedisplay();
	//glutSwapBuffers();
	
	//glutSetWindow(window2);
	
	//gluLookAt(0, 0, 200, 0, 0, -9999999999, 0, 1, 0);
	//glFrustum(-frustum_width / 2, frustum_width / 2, -(frustum_width*aspect_ratio) / 2, (frustum_width*aspect_ratio) / 2, 100, 10000.0);
	/*
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 1);
	glBegin(GL_QUADS);
	// Draw the vertices in CCW order
	glVertex3f(-50, 50, -100); // top left
	glVertex3f(-50, -50, -100); // bottom left
	glVertex3f(50, -50, -50); // bottom right
	glVertex3f(50, 50, -10); // top right
	glEnd();
	*/
	glutSetWindow(window1);
	glutPostRedisplay();

	glutSwapBuffers();
	
	return;
};
