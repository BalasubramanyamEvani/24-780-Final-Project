#define GL_SILENCE_DEPRECATION

#include "air_battle.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "yssimplesound.h"

YsRawPngDecoder png[2];

const int nEnemy = 10;
const double PI = 3.1415927;

void squareTextureMap(YsRawPngDecoder& png, double x, double y, double h, double w) {
    GLuint textID;
    glGenTextures(1, &textID);
    glBindTexture(GL_TEXTURE_2D, textID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);
    glBindTexture(GL_TEXTURE_2D, textID);
    glBegin(GL_QUADS);
    glTexCoord2d(1.0, 1.0);
    glVertex2i(x, y);
    glTexCoord2d(0.0, 1.0);
    glVertex2i(x + w, y);
    glTexCoord2d(0.0, 0.0);
    glVertex2i(x + w, y + h);
    glTexCoord2d(1.0, 0.0);
    glVertex2i(x, y + h);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
}

AirBattleGame::AirBattleGame() {
}
AirBattleGame::~AirBattleGame() {
}
void AirBattleGame::Init() {
    /*
    Fighter fighter;
    Bullet bullet1;
    Bullet bullet2;

    fighter.x = 200.0;
    fighter.y = 520.0;
    fighter.h = 40.0;
    fighter.w = 60.0;
    fighter.score = 0;

    bullet1.state = 0;
    bullet1.vy = 0;
    bullet1.dt = 0.02;

    bullet2.state = 0;
    bullet2.vy = 0;
    bullet2.dt = 0.02;
    */
}

void DrawCircle(int cx, int cy, int rad, int fill) {
    const double YS_PI = 3.1415927;

    if (0 != fill) {
        glBegin(GL_POLYGON);
    } else {
        glBegin(GL_LINE_LOOP);
    }

    int i;
    for (i = 0; i < 64; i++) {
        double angle = (double)i * YS_PI / 32.0;
        double x = (double)cx + cos(angle) * (double)rad;
        double y = (double)cy + sin(angle) * (double)rad;
        glVertex2d(x, y);
    }

    glEnd();
}

void DrawRect(int x1, int y1, int x2, int y2, int fill) {
    if (0 != fill) {
        glBegin(GL_QUADS);
    } else {
        glBegin(GL_LINE_LOOP);
    }

    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);

    glEnd();
}

Fighter::Fighter() {
    x = 200.0;
    y = 520.0;
    h = 40.0;
    w = 60.0;
    score = 0;
}
Fighter::~Fighter() {
}
void Fighter::Draw(void) {
    squareTextureMap(png[0], x, y, h, w);
};

Enermy::Enermy() {
}
Enermy::~Enermy() {
}
int Enermy::CheckHitByBullet(double bx, double by) {
    int relativeX, relativeY;
    relativeX = bx - x;
    relativeY = by - y;
    if (0 <= relativeX && relativeX < sizeX && 0 <= relativeY && relativeY < sizeY) {
        state = 1;
        return 1;
    } else {
        return 0;
    }
};

void Enermy::Move() {
    if (toRight == 1) {
        x += v * dt;
        if (x > 760) {
            toRight = 0;
        }
    } else {
        x -= v * dt;
        if (x < 40) {
            toRight = 1;
        }
    }
};

void Enermy::Initialize(int xi, int yi) {
    x = xi;
    y = yi;
}

void Enermy::Draw(void) {
    squareTextureMap(png[1], x, y, sizeY, sizeX);
};

Bullet::Bullet() {
    state = 0;
    vy = 0;
    dt = 0.02;
}
Bullet::~Bullet() {
}
void Bullet::Move(void) {
    y -= vy * dt;
};

void Bullet::Fire(void) {
    state = 1;
    vy = 1000;
};
void Bullet::Draw(void) {
    glColor3ub(0, 0, 255);
    DrawRect(x, y, x + 5, y + 20, 1);
};

