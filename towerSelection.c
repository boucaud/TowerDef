#include "towerSelection.h" 

 
unsigned char towerMenu[] = {0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x08, 0x04, 0x02, 0x00, 0x08, 0x04, 0x02, 0x00, 0x08, 0x04, 0x02, 0x00, 0x08, 0x04, 0x02, 0x00, 0x08, 0x04, 0x02, 0x00, 0x28, 0x04, 0x02, 0x80, 0x4F, 0xFF, 0xFE, 0x40, 0x28, 0x04, 0x02, 0x80, 0x08, 0x04, 0x02, 0x00, 0x08, 0x04, 0x02, 0x00, 0x08, 0x04, 0x02, 0x00, 0x08, 0x04, 0x02, 0x00, 0x08, 0x04, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00};
unsigned char tower1Icon[] = {0x00, 0x30, 0x5E, 0x6A, 0x32, 0x22, 0x3C, 0x00};
unsigned char tower2Icon[] = {0x00, 0x18, 0x18, 0x18, 0x24, 0x18, 0x00, 0x00};
unsigned char tower3Icon[] = {0x00, 0x00, 0x18, 0x34, 0x2C, 0x18, 0x00, 0x00};
unsigned char tower4Icon[] = {0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x42, 0x00};
unsigned char *towerIcons[4] = {tower1Icon, tower2Icon, tower3Icon, tower4Icon};

unsigned char icon_sell[] = {0x00, 0x3C, 0x7E, 0x78, 0x60, 0x7E, 0x3C, 0x00};
unsigned char icon_upgrade[] = {0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x00};
unsigned char icon_info[] = {0x00, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00};
unsigned char icon_destroy[] = {0x00, 0x66, 0x7E, 0x3C, 0x3C, 0x7E, 0x66, 0x00};


// towerIcon[0] =tower1Icon;
// towerIcon[1] =tower2Icon;
// towerIcon[2] =tower3Icon;
/*
ORGANISATION DU MENU
|--------------|
|[  0  ][  1  ]|
|[  2  ][  4  ]|
|--------------|


*/
void showCost(int cost)
{
	unsigned char str[10] = {0};
	int i = 0;
	
	intToStr(str, cost);
	for(i = 0; str[i] != 0; i++)
	{}
	str[i] = '$';
	
	ML_rectangle(2, 45, 7*(i+1), 55, 1, BLACK, WHITE);
	PrintMini(5, 48, str, MINI_OVER);
}
void showTextBar(textBar *t)
{
	if(t->show)
	{
		ML_rectangle(t->x, t->y, t->x + t->sizeX, t->y + t->sizeY, 1, BLACK, WHITE);
		PrintMini(t->x + 10, t->y +3, t->text, MINI_OVER);
	}
}
void showBackground(cursor *c, camera *cam, char *grid, tower *towers, int decX, int decY, mob *mobs)
{
	showGrid(grid, cam);
	showCursor(c, grid, cam, towers);
	showTowers(*cam, towers);
	showAllMobs(mobs, *cam, 0, 1);
	ML_rectangle((c->gridX +1+decX)*9 -cam->x - 2, (c->gridY+decY)*9 -cam->y - 2, (c->gridX+1+decX)*9 + 27 -cam->x + 2,(c->gridY+decY)*9 + 16 -cam->y + 2, 1, BLACK, WHITE);
	ML_bmp_or_cl(towerMenu, (c->gridX+1+decX)*9 - cam->x, (c->gridY+decY)*9 - cam->y, 27, 16);
}
void fillSelectIcons(selectionMenuIcon *icons, int scroll, int x, int y)
{
	int i = 0;
	//creer une fonction d'import des tourelles, ou alors un tableau en variable globale (plus pratique)
	icons[0].name = "Mortar";
	icons[0].realX = x + 0*8;
	icons[0].realY = y + 0*8;
	icons[0].bmp = towerIcons[0];
	icons[0].cost = 50;
	
	icons[1].name = "Lazer";
	icons[1].realX = x + 1*8 +1;
	icons[1].realY = y + 0*8;
	icons[1].bmp = towerIcons[1];
	icons[1].cost = 100;
	
	
	icons[2].name = "Mine";
	icons[2].realX = x + 0*8;
	icons[2].realY = y + 1*8 +1;
	icons[2].bmp = towerIcons[2];
	icons[2].cost = 25;
	
	
	icons[3].name = "Cannon";
	icons[3].realX = x + 1*8 +1;
	icons[3].realY = y + 1*8 +1;
	icons[3].bmp = towerIcons[3];
	icons[3].cost = 150;
	
	/*
	icons[4].name = "ralentisseur"
	icons[4].realX =
	icons[4].realY =*/
	
	/*icons[5].name = "DCA"
	icons[5].realX =
	icons[5].realY =
	
	icons[6].name = "lance flammes"
	icons[6].realX =
	icons[6].realY =*/
}
void fillEditIcons(selectionMenuIcon *icons, int scroll, int x, int y)
{
	icons[0].name = "sell";
	icons[0].realX = x + 0*8;
	icons[0].realY = y + 0*8;
	icons[0].bmp = icon_sell;
	
	icons[1].name = "upgrade";
	icons[1].realX = x + 1*8 +1;
	icons[1].realY = y + 0*8;
	icons[1].bmp = icon_upgrade;
	
	icons[2].name = "info.";
	icons[2].realX = x + 0*8;
	icons[2].realY = y + 1*8 +1;
	icons[2].bmp = icon_info;
	
	icons[3].name = "destroy (explodes)";
	icons[3].realX = x + 1*8 +1;
	icons[3].realY = y + 1*8 +1;
	icons[3].bmp = icon_destroy;
	
}

