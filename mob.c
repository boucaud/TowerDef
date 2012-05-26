#include "mob.h"
/*FONCTIONNE EN PARTANT DU PRINCIPE QUE LES MOBS PARTENT VERS LA DROITE !!!*/
unsigned char mob1_r[] = {0x00, 0x10, 0x28, 0x64, 0x24, 0x28, 0x16, 0x00};
unsigned char mob2_r[] = {0x00, 0x16, 0x28, 0x24, 0x64, 0x28, 0x10, 0x00};


unsigned char mob1_l[] = {0x00, 0x08, 0x14, 0x26, 0x24, 0x14, 0x68, 0x00};
unsigned char mob2_l[] = {0x00, 0x68, 0x14, 0x24, 0x26, 0x14, 0x08, 0x00};


unsigned char mob1_u[] = {0x00, 0x40, 0x58, 0x24, 0x42, 0x3C, 0x08, 0x00};
unsigned char mob2_u[] = {0x00, 0x02, 0x1A, 0x24, 0x42, 0x3C, 0x10, 0x00};


unsigned char mob1_d[] = {0x00, 0x08, 0x3C, 0x42, 0x24, 0x58, 0x40, 0x00};
unsigned char mob2_d[] = {0x00, 0x10, 0x3C, 0x42, 0x24, 0x1A, 0x02, 0x00};


unsigned char *mob_r_bmp[] = {mob1_r, mob2_r};
unsigned char *mob_l_bmp[] = {mob1_l, mob2_l};
unsigned char *mob_u_bmp[] = {mob1_u, mob2_u};
unsigned char *mob_d_bmp[] = {mob1_d, mob2_d};


int mob_comp(mob *target, mob *list) //returns 0 if target is not in the list, or else returns 1
{
	mob *tmp = list;	
	if(tmp == NULL)return;
	if(tmp->next == NULL){
		if(target == tmp)
			return 1;
		else	
			return 0;
	}
	do{
		if(target == tmp)
			return 1;
		tmp = tmp->next;
	}while(tmp != NULL);
	return 0;
}

void translateMobY(mob* m, int n) //internal fonction of movemob. the use is explicit
{
	if(m == NULL)return;
	
   m->realY += n;
   if(m->caseY + n < 0)
   {
      m->gridY--;
      m->caseY = 8;
   }
   else if(m-> caseY + n > 8)
   {
      m->caseY = 0;
      m->gridY++;
   }
   else m->caseY += n;
}
void translateMobX(mob* m, int n) //internal fonction of movemob. the use is explicit
{
	if(m == NULL)return;
	
   m->realX += n;
   if(m->caseX + n < 0)
   {
       m->gridX--;
       m->caseX = 8;
   }
   else if( m-> caseX + n > 8)
   {
       m->caseX = 0;
       m->gridX ++;
   }
   else m->caseX += n;
}

