struct FlyPosition
{
	double x=0;
	double y=0;
	double theta=0;
};

// This must be declared as a global variable to work with the GLUT rendering function
extern FlyPosition fly_position;