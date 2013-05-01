//Objects

typedef struct
{
	//Position Coordinents
	float x;
	float y;

	//Collision Radius
	float radius;
}Obstacle;

//Work around for robotC glitch for passing arrays
typedef struct
{
	//Array of obstacles
	Obstacle point[OBSTACLE_COUNT];

}Obstacles;

typedef struct
{
	//Position
	float x;
	float y;

}Target;

/* Structure that holds a set of Targets */
typedef struct
{
	Target point[MAX_PATH_SIZE];
	float cost;
}Path;

//Generate a new point
void newTarget(Target tar, int x, int y)
{
	tar.x = x;
	tar.y = y;
}

/* Structures */
typedef struct{

	//Updating values
	float Error;
	float Integral;
	float Derivative;
	float PreviousError;
	float IntegralMax;

	//PID constants
	float P;
	float I;
	float D;

	//Timer Checks
	long maxTime;
	int counter;
}PID;// Used for proportional loops

typedef enum
{
	//Drive Straight, don't check for left/right error
	StraightEncoder = 0,

	//Drive Straight, check for when one wheel goes faster then the other and correct
	StraightEncoderCorrect = 1,

	//Drive Straight, check to make sure we're going at the right heading using gyro info
	StraightGyroCorrect = 4,

	//Turn using encoders
	TurnEncoder = 2,

	//Turn using gyro
	TurnGyro = 3

}ControlType;
