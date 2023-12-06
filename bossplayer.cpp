#define GL_SILENCE_DEPRECATION

#include "bossplayer.h"

#include <stdlib.h>
#include <time.h>

#include <sstream>

#include "fssimplewindow.h"
#include "ysglfontdata.h"

BossPlayer::BossPlayer() {
}

void BossPlayer::Init(int init_x, int init_width, int init_height, int init_windowHeight) {
    x = init_x;
    windowHeight = init_windowHeight;
    floorHeight = windowHeight / 5;
    floor = 5;
    yFloor = 600 - floorHeight * (floor - 1);
    point = 100;
    direction = 0;

    width = init_width;
    height = init_height;
    y = yFloor - height / 2;
    state = 0;
}

BossPlayer::~BossPlayer() {
}

void BossPlayer::Rendar(void) {
    if (state == 0) {
        // set obstacle color
        glColor3ub(255, 215, 0);

        // rendar obstacle
        glBegin(GL_QUADS);
        glVertex2i(x - width / 2, y - height / 3);
        glVertex2i(x - width / 2, y + height / 3);
        glVertex2i(x + width / 2, y + height / 3);
        glVertex2i(x + width / 2, y - height / 3);
        glEnd();

        glColor3ub(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex2i(x - width / 2 + 10, y - height / 3 + 10);
        glVertex2i(x - width / 2 + 10, y - height / 3 + 30);
        glVertex2i(x - width / 2 + 30, y - height / 3 + 30);
        glVertex2i(x - width / 2 + 30, y - height / 3 + 10);
        glEnd();

        glColor3ub(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex2i(x + width / 2 - 10, y - height / 3 + 10);
        glVertex2i(x + width / 2 - 10, y - height / 3 + 30);
        glVertex2i(x + width / 2 - 30, y - height / 3 + 30);
        glVertex2i(x + width / 2 - 30, y - height / 3 + 10);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2i(x - width / 2 + 10, y - height / 3 + 40);
        glVertex2i(x + width / 2 - 10, y - height / 3 + 40);
        glVertex2i(x + width / 2 - 10, y - height / 3 + 60);
        glVertex2i(x - width / 2 + 10, y - height / 3 + 60);
        glEnd();

        glColor3ub(255, 0, 0);
        glBegin(GL_QUADS);
        glVertex2i(x - width / 2 - 30, y + height / 3);
        glVertex2i(x - width / 2 + 30, y + height / 3);
        glVertex2i(x - width / 2 + 30, y + height / 3 + 10);
        glVertex2i(x - width / 2 - 30, y + height / 3 + 10);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2i(x + width / 2 - 30, y + height / 3);
        glVertex2i(x + width / 2 + 30, y + height / 3);
        glVertex2i(x + width / 2 + 30, y + height / 3 + 10);
        glVertex2i(x + width / 2 - 30, y + height / 3 + 10);
        glEnd();

        RendarPoint(250, 30);
        if (missile.state == 0) {
            missile.Shoot(x - width / 2, y - height / 3 + 40, true);
        }
        if (missile.state == 1) {
            missile.Move();
            missile.Draw();
        }
    }
}

void BossPlayer::RendarPoint(int x, int y) {
    glRasterPos2i(x, y);
    YsGlDrawFontBitmap12x16("Boss HP:");
    std::stringstream ss;
    ss << point;
    std::string str = ss.str();
    const char* c = str.c_str();
    YsGlDrawFontBitmap12x16(c);
}

void BossPlayer::HitFrom(BeamMissile& incoming) {
    if (state == 0 && incoming.state == 1 && incoming.x >= x && incoming.y >= y - height / 3 && incoming.y <= y + height / 3) {
        point -= 10;
        incoming.Disappear();
    }
    if (point == 0) {
        state = 1;
    }
}
