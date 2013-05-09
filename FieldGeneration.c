/*****************************************/
/* FieldGeneration.c                     */
/* Date Started: April 23rd 2013         */
/* Purpose: A file that can generate or  */
/*          reassign fields of obstacles */
/*          for the robot to read off of.*/
/*****************************************/



void generateObstacles(int preset, Obstacles obst)
{
	switch(preset)
	{
		/* Assign Random Values */
		case -1:
			//Go through each point and create random x, y, and radiuses
			for(int i = 0; i < OBSTACLE_COUNT; i++)
			{
				obst.point[i].x = (int)rand();
				obst.point[i].y = (int)rand();
				obst.point[i].radius = (int)rand();
			}
			break;

		/* Preset Field 0 */
		case 0:
			float globalradius = 5.0;

			obst.point[0].x = 50; obst.point[0].y = 45; obst.point[0].radius = globalradius;
			obst.point[1].x = 20; obst.point[1].y = 20; obst.point[1].radius = globalradius;
			obst.point[2].x = 60; obst.point[2].y = 10; obst.point[2].radius = globalradius;
			obst.point[3].x = 40; obst.point[3].y = 15; obst.point[3].radius = globalradius;
			obst.point[4].x = 20; obst.point[4].y = 30; obst.point[4].radius = 10;
			obst.point[5].x = 30; obst.point[5].y = 50; obst.point[5].radius = 10;
			obst.point[6].x = 25; obst.point[6].y = 15; obst.point[6].radius = 10;
			break;
		default:
			break;


	}

}
