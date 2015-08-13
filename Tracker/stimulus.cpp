#include "stdafx.h"
#include "stimulus.h"
#include "freeglut.h"
#include "timer.h"
#include <math.h>


// This must be declared as a global variable to work with the GLUT rendering function
extern FlyPosition fly_position;

void drawCylinderBarsES()
{
	static double time_in_ms = get_counter();
	glLoadIdentity();
	glFlush();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//float startpos = Stimulus.spacing; // degrees, where first bar is drawn
	double startpos = 180;
	double startpos_i;
	double width = 1; // degrees
	double direction = 1; // Sign
	double r = 1000; // arbitrary radius, doesn't matter for now since everything else is in degrees
	double added; // 090302, added this to get rid of stimrot.mean rotation, not useful for me here...

	startpos_i = 0.01 * (time_in_ms)* direction;

	double height = 5 * r; // arbitrary number just to cover the screen
	//float x1;
	//float z1;
	//float x2;
	//float z2;


	int spacing_factor = 5;
	for (int i = 0; i < 360.1 / (abs(width)*spacing_factor); i++)
	{

		double x1 = r*cos(startpos_i*3.14159 / 180);
		double z1 = -r*sin(startpos_i*3.14159 / 180);
		double x2 = r*cos((startpos_i - width)*3.14159 / 180);
		double z2 = -r*sin((startpos_i - width)*3.14159 / 180);

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

	SwapBuffers(NULL);
	return;
};
