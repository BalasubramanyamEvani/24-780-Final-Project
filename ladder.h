#ifndef LADDER_H_IS_INCLUDED
#define LADDER_H_IS_INCLUDED

#include "baseobject.h"

class Ladder : public BaseObject {
   public:
    int x, floor, width, height, windowHeight;
    int floorHeight;
    int yTop, yBottom;

    Ladder();
    void Init(int init_x, int init_floor, int init_width, int init_windowHeight);
    ~Ladder();

    void Rendar(void);
};

#endif
