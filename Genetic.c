bool doesPathReachEndPoint(Target testPoint, Target endPoint, Obstacles obst);
float calculateCost(int pathNum, float gValueStraight, float gValueTurn);

/* Function that initilizes the path array for the path finding genetic algorithm */
void initializePaths(Target startPoint, Target endPoint, Obstacles obst)
{
	//Reset entire array to -1's
	for(int i = 0; i < GENETIC_SIZE; i++)
	{
		for(int j = 0; j < MAX_PATH_SIZE; j++)
		{
			paths[i].point[j].x = -1;
			paths[i].point[j].y = -1;
		}
	}
	//Go through and create a new path
	for(int i = 0; i < GENETIC_SIZE; i++)
	{
		//Init the first point to be the default starting point
		paths[i].point[0].x = startPoint.x;
		paths[i].point[0].y = startPoint.y;

		//Go through each point of each path
		for(int j = 0; j < MAX_PATH_SIZE-1; j++)
		{

			//Check to see if the last point can reach the endpoint without hitting anything
			if( doesPathReachEndPoint(paths[i].point[j], endPoint, obst) )
			{
				paths[i].point[j+1].x = endPoint.x;
				paths[i].point[j+1].y = endPoint.y;
				break;
			}
			//Assign a new point
			else
			{
				while(true)
				{
					//Assign new random point
					paths[i].point[j+1].x = random(FIELD_WIDTH);
					paths[i].point[j+1].y = random(FIELD_HEIGHT);

					bool flag = true;
					//CHECK FOR COLLISION
					for(int k = 0; k < OBSTACLE_COUNT; k++)
					{
						//Check first to see if there is a clear path from current point to last point
						if(doesPathIntersectObstacle(paths[i].point[j+1].x, paths[i].point[j+1].y, paths[i].point[j].x, paths[i].point[j].y, obst.point[k].x, obst.point[k].y, obst.point[k].radius))
						{
							flag = false;
						}
					}
					if(flag)
						break;
				}
			}
		}

		//Calculate how quick and efficient this newly found path is
		paths[i].cost = calculateCost(i, 10, 1);
	}
}

/* Calculate Costs */
float calculateCost(int pathNum, float gValueStraight, float gValueTurn)
{
	//variable to keep track of sum of costs
	float totalCost = 0.0;

	//Loop through each path to calculate cost
	for(int j = 0; j < MAX_PATH_SIZE-1; j++)
	{
		//check to make sure the path hasn't ended
		if(paths[pathNum].point[j].x != -1 && paths[pathNum].point[j].y != -1)
		{
			totalCost += gValueTurn * radiansToDegrees( atan2(paths[pathNum].point[j+1].y - paths[pathNum].point[j].y, paths[pathNum].point[j+1].x - paths[pathNum].point[j].x));
			totalCost += gValueStraight * sqrt( pow(paths[pathNum].point[j].x - paths[pathNum].point[j+1].x, 2) + pow(paths[pathNum].point[j].y - paths[pathNum].point[j+1].y, 2) );
		}
		else
		{
			break;
		}
	}

	return totalCost;
}

/* Check Every obstacle to see if there is any intersections */
bool doesPathReachEndPoint(Target testPoint, Target endPoint, Obstacles obst)
{
	//CHECK FOR FINAL PATH
	for(int k = 0; k < OBSTACLE_COUNT; k++)
	{
		//Check first to see if there is a clear path from current point to last point
		if( doesPathIntersectObstacle(testPoint.x, testPoint.y, endPoint.x, endPoint.y, obst.point[k].x, obst.point[k].y, obst.point[k].radius))
		{
			return false;//There was an intersection :(
		}
	}

	//No path intersecting any obstacle, all set!
	return true;
}


/* Function that copies the path to the target */
void copyPath(Path tar, Path A)
{
	//Copy all the information to the new target
	for(int i = 0; i < MAX_PATH_SIZE; i++)
	{
		tar.point[i].x = A.point[i].x;
		tar.point[i].y = A.point[i].y;
	}
	tar.cost = A.cost;
}


void saveBestPaths()
{
	for(int i = 0; i < 2; i ++)
	{
		for(int j = 0; j < MAX_PATH_SIZE; j++)
		{
			bestPaths[i].point[j].x = -1;
			bestPaths[i].point[j].y = -1;
		}
	}
	bestPaths[0].cost = 999999999;
	bestPaths[1].cost = 999999999;

	//Loop through each path and see if it makes top two
	for(int i = 0; i < GENETIC_SIZE; i++)
	{
		if(paths[i].cost < bestPaths[1].cost)
		{
			if(paths[i].cost < bestPaths[0].cost)
			{
				copyPath(bestPaths[0], paths[i]);
			}
			else
			{
				copyPath(bestPaths[1], paths[i]);
			}
		}
	}

	//reset the path
	for(int i = 0; i < GENETIC_SIZE; i++)
	{
		for(int j = 0; j < MAX_PATH_SIZE; j++)
		{
			paths[i].point[j].x = -1;
			paths[i].point[j].y = -1;
		}
		paths[i].cost = -1;
	}

}




