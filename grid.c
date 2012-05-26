#include "grid.h"


unsigned char grassLeft[] = {0x80, 0x80, 0x80, 0x40, 0x80, 0x80, 0x80, 0x80};

unsigned char grassUp[] = {0xF7, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char grassRight[] = {0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01};

unsigned char grassDown[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xEF};

unsigned char road[] = {0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x00};

void showGrid(char *grid, camera *cam) //displays the whole grid in the VRAM
{
	int i = 0, j = 0;
	int n = 0;
	//masque:
	ML_rectangle(0, 0, 128, 64, 0, 0, CHECKER);
	ML_rectangle(-cam->x, -cam->y, -cam->x + GRID_LENGTH*9, -cam->y + GRID_WIDTH*9, 1, BLACK, WHITE);
	for(i=0; i < GRID_LENGTH && i < (cam->x + 128)/9; i++)
	{
		for(j=0; j < GRID_WIDTH && j < (cam->y + 64)/9; j++)
		{
			n = 0;
			if(grid[j * GRID_LENGTH + i] == 0 || grid[j * GRID_LENGTH + i] == 6)
			{
				
				if(i > 0 && grid[j * GRID_LENGTH + i - 1] >= 1 && (grid[j * GRID_LENGTH + i - 1] < 6 || grid[j * GRID_LENGTH + i - 1]>6) )
				{
					ML_bmp_8_or_cl(grassLeft, i * 9 - cam->x, j * 9 - cam->y);
					n = 1;
				}
				if(i < GRID_LENGTH -1 && grid[j * GRID_LENGTH + i + 1] >= 1 && (grid[j * GRID_LENGTH + i + 1] < 6 ||grid[j * GRID_LENGTH + i + 1]>6))
				{
					n = 1;
					ML_bmp_8_or_cl(grassRight, i * 9 - cam->x, j * 9 - cam->y);
				}
				if(j > 0 && grid[(j - 1) * GRID_LENGTH + i] >= 1 && (grid[(j - 1) * GRID_LENGTH + i] <6 || grid[(j - 1) * GRID_LENGTH + i]>6))
				{
					n = 1;
					ML_bmp_8_or_cl(grassUp, i * 9 - cam->x, j * 9 - cam->y);
				}
				if(j < GRID_WIDTH -1 && grid[(j + 1) * GRID_LENGTH + i] >= 1 && (grid[(j + 1) * GRID_LENGTH + i] < 6 || grid[(j + 1) * GRID_LENGTH + i] > 6))
				{
					n = 1;
					ML_bmp_8_or_cl(grassDown, i * 9 - cam->x, j * 9 - cam->y);
				}
			}
			if(grid[j * GRID_LENGTH + i] > 0 && (grid[j * GRID_LENGTH + i] < 6 || grid[j * GRID_LENGTH + i]  > 6))
			{
				ML_bmp_8_or_cl(road, i * 9 - cam->x, j * 9 - cam->y);
			}
		}
	}
}
