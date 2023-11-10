#ifndef HUNTINGHOUSE_H_IS_INCLUDED
#define HUNTINGHOUSE_H_IS_INCLUDED

#include "baseobject.h"
#include "maze.h"
#include "ladder.h"

class HuntingHouse
{

public:
	int state;
	Maze m;
	//Maze m2(0, 0, 0, 20, 30, 40, 50, 10);
	Ladder l;
	//Ladder l1(100, 3, 600);


	HuntingHouse();
	HuntingHouse(int init_state);
	~HuntingHouse();

	int RunOneStep(void); // This function runs the game
};

#endif
