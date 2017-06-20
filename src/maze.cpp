#include "..\include\maze.h"

char mazeData[MAZE_HEIGHT][MAZE_WIDTH] = 
{
	{ 'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W' },
	{ 'W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W' },
	{ 'W',' ','W',' ','W','W','W',' ','W',' ','W',' ',' ',' ',' ','W' },
	{ 'W',' ','W','W',' ',' ','W',' ','W','W',' ','W',' ','W',' ','W' },
	{ 'W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ','W' },
	{ 'W',' ','W','W','W','W','W','W','W','W',' ','W','W','W',' ','W' },
	{ 'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ','W' },
	{ 'W',' ','W','W','W','W','W',' ','W','W','W',' ','W','W','W','W' },
	{ 'W',' ','W',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ','W' },
	{ 'W',' ',' ',' ','W','W','W','W','W','W','W',' ',' ',' ',' ','W' },
	{ 'W',' ','W',' ',' ',' ','W',' ',' ',' ','W',' ',' ','W',' ','W' },
	{ 'W',' ','W','W','W','W','W',' ','W','W','W','W',' ','W',' ','W' },
	{ 'W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ','W' },
	{ 'W',' ',' ','W','W',' ','W','W','W','W',' ','W','W','W',' ','W' },
	{ 'W',' ',' ',' ','W',' ','W',' ',' ',' ',' ','W',' ',' ',' ','W' },
	{ 'W','W','W','W','W','W','W','W','W','W','W','W','W',' ','W','W' },
};

 /*O----------------------------------------------------------------------->x axis
   |{ 'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W' }
   |{ 'W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W' }
   |{ 'W',' ','W',' ','W','W','W',' ','W',' ','W',' ',' ',' ',' ','W' }
   |{ 'W',' ','W','W',' ',' ','W',' ','W','W',' ','W',' ','W',' ','W' }
   |{ 'W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ','W' }
   |{ 'W',' ','W','W','W','W','W','W','W','W',' ','W','W','W',' ','W' }
   |{ 'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ','W' }
   |{ 'W',' ','W','W','W','W','W',' ','W','W','W',' ','W','W','W','W' }
   |{ 'W',' ','W',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ','W' }
   |{ 'W',' ',' ',' ','W','W','W','W','W','W','W',' ',' ',' ',' ','W' }
   |{ 'W',' ','W',' ',' ',' ','W',' ',' ',' ','W',' ',' ','W',' ','W' }
   |{ 'W',' ','W','W','W','W','W',' ','W','W','W','W',' ','W',' ','W' }
   |{ 'W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ','W' }
   |{ 'W',' ',' ','W','W',' ','W','W','W','W',' ','W','W','W',' ','W' }
   |{ 'W',' ',' ',' ','W',' ','W',' ',' ',' ',' ','W',' ',' ',' ','W' }
   |{ 'W','W','W','W','W','W','W','W','W','W','W','W','W',' ','W','W' }
   |
   |
   v
   z axis*/
