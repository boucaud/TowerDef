#ifndef TEXT_H
#define TEXT_H

#include <fxlib.h>
#include <stdlib.h>
#include "structures.h"
#include "ECode.h"
#include "assert.h"

text *createText(int x, int y, int reward, text *texts); //adds a mob to the linked list
text *removeText(text *text, text *list);
text *checkTextDelay(text *texts);
void showTexts(text *texts, camera cam);


#endif
