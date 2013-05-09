/* Function that drives a robot from point A to point B */
void driveToPoint(Target startPoint, Target endPoint)
{
	//Determine angle to be turned between points
	float deg = radiansToDegrees(
								atan2(endPoint.y - startPoint.y, endPoint.x - startPoint.x));

	//Determine length of path
	float len = sqrt( pow(endPoint.y - startPoint.y, 2) + pow(endPoint.x - startPoint.x, 2) );

	Drive(TurnGyro, deg, 0, 80, 80, true);
	Drive(StraightGyroCorrect, len, deg, 127, 127, true);
}
