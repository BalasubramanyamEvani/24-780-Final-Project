#define GL_SILENCE_DEPRECATION

#include "ladder.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

#include "baseobject.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

Ladder::Ladder() {
}

Ladder::~Ladder() {
}

void Ladder::Init(int init_x, int init_floor, int init_width, int init_windowHeight) {
    x = init_x;
    width = init_width;
    windowHeight = init_windowHeight;
    floor = init_floor;

    floorHeight = windowHeight / 5;
    yTop = windowHeight - floorHeight * (floor + 1);
    yBottom = windowHeight - floorHeight * floor;
}

void Ladder::Rendar(void) {
    glDisable(GL_LINE_STIPPLE);
    glLineWidth(8);

    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);  // Set color to black
    glVertex2i(x - width / 2, yBottom);
    glVertex2i(x - width / 2, yTop);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);  // Set color to black
    glVertex2i(x + width / 2, yBottom);
    glVertex2i(x + width / 2, yTop);
    glEnd();

    for (int i = 1; i < 6; i++) {
        glBegin(GL_LINES);
        glColor3ub(255, 0, 0);  // Set color to black
        glVertex2i(x - width / 2, yTop + i * 20);
        glVertex2i(x + width / 2, yTop + i * 20);
        glEnd();
    }
}
