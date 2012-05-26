#include "level.h"

level *createLevel(int index)
{
	level *new = malloc(sizeof(level));
	if(index == 0)
	{
		/*char grid[8*9] = {
						7, 1, 1, 5, 0, 0, 0, 0, 
						0, 0, 0, 1, 0, 0, 0, 0,
						0, 0, 0, 3, 1, 1, 5, 0,
						0, 0, 0, 0, 0, 0, 1, 0,
					    5, 1, 1, 1, 2, 0, 1, 0,
					    1, 0, 0, 0, 4, 1, 2, 0,
					    3, 1, 5, 0, 0, 0, 0, 0,
					    0, 0, 1, 0, 0, 0, 0, 0,
					    0, 0, 8, 0, 0, 0, 0, 0
					     };*/
					     //24*24
		char grid[24*24] = {
					    7, 1, 1, 1, 5, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 0, 0,
					    0, 0, 0, 0, 1, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 3, 1, 5, 0,
					    0, 5, 1, 1, 2, 0, 0, 0 ,3 ,1 ,1 ,1 ,1, 1, 1 ,1, 1 ,5 ,0, 0, 1, 0, 1, 0,
					    0, 1, 0, 0, 0, 0, 0, 0 ,1 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,1 ,0, 0, 1, 0, 1, 0,
					    0, 1, 0, 0, 0, 0, 0, 0 ,1 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,1 ,0, 0, 1, 0, 1, 0,
					    0, 1, 0, 3, 1, 1, 1, 1 ,4 ,0 ,0 ,0 ,5, 1, 2 ,0, 0 ,1 ,0, 0, 1, 0, 1, 0,
					    0, 1, 0, 1, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,1, 0, 1 ,0, 0 ,1 ,0, 0, 1, 0, 1, 0,
					    0, 1, 0, 1, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,1, 0, 4 ,1, 1 ,2 ,0, 0, 1, 0, 1, 0,
					    0, 3, 5, 1, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,1, 0, 0 ,0, 0 ,0 ,0, 0, 1, 0, 1, 0,
					    0, 0, 3, 4, 0, 5, 1, 1 ,1 ,1 ,2 ,0 ,1, 0, 0 ,0, 0 ,0 ,0, 0, 1, 0, 1, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,1 ,0 ,1, 0, 0 ,0, 0 ,0 ,0, 0, 1, 0, 1, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,1 ,0 ,1, 0, 0 ,0, 0 ,0 ,0, 0, 1, 0, 1, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,1 ,0 ,3, 1, 1 ,1, 1 ,1 ,1, 1, 4, 0, 1, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,1 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 1, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,1 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 1, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,1 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 1, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,4 ,1 ,1, 1, 1 ,1, 1 ,1 ,1, 1, 1, 1, 2, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 0, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 0, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 0, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 0, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 0, 0,
					    0, 0, 0, 0, 0, 1, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 0, 0,
					    0, 0, 0, 0, 0, 8, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0 ,0, 0 ,0 ,0, 0, 0, 0, 0, 0};
					    
		new->width = 24;
		new->length = 24;
		new->grid = malloc(sizeof(char)*new->width * new->length);
		memcpy(new->grid, &grid, sizeof(char)*new->width * new->length);
		new->difficulty = 0;
		new->mobs = NULL;
		new->towers = NULL;
	}
	else if(index == 1)
	{
	
	}
	new->wave = 0;
	return new;
}
