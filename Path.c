/* Function that returns if a line (x1, y1) -> (x2, y2) intersects the circle (cx, cy) with radius */
bool doesPathIntersectObstacle(float x1, float y1, float x2, float y2, float cx, float cy, float radius)
{
		if(x2 == x1)
			if(y1+5 > cy && cy > y2-5)
				return true;
			else if(y2+5 > cy && cy > y1 - 5)
				return true;

		if( (cx > x1+radius && cx > x2+radius) || (cy > y1+radius && cy > y2+radius) || (cx < x1-radius && cx < x2-radius) || (cy < y1-radius && cy < y2-radius) )
		{
			return false;
		}

		//Find Slope of line
		float slope = (y2 - y1) / (x2 - x1);

		//Find y-intercept of original slope
		float yintercept = y1 - slope*x1;

		//Find tangent line of slope
		float c_slope = -1 / slope;

		//Find y-intercept of tangent line
		float c_yintercept = cy - c_slope*cx;

		//Find intersection between two lines
		float xIntersect = (c_yintercept - yintercept) / (slope - c_slope);
		float yIntersect = slope * xIntersect + yintercept;

		//Find Distance between the obstacle point (cx, cy) and the newly found point (xInter, yInter);
		float distance = sqrt( pow(xIntersect - cx, 2) + pow(yIntersect - cy, 2) );

		//Is the distance within the radius of the circle?
		if(distance <= radius)
			return true;//We are intersecting an obstacle
		else
			return false;//We are not intersecting an obstacle

}
