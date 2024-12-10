#pragma once

#define RATIO 61
#define SECREEN_WIDTH 960
#define SECREEN_HEIGHT 768

#define KEY_UP      'w'
#define KEY_LEFT    'a'
#define KEY_RIGHT   'd'
#define KEY_DOWN    's'
#define KEY_QUIT    'q'

#define LINE 9
#define COLUMN 12
#define MAX_STEPS 100

#define START_X 100
#define START_Y 150

typedef enum _PROPS     PROPS;
typedef enum _DIRECTION DIRECTION;
typedef struct _POS     POS;

#define isValid(pos) pos.x >= 0 && pos.x < LINE && pos.y >= 0 && pos.y < COLUMN

enum _PROPS{
	WALL,
	FLOOR,
	BOX_DES, //箱子目的地
	MAN,
	BOX,
	HIT,    //箱子命中目标
	ALL
};

enum _DIRECTION{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct _POS{
	int x;
	int y;
};