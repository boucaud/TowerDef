#include "cursor.h"
 
 
void showCursor(cursor *c, char *grid, camera *cam, tower *tow) //displays C in the VRAM
{
	textBar name = {2, 54, 124, 10, NULL, 0};
	if(grid[c->gridY * GRID_LENGTH + c->gridX] == 0 || grid[c->gridY * GRID_LENGTH + c->gridX] == 6)
		ML_rectangle(c->gridX*9 - cam->x -1, c->gridY*9 - cam->y - 1, (c->gridX+1)*9 - cam->x - 1, (c->gridY+1)*9 - cam->y - 1, 1, BLACK, TRANSPARENT);
	else
		ML_rectangle(c->gridX*9 - cam->x - 1, c->gridY*9 - cam->y - 1, (c->gridX+1)*9 - cam->x - 1, (c->gridY+1)*9 - cam->y - 1, 1, BLACK, CHECKER);
	if(tow == NULL) return;
	if(grid[c->gridY * GRID_LENGTH + c->gridX] == 6)
	{
		ML_circle(c->gridX*9 - cam->x +4, c->gridY*9-cam->y +4, findTowerXY(c->gridX, c->gridY, tow)->range, CHECKER);
		name.text = findTowerXY(c->gridX, c->gridY, tow)->name;
		name.show = 1;
		showTextBar(&name);
	}
}

int moveCursor(cursor* c, camera *cam, char *grid, tower** towers, mob *mobs, int *money) //detecs the pressed keys and moves the cursor
{
	int towerId = -1, returned = -1, i = 0;
	if(KeyDown(K_LEFT) && c->gridX > 0)
	{
		c->gridX--;
		if(cam->x / 9 > c->gridX)
			cam->x-= 9;
	}
	if(KeyDown(K_RIGHT) && c->gridX < GRID_LENGTH -1)
	{
		c->gridX++;
		if((cam->x + 128)/ 9 < (c->gridX +1))
			cam->x+= 9;
	}
	if(KeyDown(K_UP) && c->gridY > 0)
	{
		c->gridY--;
		if(cam->y / 9 > c->gridY)
			cam->y -= 9;
	}
	if(KeyDown(K_DOWN) && c->gridY < GRID_WIDTH -1)
	{
		c->gridY++;
		if((cam->y + 64)/9 < (c->gridY+1))
			cam->y += 9;
	}
	if(KeyDown(K_EXE) && grid[c->gridY * GRID_LENGTH + c->gridX]==6)
	{
		returned = openTowerEditionMenu(*c, cam, grid, *towers, mobs, money);
		while(KeyDown(K_EXE))
		{}
	}
	if(KeyDown(K_EXE) && grid[c->gridY * GRID_LENGTH + c->gridX]==0)
	{
		towerId = openTowerSelectionMenu(*c, cam, grid, *towers, mobs, money);
		while(KeyDown(K_EXE))
		{}
	}
	if(returned != -1)
	{
		if(returned == 4)
		{
			*towers = removeTower(findTowerXY(c->gridX, c->gridY, *towers), *towers);
			grid[c->gridY * GRID_LENGTH + c->gridX] = 0;
		}
	}
	if(towerId != -1)
	{
		*towers = addTower(c->gridX, c->gridY, towerId, *towers);
	}
	return towerId;
}
