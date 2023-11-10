#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "huntinghouse.h"
#include "maze.h"
#include "ladder.h"

HuntingHouse::HuntingHouse()
{
	state = 1;
}
HuntingHouse::HuntingHouse(int init_state)
{
	state = init_state;
}
HuntingHouse::~HuntingHouse()
{
}
int HuntingHouse::RunOneStep(void)
{
	FsPollDevice();
	auto key = FsInkey();
	if (FSKEY_ESC == key)
	{
		return 1;
	}


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m.Rendar();
	l.Rendar();
	FsSwapBuffers();

	return 0;
}