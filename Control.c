bool canStillRunPID(PID pid, int error, bool accuracyCheck);
void setDriveMotor(int driveLeft, int driveRight);
int clipNum(int num, int low, int high);
int calculatePID(PID pid, int error);

/* Function that allows for basic driving abilities */
void Drive(ControlType controlType, int encoderLeft, int encoderRight, int speedLeft, int speedRight, bool accuracyCheck)
{
	//Reset Sensors & Timers
	SensorValue[LeftEncoder] = 0;
	SensorValue[RightEncoder] = 0;
	time1[T1] = 0;

	/* Drive Straight with no left/right wheel correction */
	if(controlType == StraightEncoder)
	{
		//Initial PID Values
		PID kPID;
		kPID.P = 2;
		kPID.I = 0.03;
		kPID.D = 3;
		kPID.IntegralMax = 500;
		kPID.Error = 10000;
		kPID.maxTime = 10000;

		//Run through PID until robot has reached goal
		while(canStillRunPID(kPID, 5, accuracyCheck))
		{
			//Calculate Speed of wheels
			int speed = calculatePID(kPID,
				(SensorValue[LeftEncoder] - SensorValue[RightEncoder])/2 - (encoderLeft + encoderRight)/2*STAIGHT_CONV);


			//Update Motors
			setDriveMotor(clipNum(speed, -speedLeft, speedLeft), clipNum(speed, -speedRight, speedRight));

			//Prevent CPU Hog
			wait1Msec(5);
		}

	}
	/* Turn using encoders */
	else if(controlType == TurnEncoder)
	{
		//Initial PID Values
		PID kPID;
		kPID.P = 5;
		kPID.I = 0;
		kPID.D = 0;
		kPID.IntegralMax = 500;
		kPID.Error = 10000;
		kPID.maxTime = 10000;

		//Run through PID until robot has reached goal
		while(canStillRunPID(kPID, 5, accuracyCheck))
		{
			//Calculate Speed of wheels using errors
			int speed = calculatePID(kPID,
				encoderLeft*TURN_CONV - (SensorValue[LeftEncoder] + SensorValue[RightEncoder])/2 );

			//Update Motors
			setDriveMotor(speed, -speed);

			//Prevent CPU Hog
			wait1Msec(5);
		}
	}
}

/* Function that waits for a button to be pressed */
void WaitForButton()
{
	while(SensorValue[InputButton] == 1){}
}


/* Update Drive Motors */
void setDriveMotor(int driveLeft, int driveRight)
{
	//Clip Numbers
	driveLeft = clipNum(driveLeft, -127, 127);
	driveRight = clipNum(driveRight, -127, 127);

	//Update Motors
	motor[LeftDrive1] = motor[LeftDrive2] = driveLeft;
	motor[RightDrive1] = motor[RightDrive2] = driveRight;
}

//Limit a number between low and high
int clipNum(int num, int low, int high)
{
	if(num<=low)
		return low;
	else if(num>=high)
		return high;
	else
		return num;
}

//Figure out if we can still run the PID loop
bool canStillRunPID(PID pid, int error, bool accuracyCheck)
{
	//Check for PID timeout error
	if(pid.maxTime < time1[T1])
	{
		return false;
	}
	//Check to see if the error is low enough to quit
	if(abs(pid.Error) <= error)
	{
		pid.counter ++;
		if(pid.counter >= 50 || accuracyCheck == FALSE)
		{
			return false;
		}
	}
	else
	{
		pid.counter = 0;
	}

	return true;
}

/* Function that returns PID values */
int calculatePID(PID pid, int error)
{
	//Proportional
	pid.Error = error;

	//Integral
	pid.Integral = pid.Integral + pid.Error;

	if(pid.IntegralMax!=-1)
	{
		pid.Integral = clipNum(pid.Integral, -pid.IntegralMax, pid.IntegralMax);
	}

	//Derivative
	pid.Derivative = pid.PreviousError - pid.Error;
	pid.PreviousError = pid.Error;

	//Return result
	return (pid.Error*pid.P) + (pid.Integral*pid.I) + (pid.Derivative*pid.D);
}
