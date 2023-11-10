#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "huntinghouse.h"
#include "maze.h"

int main(void)
{
	FsOpenWindow(0, 0, 800, 600, 1);

	//GameMenu menu;
	HuntingHouse game(1);
	int state = 0;

	while (2 != state)
	{
		game.RunOneStep();
	}
	//game.RunOneStep();

	/*-----__Code lines below are for game manu__-----*/
	/*
	int state = 0; // 0:Menu  1:Game  2:Quit
	int c = 0;
	while (2 != state)
	{
		if (0 == state)
		{
			auto sel = menu.RunOneStep();
			if (GameMenu::SEL_RUN_GAME == sel)
			{
				game.Initialize();
				state = 1;
			}
			else if (GameMenu::SEL_QUIT == sel)
			{
				state = 2;
			}
		}
		else if (1 == state)
		{
			auto res = game.RunOneStep();
			if (0 != res)
			{
				state = 0;
			}
		}
	}
	*/
	/*-----__Code lines below are for game manu__-----*/
	return 0;
}