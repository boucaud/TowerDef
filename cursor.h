#ifndef CURSOR_H
#define CURSOR_H
#include "structures.h"
#include "fxlib.h"
#include "MonochromeLib.h"
#include "ECode.h"
#include "assert.h"
#include "syscall.h"
#include "stdlib.h"
#include "tower.h"

void showCursor(cursor *c, char *grid, camera *cam, tower *tow);
int moveCursor(cursor* c, camera *cam, char *grid, tower **towers, mob *mobs, int *money);
 
 #endif
