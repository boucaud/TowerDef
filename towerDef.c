#include "structures.h"
#include "level.h"
#include "fxlib.h"
#include "stdlib.h"
#include "MonochromeLib.h"
#include "ECode.h"
#include "assert.h"
#include "syscall.h"
#include "stdlib.h"
#include "tower.h"
#include "towerSelection.h"
#include "grid.h"
#include "cursor.h"
#include "mob.h"
#include "ui_fonctions.h"
#include "text.h"

/*TODO:
Affichage des tirs plus esthétiques, et un tir pour chaque tourelle
Système d'explosions
gestion unique de chaque tourelle

Barre de vie des mobs FAIT
Arrivée/Départ de mobs FAIT
Système de vagues VAGUES FAITES, RESTE A GERER L'ALEATOIRE
Vague IA de la tourelle FAIT (pas dur)
Gestion de niveaux FAIT (basique, comme Dead Labs)
Différentes vitesses de mobs FAIT
*/
/*unsigned char tower1[] = {0x00, 0x30, 0x4E, 0x42, 0x22, 0x22, 0x3C, 0x00};

unsigned char tower2[] = {0x00, 0x3C, 0x24, 0x42, 0x42, 0x42, 0x3C, 0x00};

unsigned char tower3[] = {0x00, 0x58, 0x18, 0x66, 0x66, 0x18, 0x1A, 0x00};*/


//27 * 16



//concu pour des cases de 9*9 (0 1,2,3,4,5,6,7,8)
//0 = tourelle placable
//1 = chemin des mobs, tourelles non placables
//de 2 à 5: changements de direction
//6: tourelle
//7: Départ
//8: Arrivée
int tick()
{
	int i = 0, j = 0, n = 0;
	int pause = 0;
	int money = 100;
	camera cam = {0, 0};
	level *lev = createLevel(0);
	cursor c = {0, 0};
	int sleep = 15;
    mob *mobs = NULL;
	int counter = 0;
	unsigned int fps = 0, frame = 0, tempsOrigine = RTC_GetTicks();
	unsigned char fps_text[8] = {0};
	dot gridStart = {0, 0};
	dot gridEnd = {0, 0};
	text *texts = NULL;
	/*creation of the towers list*/
	//int nbTowerSlots = getNbTowerSlots(grid);
	//tower* towers_list = NULL;
	mobs = addWave(0, 0, 1, 9, 100, mobs);
	//searching the start and the end:
	for(i = 0; i < GRID_LENGTH; i++)
	{
		for(j = 0; j < GRID_WIDTH; j++)
		{
			if(lev->grid[j * GRID_LENGTH + i] == 8)
			{
				gridEnd.x = i;
				gridEnd.y = j;
			}
			if(lev->grid[j * GRID_LENGTH + i] == 8)
			{
				gridStart.x = i;
				gridStart.y = j;
			}
		}
	}
	
	while(1)
	{
		//fps
		if(RTC_GetTicks() - tempsOrigine >= 32 )//si 1/4 de seconde s'est ecoule
		{
			fps = frame*4;
			frame = 0;
			tempsOrigine = RTC_GetTicks();
		}
		frame++;

		//actions
		if(pause == 0)
		{
			mobs = moveAllMobs(mobs, lev->grid, counter, gridEnd, lev->towers);
			mobs = checkMobsLife(mobs, lev->towers, &money, &texts);
		}
		if(!(counter % 2))
		{
			if(KeyDown(K_F1))mobs = addWave(0, 0, 1, 9, 100, mobs);
			if(KeyDown(K_F2))mobs = addWave(0, 0, 10, 9, 100, mobs);
			moveCursor(&c, &cam, lev->grid, &(lev->towers), mobs, &money);
			//ici: actions à effectuer tous les 3 tours de boucle
		}
		if(KeyDown(K_SHIFT))
		{
			if(pause)pause = 0;
			else pause = 1;
			while(KeyDown(K_SHIFT)){}
		}
		
		texts = checkTextDelay(texts);
		
		//graphics
		showGrid(lev->grid, &cam);
		showTowers(cam, lev->towers);
		showAllMobs(mobs, cam, counter, pause);
		showCursor(&c, lev->grid, &cam, lev->towers);
		/**/showTexts(texts, cam);
		ML_rectangle(128 - 14, -1, 128, 9, 1, BLACK, WHITE);
		if(!(counter % 5) && !pause)towers_action(lev->towers, mobs, &cam);
		//tower_action
		if(pause)
		{
			PrintMini(128-11, 1, " ||", MINI_OVER);
		}
		else
		{
			if(sleep == 7){
				if(KeyDown(K_MINUS))sleep = 15;
				PrintMini(128-11, 1, "x2", MINI_OVER);
				}
			if(sleep == 15){
				if(KeyDown(K_PLUS))sleep = 7;
					PrintMini(128-11, 1, "x1", MINI_OVER);
				}
		}
		intToStr(fps_text, fps);
		PrintMini(0, 0, fps_text, MINI_OVER);
		counter++;
		ML_display_vram();
		ML_clear_vram();
		Sleep(sleep + 5 * (counter % 5 != 0));
		n++;
	}
    return 0;
}

int AddIn_main(int isAppli, unsigned short OptionNum)
{
	int counter = 0;
	while(1)
	{
		if(counter == 5)
		{
			counter = 0;
			tick();
		}
		counter++;
	}
}





#pragma section _BR_Size
unsigned long BR_Size;
#pragma section
#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