void showMob(mob m, camera cam) //display m in the VRAM
{
	// if(m.realX < 0 || m.realY < 0)return;
	ML_rectangle(m.realX - cam.x - 2, m.realY - cam.y - 2, (m.realX) - cam.x + 2, (m.realY) - cam.y + 2, 0, WHITE, WHITE);

	if(m.dir == DOWN)
	{
		ML_bmp_8_or_cl(mob_d_bmp[m.n], m.realX - cam.x - 4, m.realY - cam.y - 4);
		ML_line(m.realX-cam.x - 5, m.realY - cam.y - 5, m.realX-cam.x + 5, m.realY - cam.y - 5, BLACK);
		ML_line(m.realX-cam.x - 5, m.realY - cam.y - 6, m.realX-cam.x + 5 - (m.fullLife - m.life) /12, m.realY - cam.y - 6, BLACK);
	}
	else if(m.dir == UP)
	{
		ML_bmp_8_or_cl(mob_u_bmp[m.n], m.realX - cam.x - 4, m.realY - cam.y - 4);
		ML_line(m.realX-cam.x - 5, m.realY - cam.y +5, m.realX-cam.x + 5, m.realY - cam.y + 5, BLACK);
		ML_line(m.realX-cam.x - 5, m.realY - cam.y + 6, m.realX-cam.x + 5 - (m.fullLife - m.life) /12, m.realY - cam.y + 6, BLACK);
	}
	else if(m.dir == LEFT)
	{
		ML_bmp_8_or_cl(mob_l_bmp[m.n], m.realX - cam.x - 4, m.realY - cam.y - 4);
		ML_line(m.realX-cam.x +5, m.realY - cam.y - 5, m.realX-cam.x +5, m.realY - cam.y + 5, BLACK);
		ML_line( m.realX - cam.x + 6, m.realY - cam.y - 5 + (m.fullLife - m.life) /12, m.realX-cam.x + 6, m.realY - cam.y + 5, BLACK);
	}
	else if(m.dir == RIGHT)
	{
		ML_bmp_8_or_cl(mob_r_bmp[m.n], m.realX - cam.x - 4, m.realY - cam.y - 4);
		ML_line(m.realX-cam.x -5, m.realY - cam.y - 5, m.realX-cam.x -5, m.realY - cam.y + 5, BLACK);
		ML_line( m.realX - cam.x - 6, m.realY - cam.y - 5 + (m.fullLife - m.life) /12, m.realX-cam.x-6, m.realY - cam.y + 5, BLACK);
	
	}
}
void showAllMobs(mob *m, camera cam, int counter, int freeze) //displays the linked list of mobs, and update the animation
{
	mob *temp = m;
	if(m==NULL)return;
	if(temp->next == NULL){
		if(!(counter % 15))
		{
			if(!freeze){
				temp->n ++;
				if(temp->n > 1)
					temp->n = 0;
			}
			//ici: actions à effectuer tous les 3 tours de boucle
		}
		showMob(*temp, cam);
		return;
	}
	do{
		if(!(counter % 15))
		{
			if(!freeze){
				temp->n ++;
				if(temp->n > 1)
					temp->n = 0;
			}
			//ici: actions à effectuer tous les 3 tours de boucle
		}
		showMob(*temp, cam);
		temp = temp->next;
	}while(temp != NULL);
}

mob *checkMobsLife(mob *mobs, tower *towers, int *money, text **texts) //checks wether a mobs is killed, and deletes it if the mob is dead
{
	char str[10] = {0};
	mob *tmp = mobs;
	mob *tmp2 = NULL;
	str[0] = '+';
	
	if(tmp == NULL)
		return NULL;
	if(tmp->next == NULL)
	{
		if(tmp->life <= 0){
			*money += tmp->reward;
			*texts = createText(tmp->realX, tmp->realY, tmp->reward, *texts);
			mobs = deleteMob(tmp, mobs, towers);}
		return mobs;
	}
	do{
		if(tmp->life <= 0){
			*money += tmp->reward;
			*texts = createText(tmp->realX, tmp->realY, tmp->reward, *texts);
			tmp2 = tmp->next;
			mobs = deleteMob(tmp, mobs, towers);
			tmp = tmp2;
			//unrolled because I was lazy
		/*	str[1] = 0;
			str[2] = 0;
			str[3] = 0;
			str[4] = 0;
			str[5] = 0;
			str[6] = 0;
			str[7] = 0;
			str[8] = 0;
			str[9] = 0;*/
		}
		else tmp = tmp->next;
	}while(tmp != NULL);
	return mobs;
}
mob *moveAllMobs(mob *m, char *grid, int counter, dot end, tower *towers) //move the linked list
{
	mob *temp = m;
	mob *tmp2 = NULL;
	if(temp==NULL)return NULL;
	if(temp->next == NULL){
		if(temp->counter == 10-temp->speed){
		temp->counter = 0;
			if(move(temp, grid, end) == 1)m = deleteMob(temp, m, towers);
		}else temp->counter++;
		return m;
	}
	do{
		if(temp->counter == 10-temp->speed){
			temp->counter = 0;
			if(move(temp, grid, end) == 1){
				tmp2 = temp->next;
				m = deleteMob(temp, m, towers);
				temp = tmp2;
			}
		}else temp->counter++;
		temp = temp->next;
	}while(temp != NULL);
	return m;
}

