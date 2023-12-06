#ifndef OBSTACLE_H_IS_INCLUDED
#define OBSTACLE_H_IS_INCLUDED

// Include necessary libraries
#include <iostream>

#include "yspng.h"

class Obstacle {
   public:
    int x, y, state;
    int width, height;
    Obstacle();
    ~Obstacle();
    void Init(int init_x, int init_y, int init_state, int init_width, int init_height);
    void Rendar();
};

#endif
