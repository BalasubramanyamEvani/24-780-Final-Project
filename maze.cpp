#define GL_SILENCE_DEPRECATION

#include "maze.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

#include "baseobject.h"
#include "floor.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

Maze::Maze() {
}

void Maze::Init(int init_x, int init_y, int init_state) {
    x = init_x;
    y = init_y;
    state = init_state;
}
Maze::~Maze() {
}