int move(mob* m, char* grid, dot end) //moves m. (called by moveallmobs)
{

	
    int i=0, j=0;
	if(m == NULL)return;
	
	if(m->realX < 0){
		translateMobX(m, 1);
		return 0;
	}
	if(m->realY < 0){
		translateMobY(m, 1);
		return 0;
	}
    if( (m->caseX == 4 && m->caseY == 4) &&
    grid[m->gridY * GRID_LENGTH + m->gridX] >1 &&
    grid[m->gridY * GRID_LENGTH + m->gridX]<6)
    //si changement de direction a faire
    {
        switch(grid[m->gridY * GRID_LENGTH    + m->gridX])
        {
        case 2:
            m->dir = LEFT;
            break;
        case 3:
            m->dir = RIGHT;
            break;
        case 4:
            m->dir = UP;
            break;
        case 5:
            m->dir = DOWN;
            break;
		}
	}
    //deplacements
    if(m->dir == LEFT)
        translateMobX(m, -1);
    if(m->dir == RIGHT)
        translateMobX(m, 1);
    if(m->dir == UP)
        translateMobY(m, -1);
    if(m->dir == DOWN)
        translateMobY(m, 1);
	// if(m->dir == LEFT)
        // translateMobX(m, -m->speed);
    // if(m->dir == RIGHT)
        // translateMobX(m, m->speed);
    // if(m->dir == UP)
        // translateMobY(m, -m->speed);
    // if(m->dir == DOWN)
        // translateMobY(m, m->speed);
	//voir si le mob est à l'arrivée:
	if(m->gridX == end.x && m->gridY == end.y)
		return 1;
	return 0;
}
mob *createMob(int realX, int realY, int speed, int life, mob *mobs) //adds a mob to the linked list
{
	mob *temp = mobs;
	mob *new = malloc(sizeof(mob));
	new->speed = speed;
	new->life = life;
	new->fullLife = life;
	new->counter = 0;
	new->realX = realX;
	new->realY = realY+4;
	new->gridX = (realX)/9;
	new->gridY = (realY)/9;
	new->caseX = realX%9;
	new->caseY = realY%9+4;
	new->n = 0;
	new->reward = 15;
	new->next = NULL;
	new->prev = NULL;
	new->dir = RIGHT;
	if(temp == NULL)
	{
		new->prev = NULL;
		return new;
	}
	if(temp->next == NULL)
	{
		new->prev = mobs;
	}
	else
	{
		do{
			temp = temp->next;
		}while(temp->next != NULL);
	}
	if(temp->next == NULL)//mieux vaut plus de vérifications que pas du tout ^^...
	{
		new->prev = temp;
	}
	temp->next = new;
	return mobs;
	
}

mob *addWave(int startX, int startY, int nb, int speed, int life, mob *mobs) //adds a wave of mobs to the linked list (calls createMob)
{
	int i = 0;
	for(i = 0; i < nb; i++)
	{
		mobs = createMob(startX*9 - (9*i), startY /*- (15*i)*9*/, speed, life, mobs);
	}
	return mobs;
}

mob *deleteMob(mob *m, mob *mobs, tower *towers) //frees m and deletes it from the linked list
{
	if(m == NULL)return;
	if(m->next != NULL)
	{
		if(m->prev != NULL){
			m->prev->next = m->next;
			m->next->prev = m->prev;
		}
		else{
			m->next->prev = NULL;
			mobs = m->next;
		}
	}
	else{
		if(m->prev != NULL)
			m->prev->next = NULL;
		else
			mobs = NULL;
	}
	freeTargets(towers, m, mobs);
	free(m);
	return mobs;
}