void showIcons(selectionMenuIcon *icons, int decX, int decY, int nb)
{
	int i = 0;
	for(i = 0; i < nb; i++)
	{
		ML_bmp_8_or_cl(icons[i].bmp, icons[i].realX + decX*9, icons[i].realY + decY*9);
	}
}
int moveLocalCursor(cursor *local, textBar *desc, selectionMenuIcon *icons, int isDescription)
{
	if(KeyDown(K_LEFT) && local->gridX > 0)local->gridX--;
	if(KeyDown(K_RIGHT) && local->gridX <1)local->gridX++;
	if(!isDescription)
	{
		if(KeyDown(K_UP) && local->gridY > 0)local->gridY--;
		if(KeyDown(K_DOWN) && local->gridY<1)local->gridY++;
	}
	if(KeyDown(K_LEFT)||KeyDown(K_RIGHT)||KeyDown(K_UP)||KeyDown(K_DOWN))
	{
		desc->text = icons[local->gridY * 2 + local->gridX].name;
		desc->show = 1;
	}
	if(KeyDown(K_EXE)) return local->gridY * 2 +local->gridX;
	else return -1;
}
void showLocalCursor(cursor *c, camera *cam, cursor local, int decX, int decY)
{
	ML_rectangle((c->gridX + decX + 1)*9 - cam->x + 5 + local.gridX * 8 - 1/**/, (c->gridY + decY )*9 - cam->y + local.gridY*8 -1/**/, (c->gridX + decX + 1)*9 - cam->x + 5 + local.gridX * 8 + 9/**/
		, (c->gridY + decY)*9 - cam->y + local.gridY*8 + 9/**/, 1, BLACK, WHITE);
		
}