int AirBattleGame::run(void) {
    YsSoundPlayer player;

    auto start = FsSubSecondTimer();

    player.MakeCurrent();
    player.Start();
    FsChangeToProgramDir();
    YsSoundPlayer::SoundData test, laser, explode;
    if (YSOK != test.LoadWav("bg.wav")) {
        printf("Failed to read bg.wav\n");
        return 1;
    }
    if (YSOK != laser.LoadWav("bullet.wav")) {
        printf("Error!  Cannot load bullet.wav!\n");
    }
    if (YSOK != explode.LoadWav("hit_airbattle.wav")) {
        printf("Error!  Cannot load hit_airbattle.wav!\n");
    }
    player.SetVolume(test, 0.5);
    player.SetVolume(laser, 1.0);
    player.SetVolume(explode, 1.0);

    player.PlayBackground(test);

    // Initialize photos
    png[0].Decode("X-wing.png");
    png[1].Decode("Enemy.png");

    // initialize objects
    Fighter fighter;
    Bullet bullet1;
    Bullet bullet2;

    fighter.x = 200.0;
    fighter.y = 520.0;
    fighter.h = 40.0;
    fighter.w = 60.0;
    fighter.score = 0;

    bullet1.state = 0;
    bullet1.vy = 0;
    bullet1.dt = 0.02;

    bullet2.state = 0;
    bullet2.vy = 0;
    bullet2.dt = 0.02;

    std::list<Enermy> EnemyList;
    for (int i = 0; i < nEnemy; i++) {
        Enermy tempEnemy;
        tempEnemy.x = rand() % 760;
        tempEnemy.y = i * 30;
        tempEnemy.dt = 0.02;
        tempEnemy.sizeX = 50;
        tempEnemy.sizeY = 30;
        tempEnemy.state = 0;
        tempEnemy.toRight = 1;
        tempEnemy.v = rand() % 100;
        tempEnemy.Initialize(rand() % 760, i * 30);
        EnemyList.push_back(tempEnemy);
    }

    int toRight = 1;
    for (;;) {
        FsPollDevice();
        player.KeepPlaying();

        auto now = FsSubSecondTimer();
        double passedTime = double(now - start) / 1000.0;
        auto key = FsInkey();
        if (FSKEY_ESC == key || fighter.score >= nEnemy) {
            player.Stop(test);
            break;
        }

        if (FSKEY_RIGHT == key) {
            fighter.x += 5;
            if (fighter.x > 700) {
                toRight = 0;
            }
        } else if (FSKEY_LEFT == key) {
            fighter.x -= 5;
            if (fighter.x < 100) {
                toRight = 1;
            }
        }

        if (bullet1.state == 0 && bullet2.state == 0) {
            bullet1.state = 1;
            bullet1.x = fighter.x + 5;
            bullet1.y = fighter.y;
            bullet1.Fire();
            player.Stop(laser);
            player.PlayOneShot(laser);

            bullet2.state = 1;
            bullet2.x = fighter.x + fighter.w - 5;
            bullet2.y = fighter.y;
            bullet2.Fire();
        }

        if (bullet1.state == 1 && bullet2.state == 1) {
            bullet1.Move();
            bullet2.Move();
            if (bullet1.y < 0.0 || bullet2.y < 0) {
                bullet1.state = 0;
                bullet1.x = fighter.x;
                bullet1.y = fighter.y;

                bullet2.state = 0;
                bullet2.x = fighter.x;
                bullet2.y = fighter.y;
            }

            std::list<Enermy>::iterator p = EnemyList.begin();
            while (p != EnemyList.end()) {
                if (p->state == 0 && (p->CheckHitByBullet(bullet1.x, bullet1.y) == 1 ||
                                      p->CheckHitByBullet(bullet2.x, bullet2.y))) {
                    fighter.score++;
                    player.Stop(explode);
                    player.PlayOneShot(explode);
                    p->state = 1;
                    bullet1.state = 0;
                    bullet1.x = fighter.x;
                    bullet1.y = fighter.y;

                    bullet2.state = 0;
                    bullet2.x = fighter.x;
                    bullet2.y = fighter.y;
                }
                p->Move();
                p++;
            }
        }

        // draw everything out here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        fighter.Draw();
        if (bullet1.state == 1 && bullet2.state == 1) {
            bullet1.Draw();
            bullet2.Draw();
        }
        bool allHit = true;
        std::list<Enermy>::iterator p = EnemyList.begin();
        while (p != EnemyList.end()) {
            if (p->state == 0) {
                p->Draw();
            }
            allHit = allHit && p->state == 1;
            p++;
        }

        if (allHit) {
            break;
        } else if (passedTime > 25.0) {
            break;
        }

        // Rendar fighter score
        glColor3f(0, 0, 0);
        glRasterPos2i(20, 20);
        YsGlDrawFontBitmap6x7("Fighter Score:");
        std::stringstream ss;
        ss << fighter.score;
        std::string str = ss.str();
        const char* c = str.c_str();
        YsGlDrawFontBitmap12x16(c);

        FsSwapBuffers();
        FsSleep(25);
    }

    player.End();
    return (fighter.score);
}
