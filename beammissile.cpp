#define GL_SILENCE_DEPRECATION

#include "beammissile.h"

#include <iostream>

#include "fssimplewindow.h"

void BeamMissile::Shoot(int sx, int sy, bool reverse) {
    state = 1;
    x = sx;
    y = sy;
    if (reverse) {
        v = -4;
    } else {
        v = 4;
    }
}

void BeamMissile::Disappear(void) {
    state = 0;
}

void BeamMissile::Move() {
    if (0 != state) {
        x += v;
        if (x < 0 || x > 800) {
            Disappear();
        }
    }
}

void BeamMissile::Draw(void) {
    if (0 != state) {
        glColor3f(1, 0, 0);
        glPointSize(10);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }
}
