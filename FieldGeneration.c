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
			float globalradius = 2.0;

			obst.point[0].x = 0; obst.point[0].y = 25; obst.point[0].radius = globalradius;
			obst.point[1].x = 0; obst.point[1].y = 25; obst.point[1].radius = globalradius;
			obst.point[2].x = 0; obst.point[2].y = 25; obst.point[2].radius = globalradius;
			obst.point[3].x = 0; obst.point[3].y = 25; obst.point[3].radius = globalradius;
			obst.point[4].x = 0; obst.point[4].y = 25; obst.point[4].radius = globalradius;
			obst.point[5].x = 0; obst.point[5].y = 25; obst.point[5].radius = globalradius;

			break;
		default:
			break;


	}

}
