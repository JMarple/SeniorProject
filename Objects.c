//Objects

typedef struct
{
	//Position Coordinents
	float x;
	float y;

	//Collision Radius
	float radius;
}Obstacle;


typedef struct
{
	//Position
	float x;
	float y;

}Target;

typedef struct
{
	float data;
}Data;

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

	//Turn using encoders
	TurnEncoder = 2,

	//Turn using gyro
	TurnGyro = 3

}ControlType;