/* Function that takes bestPaths and creates new paths to be used/tested again */
void breedNewValues(float crossover, float mutate, Target startPoint, Target endPoint, Obstacles obst)
{
	//Copy best paths back to the main path array
	copyPath(paths[0], bestPaths[0]);
	copyPath(paths[1], bestPaths[1]);

	//Go through each path and generate something new
	for(int i = 2; i < GENETIC_SIZE; i++)
	{
		//Set default start
		paths[i].point[0].x = startPoint.x;
		paths[i].point[0].y = startPoint.y;

		//Go through each point
		for(int j = 0; j < MAX_PATH_SIZE-1; j++)
		{

			//check to see if the current point can go to end
			if( doesPathReachEndPoint(paths[i].point[j], endPoint, obst) )
			{
				paths[i].point[j+1].x = endPoint.x;
				paths[i].point[j+1].y = endPoint.y;
				break;
			}

			//Flag for seeing if we should mutate instead of cross over
			bool mutate = true;

			//if random value calls for cross over
			if( mutate > random(crossover + mutate) )
			{
				//Set mutation to false for now
				mutate = false;

				//Variables to add to the X/Y coordinantes to get better results
				int addX = (int)random(6)-3;
				int addY = (int)random(6)-3;

				//Add extra paramaters to the path temporarily
				bestPaths[0].point[j+1].x += addX;
				bestPaths[0].point[j+1].y += addY;
				bestPaths[1].point[j+1].x += addX;
				bestPaths[1].point[j+1].y += addY;

				//Check Paths to see if the path we want to try is possible
				bool pathA = false;
				if(bestPaths[0].point[j+1].x+addX>=0 && bestPaths[0].point[j+1].y+addY>=0)
					pathA = doesPathReachEndPoint(bestPaths[0].point[j+1], paths[i].point[j], obst);
				bool pathB = false;
				if(bestPaths[1].point[j+1].x+addX>=0 && bestPaths[1].point[j+1].y+addY>=0)
					pathB= doesPathReachEndPoint(bestPaths[1].point[j+1], paths[i].point[j], obst);

				//Remove what we added before to get our original result
				bestPaths[0].point[j+1].x -= addX;
				bestPaths[0].point[j+1].y -= addY;
				bestPaths[1].point[j+1].x -= addX;
				bestPaths[1].point[j+1].y -= addY;

				//Randomly go between the two best paths
				if(5 > random(10) )
				{
					if(pathA)
					{
						paths[i].point[j+1].x = bestPaths[0].point[j+1].x + addX;
						paths[i].point[j+1].y = bestPaths[0].point[j+1].y + addY;
					}
					else if(pathB)
					{
						paths[i].point[j+1].x = bestPaths[1].point[j+1].x + addX;
						paths[i].point[j+1].y = bestPaths[1].point[j+1].y + addY;
					}
					else
					{
						mutate = true;
					}
				}
				else
				{
					if(pathB)
					{
						paths[i].point[j+1].x = bestPaths[1].point[j+1].x + addX;
						paths[i].point[j+1].y = bestPaths[1].point[j+1].y + addY;
					}
					else if(pathA)
					{
						paths[i].point[j+1].x = bestPaths[0].point[j+1].x + addX;
						paths[i].point[j+1].y = bestPaths[0].point[j+1].y + addY;
					}
					else
					{
						mutate = true;
					}
				}
			}
			//Mutate!
			if(mutate)
			{
				//Keep looping until we find a suitable path to use
				while(true)
				{
					//Assign new random point
					paths[i].point[j+1].x = random(FIELD_WIDTH);
					paths[i].point[j+1].y = random(FIELD_HEIGHT);

					bool flag = true;
					//CHECK FOR COLLISION
					for(int k = 0; k < OBSTACLE_COUNT; k++)
					{
						//Check first to see if there is a clear path from current point to last point
						if(doesPathIntersectObstacle(paths[i].point[j+1].x, paths[i].point[j+1].y, paths[i].point[j].x, paths[i].point[j].y, obst.point[k].x, obst.point[k].y, obst.point[k].radius))
						{
							flag = false;
						}
					}
					if(flag)
						break;
				}
			}

		}

		paths[i].cost = calculateCost(i, 10, 1);

	}
}
