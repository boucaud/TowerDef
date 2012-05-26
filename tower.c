#include "tower.h"

/*unsigned char tower2[] = {0x00, 0x30, 0x4E, 0x42, 0x22, 0x22, 0x3C, 0x00};

unsigned char tower3[] = {0x00, 0x3C, 0x24, 0x42, 0x42, 0x42, 0x3C, 0x00};

unsigned char tower1[] = {0x00, 0x58, 0x18, 0x66, 0x66, 0x18, 0x1A, 0x00};*/

unsigned char mortar_bmp[] = {0x00, 0x30, 0x5E, 0x6A, 0x32, 0x22, 0x3C, 0x00};
unsigned char lazer_bmp[] = {0x00, 0x18, 0x18, 0x18, 0x24, 0x18, 0x00, 0x00};
unsigned char mine_bmp[] = {0x00, 0x00, 0x18, 0x34, 0x2C, 0x18, 0x00, 0x00};
unsigned char cannon_bmp[] = {0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x42, 0x00};


//void ll_template()
//{
	//tower *tmp = towers;	
	//if(tmp == NULL)return;
	//if(tmp->next == NULL){
		//action();
		//return;
	//}
	//do{
		//action();
		//tmp = tmp->next;
	//}while(tmp != NULL);
	//return;
//}

int getNbTowerSlots(char *grid)//useless - returns the maximum number of towers
{
	int i = 0, nbTowers = 0;;
	for(i = 0; i < GRID_LENGTH * GRID_WIDTH; i++)
	{
		if(grid[i] == 0) nbTowers++;
	}
	return nbTowers;
}

tower* addTower(int gridX, int gridY, int id, tower* towers) //adds a tower to the linked list
{
	char mortar[] = {"Mortar"};
	char lazer[] = {"Lazer"};
	char mine[] = {"Mine"};
	char cannon[] = {"Cannon"};
	
	tower *new = malloc(sizeof(tower));
	tower *tmp = towers;
	tower *tmp_prev;
	
	new->tick = 0;
	new->gridX = gridX;
	new->gridY = gridY;
	new->range = 20;
	new->id = id;
	new->level = 1;
	new->next = NULL;
	new->prev = NULL;
	new->fireRate = 5; //5: tire tout le temps, 4: extremement vite, 3: vite, 2: moyen, 1: lent, 0: tres lent
	new->target = NULL;
	/********************************LOADING TOWERS CARACTERISTICS**********************************/
	if(new->id == 1)//mortar
	{
		new->name = malloc(sizeof(char)*7);
		memcpy(new->name, mortar, sizeof(char)*7);
		new->damage = 5;
		new->bmp = mortar_bmp;
	}
	if(new->id == 2)//lazer
	{
		new->name = malloc(sizeof(char)*6);
		memcpy(new->name, lazer, sizeof(char)*6);
		new->bmp = lazer_bmp;
		new->damage = 20;
	}
	if(new->id == 3)//mine
	{
		new->name = malloc(sizeof(char)*5);
		memcpy(new->name,  mine, sizeof(char)*5);	
		new->bmp = mine_bmp;
		new->damage = 30;
	}
	if(new->id == 4)//cannon
	{
		new->name = malloc(sizeof(char)*7);
		memcpy(new->name, cannon, sizeof(char)*7);
		new->bmp = cannon_bmp;
		new->damage = 60;
	}
	
	if(tmp == NULL)
	{
		new->prev = NULL;
		return new;
	}
	if(tmp->next == NULL)
	{
		new->prev = towers;
	}
	else
	{
		do{
			tmp = tmp->next;
		}while(tmp->next != NULL);
	}
	if(tmp->next == NULL)//mieux vaut plus de vérifications que pas du tout ^^...
	{
		new->prev = tmp;
	}
	tmp->next = new;
	return towers;
}

tower *removeTower(tower *t, tower *towers) //removes (and frees) one tower from the linked list
{
	tower *temp = NULL;
	if(t->prev == NULL && t->next == NULL)//if there is only 1 tower
	{
		free(t);
		return NULL;
	}
	if(t->prev == NULL)//if it is the first of the list
	{
		temp = t->next;
		temp->prev = NULL;
		free(t);
		return temp;
	}
	if(t->next == NULL)//if it is the last of the list
	{
		temp = t->prev;
		temp->next = NULL;
		free(t);
		return towers;	
	}
	//sinon
		temp = t->prev;
		temp->next = t->next;
		t->next->prev = temp;
		free(t);
		return towers;
}


void cleanTargets(tower *towers, mob *mobs) //makes sure that the towers won't shoot a mob that has already been set free - it avoids system errors
{
	tower *tmp = towers;	
	if(tmp == NULL)return;
	if(tmp->next == NULL){
		if(!mob_comp(tmp->target, mobs)) //if the target does no more exist in the linked list of mobs
		{
			tmp->target == NULL;
		}	
		return;
	}
	do{
		if(!mob_comp(tmp->target, mobs)) //same here
		{
			tmp->target == NULL;
		}	
		tmp = tmp->next;
	}while(tmp != NULL);
	return;
}

