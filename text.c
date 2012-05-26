#include "text.h"

text *createText(int x, int y, int reward, text *texts) //adds a mob to the linked list
{
	text *temp = texts;
	text *new = malloc(sizeof(text));
	char str[10] = {0};
	
	new->x = x;
	new->y = y;
	new->delay = 10;
	new->next = NULL;
	new->prev = NULL;
	
	intToStr(str, reward);
	
	new->str = malloc(sizeof(char) * 10);
	memcpy(new->str, str, sizeof(char)*10);
	
	
	if(temp == NULL)
	{
		new->prev = NULL;
		return new;
	}
	if(temp->next == NULL)
	{
		new->prev = texts;
		texts->next = new;
		return texts;
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
	return texts;
	
}

text *removeText(text *text, text *list)
{
	if(text == NULL)return;
	if(text->next != NULL)
	{
		if(text->prev != NULL){
			text->prev->next = text->next;
			text->next->prev = text->prev;
		}
		else{
			text->next->prev = NULL;
			list = text->next;
		}
	}
	else{
		if(text->prev != NULL)
			text->prev->next = NULL;
		else
			list = NULL;
	}
	free(text);
	return list;
}

text *checkTextDelay(text *texts)
{
	text *tmp = texts;
	text *tmp2 = NULL;
	
	if(tmp == NULL)
		return NULL;
	if(tmp->next == NULL)
	{
		if(tmp->delay <= 0)
			texts = removeText(tmp, texts);
		return texts;
	}
	do{
		if(tmp->delay <= 0){
			tmp2 = tmp->next;;
			texts = removeText(tmp, texts);
			tmp = tmp2;
		}
		else tmp = tmp->next;
	}while(tmp != NULL);
	return texts;
}

void showTexts(text *texts, camera cam)
{
	text *tmp = texts;
	if(tmp == NULL) return;
	if(tmp->next == NULL)
	{
		PrintMini(tmp->x - cam.x - 2, tmp->y - cam.y - 2, tmp->str, MINI_REV);
		tmp->delay--;
		if(tmp->delay < 8)
			tmp -> y --;
		return;
	}
	do{
		PrintMini(tmp->x - cam.x - 2, tmp->y - cam.y - 2, tmp->str, MINI_REV);
		tmp->delay--;
		if(tmp->delay < 8)
			tmp -> y --;
		tmp = tmp->next;
	}while(tmp != NULL);
	return;
}
