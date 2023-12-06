#define GL_SILENCE_DEPRECATION

#include "floor.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <sstream>

#include "baseobject.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

Floor::Floor() {
}

Floor::~Floor() {
}

void Floor::Init(int init_y, int init_windowHeight, int init_floorThickness, int init_floor) {
    windowHeight = init_windowHeight;
    thickness = init_floorThickness;
    y = init_y;
    floor = init_floor;
}

void Floor::Rendar(void) {
    if (floor > 1) {
        // set floor color
        glColor3ub(222, 184, 135);

        // rendar floor
        glBegin(GL_QUADS);
        glVertex2i(0, y - thickness / 2);
        glVertex2i(0, y + thickness / 2);
        glVertex2i(800, y + thickness / 2);
        glVertex2i(800, y - thickness / 2);
        glEnd();
    }

    if (4 != floor) {
        // set font color
        glColor3ub(220, 20, 60);

        // rendar game level of the floor
        glRasterPos2i(700, y - 180);

        YsGlDrawFontBitmap10x14("Level:");
        std::stringstream ss1;
        ss1 << floor;
        std::string str1 = ss1.str();
        const char* c1 = str1.c_str();
        YsGlDrawFontBitmap10x14(c1);
    }
}