void freeTargets(tower *towers, mob *target, mob *mobs) //first verification: removes a mob from the targets. Is called when a mob dies.
{
	tower *tmp = towers;
	if(tmp == NULL)return;
	if(tmp->next == NULL){
		if(tmp->target == target)
		{
			tmp->target = NULL;
			tmp->target = search_ennemy(tmp, mobs);
		}
		return;
	}
	do{
		if(tmp->target == target)
		{
			tmp->target = NULL;
			tmp->target = search_ennemy(tmp, mobs);
		}
		tmp = tmp->next;
	}while(tmp != NULL);
	return;
}

void showTowers(camera cam, tower *towers) //draws the towers in the vram
{
	tower *tmp = towers;
	if(tmp == NULL)return;
	do{
		ML_bmp_8_or_cl(tmp->bmp, tmp->gridX*9 - cam.x, tmp->gridY*9 - cam.y);
		tmp = tmp->next;
	}while(tmp != NULL);
	return;
}

void towers_action(tower *towers, mob *m, camera *cam) //it is the action that will do a tower in every iteration of the main loo
{
	tower *tmp = towers;
	//cleanTargets(towers, m); //protect from buffer overflows
	//POUR DES RAISONS DE VITESSE, JE DOIS RECODER CETTE FONCTION

	if(tmp == NULL) //linked lists manipulation
	{
		return;
	}
	if(tmp->next == NULL)
	{	
		if(tmp->target == NULL)
		{
			tmp->target = search_ennemy(tmp, m);
		}
		if((!(tmp->tick % (7-tmp->fireRate))) && tmp->target != NULL){ //if the tower can shoot. buggy line, i will need to redo it.
			tmp->target = shoot(tmp, tmp->target, cam); //shooting the target
			
			
		}
		shoot(tmp, m, cam); //shooting the target
		tmp->tick++;
		
		return;
	}
	do{
		if(tmp->target == NULL)
		{
			tmp->target = search_ennemy(tmp, m);
		}
		if((!(tmp->tick % (7-tmp->fireRate))) && tmp->target != NULL){ //if the tower can shoot. buggy line, i will need to redo it.
			tmp->target = shoot(tmp, tmp->target, cam); //shooting the target
		}
		shoot(tmp, m, cam); //shooting the target
		tmp->tick++;
		tmp = tmp->next;
	}while(tmp != NULL);
}
mob *search_ennemy(tower *t, mob *mobs) //if the target is NULL, the tower will search the closest target possible.
{
	
	//POUR DES RAISONS DE VITESSE, JE DOIS RECODER CETTE FONCTION !
	mob *tmp = mobs;
	if(mobs == NULL)return NULL;
	if(tmp->next == NULL && v_abs((tmp->realX - t->gridX*9)*(tmp->realX - t->gridX*9) + (tmp->realY - t->gridY*9)*(tmp->realY - t->gridY*9)) < pow(t->range + 9, 2)|| (t->gridX*9 - tmp->realX)*(t->gridX*9 - tmp->realX) + (t->gridY*9 - tmp->realY)*(t->gridY*9 - tmp->realY) < pow(t->range + 9, 2))
		return tmp;
	if(tmp->next  == NULL)return NULL;
	do{
		if(v_abs( (tmp->realX - t->gridX*9)*(tmp->realX - t->gridX*9) + (tmp->realY - t->gridY*9)*(tmp->realY - t->gridY*9)) < (t->range + 9)*(t->range + 9)|| (t->gridX*9 - tmp->realX)*(t->gridX*9 - tmp->realX) + (t->gridY*9 - tmp->realY)*(t->gridY*9 - tmp->realY) < (t->range + 9)*(t->range + 9))
			return tmp;
		tmp = tmp->next;
	}while(tmp != NULL);
	return NULL;
}
mob *shoot(tower *towers, mob *m, camera *cam) //shoots m with towers
{
	if(m == NULL) return NULL;
	if(v_abs( (m->realX - towers->gridX*9)*(m->realX - towers->gridX*9) + (m->realY - towers->gridY*9)*(m->realY - towers->gridY*9)) < pow((towers->range + 9), 2)||  ((towers->gridX*9 - m->realX)*(towers->gridX*9 - m->realX) + (towers->gridY*9 - m->realY)*(towers->gridY*9 - m->realY) < pow(towers->range + 9, 2)))
	{
		ML_circle(m->realX - cam->x, m->realY - cam->y, 3, BLACK);
		ML_line(towers->gridX*9 + 4 - cam->x, (towers->gridY) * 9 + 4 - cam->y, m->realX - cam->x, m->realY - cam->y,BLACK);
		m->life -=towers->damage;
		return m;
	}
	return NULL;
}

tower *findTowerXY(int x, int y, tower *towers) //returns the tower that is located in (x, y), and NULL if there is no tower
{
	tower *tmp = towers;
	if(tmp == NULL)
	{
		return NULL;
	}
	if(tmp->next == NULL)
	{
		if(tmp->gridX == x && tmp->gridY == y)
			return tmp;
		else return NULL;
	}
	do{
		if(tmp->gridX == x && tmp->gridY == y)
			return tmp;
		tmp = tmp->next;
	}while(tmp != NULL);
}
