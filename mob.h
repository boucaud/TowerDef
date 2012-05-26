
#ifndef MOB_H
#define MOB_H

#include "fxlib.h"
#include "MonochromeLib.h"
#include "ECode.h"
#include "assert.h"
#include "syscall.h"
#include "stdlib.h"
#include "tower.h"
#include "structures.h"
#include "text.h"

int mob_comp(mob *target, mob *list);
void showMob(mob m, camera cam);
void showAllMobs(mob *m, camera cam, int counter, int freeze);
mob *moveAllMobs(mob *m, char *grid, int counter, dot end, tower *towers);
mob *checkMobsLife(mob *mobs, tower *towers, int *money, text **texts);
void translateMobY(mob* m, int n);
void translateMobX(mob* m, int n);
int move(mob* m, char* grid, dot end);
mob *addWave(int startX, int startY, int nb, int speed, int life, mob *mobs);
mob *createMob(int startX, int startY, int speed, int life, mob *mobs);
mob *deleteMob(mob *m, mob *mobs, tower *towers);
 #endif
