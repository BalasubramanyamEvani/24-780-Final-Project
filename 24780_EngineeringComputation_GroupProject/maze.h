#ifndef MAZE_H_IS_INCLUDED
#define MAZE_H_IS_INCLUDED

#include "baseobject.h"

class Maze: public BaseObject
{
public:
	int firstfloor, secondfloor, thirdfloor, fourthfloor;
	int floorthickness;
	
	Maze();
	Maze(int x, int y, int init_state, int firstfloor, int secondfloor, int thirdfloor, int fourthfloor, int floorthickness);
	~Maze();

	void Rendar(void);
};

#endif

