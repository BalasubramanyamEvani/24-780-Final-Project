#ifndef AIR_BATTLE_GAME_H
#define AIR_BATTLE_GAME_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <list>

#include "fssimplewindow.h"
#include "yspng.h"
#include "yssimplesound.h"

void squareTextureMap(YsRawPngDecoder& png, double x, double y, double h, double w);
void DrawCircle(int cx, int cy, int rad, int fill);
void DrawRect(int x1, int y1, int x2, int y2, int fill);

class AirBattleGame {
   public:
    AirBattleGame();
    ~AirBattleGame();
    void Init();
    int run();
    /*
    Fighter fighter;
    Bullet bullet1;
    Bullet bullet2;
    */
};

class Fighter {
   public:
    double x;
    double y;
    double h;
    double w;
    int score;

    Fighter();
    ~Fighter();
    void Draw(void);
};

class Enermy {
   public:
    double x;
    double y;
    double dt;
    double sizeX;
    double sizeY;
    int state;
    int toRight;
    double v;

    Enermy();
    ~Enermy();
    int CheckHitByBullet(double bx, double by);
    void Move(void);
    void Initialize(int xi, int yi);
    void Draw(void);
};

class Bullet {
   public:
    double x;
    double y;
    double vy;
    double dt;
    int state;

    Bullet();
    ~Bullet();
    void Move(void);
    void Fire(void);
    void Draw(void);
};

#endif
