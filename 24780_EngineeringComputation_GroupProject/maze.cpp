#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "baseobject.h"
#include "maze.h"

Maze::Maze()
{
	x = 0;
	y = 0;
	state = 1;
	firstfloor = 600 / 5;
	secondfloor = 600 / 5 * 2;
	thirdfloor = 600 / 5 * 3;
	fourthfloor = 600 / 5 * 4;
	floorthickness = 10;
}

Maze::Maze(int init_x, int init_y, int init_state, int init_first, int init_second, int init_third, int init_fourth, int init_thick)
	: BaseObject(init_x, init_y, init_state)
{
	/*
	x = init_x;
	y = init_y;
	state = init_state;
	*/

	firstfloor = init_first;
	secondfloor = init_second;
	thirdfloor = init_third;
	fourthfloor = init_fourth;
	floorthickness = init_thick;
}
Maze::~Maze()
{
}

void Maze::Rendar(void)
{
	printf("%s%d\n", __FUNCTION__, __LINE__);

	// rendar 
	glColor3f(0, 0, 0);

	// rendar first floor
	glBegin(GL_QUADS);
	glVertex2i(0, 600 - firstfloor);
	glVertex2i(0, 600 - (firstfloor + floorthickness));
	glVertex2i(800, 600 - (firstfloor + floorthickness));
	glVertex2i(800, 600 - firstfloor);
	glEnd();

	// rendar second floor
	glBegin(GL_QUADS);
	glVertex2i(0, 600 - secondfloor);
	glVertex2i(0, 600 - (secondfloor + floorthickness));
	glVertex2i(800, 600 - (secondfloor + floorthickness));
	glVertex2i(800, 600 - secondfloor);
	glEnd();

	// rendar third floor
	glBegin(GL_QUADS);
	glVertex2i(0, 600 - thirdfloor);
	glVertex2i(0, 600 - (thirdfloor + floorthickness));
	glVertex2i(800, 600 - (thirdfloor + floorthickness));
	glVertex2i(800, 600 - thirdfloor);
	glEnd();

	// rendar third floor
	glBegin(GL_QUADS);
	glVertex2i(0, 600 - fourthfloor);
	glVertex2i(0, 600 - (fourthfloor + floorthickness));
	glVertex2i(800, 600 - (fourthfloor + floorthickness));
	glVertex2i(800, 600 - fourthfloor);
	glEnd();

}