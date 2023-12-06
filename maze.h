#ifndef MAZE_H_IS_INCLUDED
#define MAZE_H_IS_INCLUDED

#include "baseobject.h"

class Maze : public BaseObject {
   public:
    int x, y, state;
    Maze();
    ~Maze();
    void Init(int init_x, int init_y, int init_state);
};

#endif
