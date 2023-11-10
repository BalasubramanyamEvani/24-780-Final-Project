#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "baseobject.h"
#include "ladder.h"

Ladder::Ladder()
{
	x = 100;
    floor = 2;
    windowHeight = 600;
}

Ladder::Ladder(int init_x, int init_floor, int init_windowHeight)
{
    x = init_x;
	floor = init_floor;
    windowHeight = init_windowHeight;
}

Ladder::~Ladder()
{
}

void Ladder::Rendar(void)
{
	printf("%s%d\n", __FUNCTION__, __LINE__);

	// rendar 
    int yTop = (float(windowHeight) / 5.0) * float(6 - floor);
    int yBottom = (float(windowHeight) / 5.0) * float(5 - floor);

    if (floor > 0)
    {
        glBegin(GL_LINES);
        glColor3ub(0, 0, 0);  // Set color to black
        glVertex2i(x, yBottom);
        glVertex2i(x, yTop);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(0, 0, 0);  // Set color to black
        glVertex2i(x + 60, yBottom);
        glVertex2i(x + 60, yTop);
        glEnd();

        for (int i = 1; i < 6; i++) {
            glBegin(GL_LINES);
            glColor3ub(0, 0, 0);  // Set color to black
            glVertex2i(x, yBottom + i * 20);
            glVertex2i(x + 60, yBottom + i * 20);
            glEnd();
        }
    }

}