#ifndef FLOOR_H_IS_INCLUDED
#define FLOOR_H_IS_INCLUDED

#include "baseobject.h"

class Floor : public BaseObject {
   public:
    int windowHeight;
    int thickness;
    int floor;

    Floor();
    void Init(int init_y, int init_windowHeight, int init_floorThickness, int floor);
    ~Floor();

    void Rendar(void);
};

#endif
#pragma once
