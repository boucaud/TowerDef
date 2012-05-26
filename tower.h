#ifndef TOWER_H
#define TOWER_H
#include "structures.h"
#include "stdlib.h"
#include "math.h"
#include "MonochromeLib.h"

void cleanTargets(tower *towers, mob *mobs);
int getNbTowerSlots(char *grid);
tower* addTower(int gridX, int gridY, int id, tower* towers);
void  towers_action(tower *towers, mob *m, camera *cam);
void showTowers(camera cam, tower *towers);
mob *shoot(tower *towers, mob *m, camera *cam);
tower *removeTower(tower *t, tower *towers);
tower *findTowerXY(int x, int y, tower *towers);
mob *search_ennemy(tower *t, mob *mobs);
void freeTargets(tower *towers, mob *target, mob *mobs);
#endif
