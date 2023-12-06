#define GL_SILENCE_DEPRECATION

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <sstream>

#include "floor.h"
#include "fssimplewindow.h"
#include "ladder.h"
#include "maze.h"
#include "obstacle.h"
#include "ysglfontdata.h"

int Absolute(int a, int b) {
    if (a < b) {
        return b - a;
    } else {
        return a - b;
    }
}

Player::Player() {
}

void Player::Init(int init_x, int init_floor, int init_state, int init_width, int init_height, int init_windowHeight, int init_climb) {
    x = init_x;

    windowHeight = init_windowHeight;
    floorHeight = windowHeight / 5;
    floor = init_floor;
    yFloor = 600 - floorHeight * (floor - 1);
    point = 1;
    direction = 0;
    width = init_width;
    height = init_height;
    y = yFloor - height / 2;
    state = init_state;  // 0: on a floor, 1: on a ladder
    climb = init_climb;  // 0: default_can not climb a ladder, 1: being able to climb a ladder
}

Player::~Player() {
}

void Player::Rendar(void) {
    RendarPoint(30, 30);
    if (missile.state == 1) {
        missile.Move();
        missile.Draw();
    }
}

void Player::RendarPoint(int x, int y) {
    glColor3ub(255, 0, 0);
    glRasterPos2i(x, y);
    YsGlDrawFontBitmap12x16("Player HP:");
    std::stringstream ss;
    ss << point;
    std::string str = ss.str();
    const char* c = str.c_str();
    YsGlDrawFontBitmap12x16(c);
}

void Player::Move(int key, Ladder l[], int bossState) {
    int horizontal_move = 0;
    for (int i = 0; i < 5; ++i) {
        if (1 == CurrentFloor[i]) {
            horizontal_move = 1;
        }
    }
    int vertical_move = 0;
    int current_ladder = 0;
    for (int i = 0; i < 4; ++i) {
        if (1 == CurrentLadder[i]) {
            vertical_move = 1;
            current_ladder = i;
        }
    }
    if (alive) {
        switch (key) {
            case FSKEY_RIGHT:
                if (800 >= x + width / 2 && 1 == horizontal_move) {
                    x += 10;  // Go right
                    direction = 1;
                }
                if (CurrentFloor[4] == 1 && bossState == 0 && x > 300) {
                    x = 300;
                }
                break;
            case FSKEY_LEFT:
                if (0 <= x - width / 2 && 1 == horizontal_move) {
                    x -= 10;  // Go left
                    direction = 0;
                }
                break;
            case FSKEY_UP:
                if (1 == vertical_move && y + height / 2 + 3 > l[current_ladder].yTop)  // p.climb = 1: the player can climb up a ladder
                {
                    y -= 10;  // Go up
                }
                break;
            case FSKEY_DOWN:
                if (1 == vertical_move && 600 >= y + height / 2 && y + height / 2 + 3 < l[current_ladder].yBottom)  // p.climb = 1: the player can climb up a ladder
                {
                    y += 10;  // Go down
                }
                break;
            case FSKEY_SPACE:
                if (missile.state == 0) {
                    missile.Shoot(x, y - 30, direction == 0);
                }
                break;
        }
    }
}

bool Player::ObstacleColisionCheck(Obstacle obstacle) {
    return (Absolute(x, obstacle.x) <= width / 2 + obstacle.width / 2 && Absolute(y, obstacle.y) <= height / 2 + obstacle.height / 2);
}

void Player::PositionCheck(Floor f[], Ladder l[]) {
    // Floor check
    for (int i = 0; i < 5; ++i) {
        if ((Absolute(y, f[i].y) <= (height / 2 + f[i].thickness / 2)) && (y + height / 2 <= f[i].y)) {
            CurrentFloor[i] = 1;
        } else {
            CurrentFloor[i] = 0;
        }
    }

    // ladder check
    for (int i = 0; i < 4; ++i) {
        if (l[i].yBottom >= y && y + height / 2 + 10 >= l[i].yTop && Absolute(x, l[i].x + l[i].width / 2) <= l[i].width && Absolute(x, l[i].x - l[i].width / 2) <= l[i].width) {
            CurrentLadder[i] = 1;
        } else {
            CurrentLadder[i] = 0;
        }
    }
}

void Player::CheckHitFrom(BeamMissile& incoming) {
    if (alive && incoming.state == 1 && incoming.x >= x - width / 2 && incoming.x <= x + width / 2 && incoming.y >= y - height / 2 && incoming.y <= y + height / 2) {
        point -= 10;
        incoming.Disappear();
        if (point <= 0) {
            point = 0;
            alive = false;
        }
    }
}
