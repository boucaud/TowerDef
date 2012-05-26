#ifndef STRUCT_H
#define STRUCT_H
/*
#define GRID_WIDTH 5
#define GRID_LENGTH 5
*/
//#define abs(x) x>0?x:-x;
#define GRID_WIDTH 24
#define GRID_LENGTH 24
#define NB_TOWERS 6	
#define v_abs(a) a<0?-a:a

typedef enum {LEFT, RIGHT, UP, DOWN}direction;
typedef struct level level;
typedef struct camera camera;
typedef struct dot dot;
typedef struct mob mob;
typedef struct towerLabel towerLabel;
typedef struct tower tower;
typedef struct cursor cursor;
typedef struct selectionMenuIcon selectionMenuIcon;
typedef struct textBar textBar;
typedef struct shot shot;//tirs d'une tourelle
typedef struct text text;

struct level{
mob *mobs;
tower *towers;
char *grid;
int width;
int length;
int difficulty; //à chaque degré de difficulté, les mobs montent en vitesse et en puissance plus vite
int wave; //compteur de vagues
};
struct camera{
int x;
int y;
};

struct dot{
int x;
int y;
};

struct mob{ //un peu lourd mais ca facilite les calculs apres
int realX;
int realY;
int gridX;
int gridY;
int caseX;
int caseY;
int life;
int fullLife;
int speed;
int n;//pour l'animation (pas la peine d'utiliser libAnim: il n'ya qu'une animation)
int counter;//pour la vitesse
int reward; //when the mob dies, the player earns the reward (int $)
direction dir;
mob *prev;
mob *next;
};

struct towerLabel{
	int x;
	int y;
	int id;
	char* name;
};

struct cursor{
int gridX;
int gridY;
};

struct selectionMenuIcon{
int index;
int realX;
int realY;
char *bmp;
char *name;
int cost;
char isHovered;
};

struct textBar{
int x;
int y;
int sizeX;
int sizeY;
char *text;
char show;
};

struct shot{
int x1;
int y1;
int x2;
int y2;
float dirX;
float dirY;
int speed;
int damage;
tower *parent;
shot *nxt;
};
struct tower{
int gridX;
int gridY;
char *name;
char *bmp;
int id;
int level;
int damage;
int fireRate;
float shotSpeed;
int orientation; //useless for the moment
int tick;
int range;
mob *target; //appel à une fonction assez complexe: affiche un bitmap du tir de la tourelle, et affiche un bitmap du mob qui se fait toucher
tower *prev;
tower *next;
};

struct text{
	int x;
	int y;
	char *str;
	int delay;
	text *prev;
	text *next;
};
#endif
