#define GL_SILENCE_DEPRECATION

#include "obstacle.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

#include "baseobject.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"

Obstacle::Obstacle() {
}

void Obstacle::Init(int init_x, int init_y, int init_state, int init_width, int init_height) {
    x = init_x;
    y = init_y;
    state = init_state;
    width = init_width;
    height = init_height;
}

Obstacle::~Obstacle() {
}

void Obstacle::Rendar(void) {
    if (0 != state) {
        // set obstacle color
        glColor3f(1, 1, 1);

        // rendar obstacle
        glBegin(GL_QUADS);
        glVertex2i(x - width / 2, y - height / 2);
        glVertex2i(x - width / 2, y + height / 2);
        glVertex2i(x + width / 2, y + height / 2);
        glVertex2i(x + width / 2, y - height / 2);
        glEnd();
    }
}
