#include <graphics.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>

#include "box_man.h"

using namespace std;

IMAGE images[ALL];

struct _POS man;

POS temp[4];

//游戏地图
int map[LINE][COLUMN] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 4, 1, 0, 2, 1, 0, 2, 1, 0, 0},
	{0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
	{0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0},
	{0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0},
	{0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

//判断游戏是否结束
bool isGameover(){
	for(int i = 0; i<LINE; i++){
		for(int j = 0; j < COLUMN; j++){
			if(map[i][j] == BOX_DES) return false;
		}
	}
	return true;
}

bool isBOXDES(POS pos){
	for(int i = 0; i<4; i++){
		if(man.x == temp[i].x && man.y == temp[i].y){
			return true;
		}
	}
	return false;
}

int steps = 0;
int count = 0;

void gameOver(IMAGE* bg){
	putimage(0, 0, bg);
	settextcolor(WHITE);
	RECT rec = {0, 0, SECREEN_WIDTH, SECREEN_HEIGHT};  //定义一个矩形/矩形结构体
	settextstyle(20, 0, "宋体");
	drawtext("游戏结束", &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//水平/垂直居中/设置为同一行
}

void changeMap(POS* pos, PROPS prop){
	map[pos->x][pos->y] = prop;
	putimage(START_X + pos->y * RATIO, START_Y + pos->x * RATIO, &images[prop]);
}

void gameControl(DIRECTION direct){

	POS next_pos = man;
	POS next_next_pos = man;

	switch(direct){
		case UP:
			next_pos.x--;
			next_next_pos.x -= 2;
			break;
		case DOWN:
			next_pos.x++;
			next_next_pos.x +=2;
			break;
		case LEFT:
			next_pos.y--;
			next_next_pos.y -= 2;
			break;
		case RIGHT:
			next_pos.y++;
			next_next_pos.y += 2;
			break;
	}

	if(isValid(next_pos) && map[next_pos.x][next_pos.y] == FLOOR){
		changeMap(&next_pos, MAN);
		if(isBOXDES(man)){
			changeMap(&man, BOX_DES);
		}
		else changeMap(&man, FLOOR);
		man = next_pos;
		
	}

	else if(isValid(next_pos) && map[next_pos.x][next_pos.y] == BOX_DES){
		changeMap(&next_pos, MAN);
		changeMap(&man, FLOOR);
		man = next_pos;
	}

	else if(isValid(next_next_pos) && map[next_pos.x][next_pos.y] == BOX){
		if(map[next_next_pos.x][next_next_pos.y] == FLOOR){ //箱子前面是地板
			changeMap(&next_next_pos, BOX);
			changeMap(&next_pos, MAN);
			if(isBOXDES(man)){
			changeMap(&man, BOX_DES);
			}
			else changeMap(&man, FLOOR);
			man = next_pos;
		}
		else if(map[next_next_pos.x][next_next_pos.y] == BOX_DES){  //箱子前面是目的地
			changeMap(&next_next_pos, BOX);
			changeMap(&next_pos, MAN);
			changeMap(&man, FLOOR);
			man = next_pos;
		}
	}
}

int main(void){
	IMAGE bg_img;
	initgraph(SECREEN_WIDTH, SECREEN_HEIGHT);
	loadimage(&bg_img, _T("blackground.bmp"), SECREEN_WIDTH, SECREEN_HEIGHT,true);
	putimage(0, 0, &bg_img);

	loadimage(&images[WALL], _T("wall_right.bmp"), RATIO, RATIO, true);
	loadimage(&images[FLOOR], _T("floor.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX_DES], _T("des.bmp"), RATIO, RATIO, true);
	loadimage(&images[MAN], _T("man.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX], _T("box.bmp"), RATIO, RATIO, true);
	loadimage(&images[HIT], _T("box.bmp"), RATIO, RATIO, true);
	for(int i = 0; i < LINE; i++){
		for(int j = 0; j<COLUMN; j++){
			if(map[i][j] == MAN){
				man.x = i;
				man.y = j;
			}

			else if(map[i][j] == BOX_DES){
				temp[count].x = i;
				temp[count].y = j;
				count++;
			}

			putimage(START_X + j * RATIO, START_Y + i * RATIO, &images[map[i][j]]);
		}
	}

	//游戏环节
	bool quit = false;

	do{
		if(_kbhit()){  //是否敲击键盘
			char ch = _getch();
			
			if(ch == KEY_UP){
				gameControl(UP);
			}
			else if(ch == KEY_LEFT){
				gameControl(LEFT);
			}
			else if(ch == KEY_RIGHT){
				gameControl(RIGHT);
			}
			else if(ch == KEY_DOWN){
				gameControl(DOWN);
			}
			else if(ch == KEY_QUIT){
				quit = true;
			}
			steps++;
			
			if(isGameover()){
				gameOver(&bg_img);
				quit = true;
			}

			else if(steps >= MAX_STEPS){
				putimage(0, 0, &bg_img);
				settextcolor(WHITE);
				RECT rec = {0, 0, SECREEN_WIDTH, SECREEN_HEIGHT};  
				settextstyle(20, 0, "宋体");
				drawtext("步数过多，游戏结束", &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				quit = true;
			}
		}
		Sleep(100);
	}while(quit == false);

	system("pause");

	//游戏结束，释放资源
	closegraph();

	return 0;
}