int openTowerEditionMenu(cursor c, camera *cam, char *grid, tower *towers, mob *mobs, int *money)//fonction is commented in openTowerSelectionMenu
{
	selectionMenuIcon icons[4] = {0};
	int i = 0; //counter
	int selected = 0;
	int ret = -1;
	int decX = 0, decY = 0;
	textBar description = {2, 55, 124, 10, NULL, 0};
	cursor local;
	Sleep(5);
	while(KeyDown(K_EXE)){}
	local.gridX = 0;
	local.gridY = 0;
	
	for(i = 0; i < 4; i++)
	{
		icons[i].index = i;
	}
	while((c.gridY + decY +1)*9 - cam->y > 64 - 27) decY --;
	while((c.gridX + decX +1)*9 - cam->x > 128 - 27) decX--;
	fillEditIcons(icons, 0, (c.gridX +1)*9 - cam->x + 5, c.gridY*9 - cam->y);
	description.text = icons[local.gridY * 2 + local.gridX].name;
	description.show = 1;
	
	while(KeyUp(K_EXIT))
	{
		ret = moveLocalCursor(&local, &description, &icons, 0);
		if(ret != -1)
		{
			//grid[c.gridY*GRID_LENGTH + c.gridX] = 6;
			return icons[ret].index +1;
		}
		showBackground(&c, cam, grid, towers, decX, decY, mobs);
		showLocalCursor(&c, cam, local, decX, decY);
		showIcons(icons, decX, decY, 4);
		showTextBar(&description);
		
		showMoney(*money);
		ML_display_vram();
		ML_clear_vram();
		Sleep(100);
	}
	return -1;
	
	
}
int openTowerSelectionMenu(cursor c, camera *cam, char *grid, tower *towers, mob *mobs, int *money) 
{
	selectionMenuIcon icons[4] = {0};
	int scroll = 0;
	int i = 0;
	int towerId = 0;
	int ret = -1;
	int decX = 0, decY = 0;
	
	textBar description = {2, 55, 124, 10, NULL, 0};
	textBar not_enough_money = {2, 0, 124, 10, "Not enough money", 0};
	
	cursor local;
	Sleep(5);
	
	while(KeyDown(K_EXE)){}//wainting for exe to be released
	//initialisations...
	local.gridX = 0;
	local.gridY = 0;
	
	for(i = 0; i < 4; i++)
	{
		icons[i].index = i;
	}
	//moving the cursor if it goes out of the screen or is hidden by the GUI
	while((c.gridY + decY +1)*9 - cam->y > 64 - 27) decY --;
	while((c.gridX + decX +1)*9 - cam->x > 128 - 27) decX--;
	//initialisating icons
	fillSelectIcons(icons, scroll, (c.gridX + 1)*9 - cam->x + 5, c.gridY*9 - cam->y);
	description.text = icons[local.gridY * 2 + local.gridX].name;
	description.show = 1;
	not_enough_money.show = 0;
	//main loop
	while(KeyUp(K_EXIT))
	{
		//ML_rectangle(0, 0, 128, 64, 0, 0, CHECKER);

		ret = moveLocalCursor(&local, &description, icons, 0);
		
		if(ret != -1 && *money >= icons[local.gridY * 2 + local.gridX].cost) //a tower has been chosen, and the player has enough money to buy it
		{
			grid[c.gridY*GRID_LENGTH + c.gridX] = 6; //modifying the grid
			*money -= icons[local.gridY * 2 + local.gridX].cost; //substracting the money
			return icons[ret].index +1; //returning the chosen id
		}
		else if(ret != -1)
			ret = -1;
		//checks if the player has enough money
		if(*money < icons[local.gridY * 2 + local.gridX].cost)
			not_enough_money.show = 1;
		else not_enough_money.show = 0;
		
		//graphics
		showBackground(&c, cam, grid, towers, decX, decY, mobs);
		showLocalCursor(&c, cam, local, decX, decY);
		showIcons(icons, decX, decY, 4);
		
		showTextBar(&description);
		showTextBar(&not_enough_money);
		
		showCost(icons[local.gridY * 2 + local.gridX].cost);
		showMoney(*money);
		ML_display_vram();
		ML_clear_vram();
		
		Sleep(100);
	}
	return -1; //if EXIT has been pressed
}

