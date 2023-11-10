#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "huntinghouse.h"


BaseObject::BaseObject()
{
	x = 0;
	y = 0;
	state = 1;
}
BaseObject::BaseObject(int init_x, int init_y, int init_state)
{
	x = init_x;
	y = init_y;
	state = init_state;
}
BaseObject::~BaseObject()
{
}
