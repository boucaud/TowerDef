
#ifndef TOWER_SELECTION_H
#define TOWER_SELECTION_H

#include "structures.h"
#include "fxlib.h"
#include "MonochromeLib.h"
#include "ECode.h"
#include "assert.h"
#include "syscall.h"
#include "stdlib.h"
#include "structures.h"
#include "tower.h"

void showCost(int cost);
void showTextBar(textBar *t);
void showBackground(cursor *c, camera *cam, char *grid, tower *towers, int decX, int decY, mob *mobs);
void fillSelectIcons(selectionMenuIcon *icons, int scroll, int x, int y);
void fillEditIcons(selectionMenuIcon *icons, int scroll, int x, int y);
void showIcons(selectionMenuIcon *icons, int decX, int decY, int nb);
int moveLocalCursor(cursor *local, textBar *desc, selectionMenuIcon *icons, int isDescription);
void showLocalCursor(cursor *c, camera *cam, cursor local, int decX, int decY);
int openTowerSelectionMenu(cursor c, camera *cam, char *grid, tower *towers, mob *mobs, int *money);
int openTowerEditionMenu(cursor c, camera *cam, char *grid, tower *towers, mob *mobs, int *money);
#endif
