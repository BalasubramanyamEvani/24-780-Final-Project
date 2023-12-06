#define GL_SILENCE_DEPRECATION

#include "dinosaur.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"

void DinosaurGame::DrawHUD(int score, int nLifes) {
    // Implementation of PrintHUD
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    glColor4f(1.0f, 0, 1.0f, 0.8f);
    glVertex2d(50, 30);
    glColor4f(0.5f, 0, 0.5f, 0.8f);
    glVertex2d(280, 30);
    glColor4f(0, 0.5f, 1.0f, 0.8f);
    glVertex2d(280, 90);
    glColor4f(1.0f, 0.8, 0, 0.8f);
    glVertex2d(50, 90);
    glEnd();

    glColor3f(0, 0, 0);
    glRasterPos2d(60, 80);
    YsGlDrawFontBitmap12x16("Current score : ");
    glRasterPos2d(60, 60);
    YsGlDrawFontBitmap12x16("HP:");

    // Drawing the score
    glRasterPos2d(250, 80);
    YsGlDrawFontBitmap12x16(std::to_string(score).c_str());

    // Setting color based on nLifes
    float colorValue = nLifes / 100.0f;
    glColor3f(1 - colorValue, colorValue, 0);

    // Drawing the HP
    glRasterPos2d(100, 60);
    YsGlDrawFontBitmap12x16(std::to_string(nLifes).c_str());

    glFlush();
}

void DinosaurGame::DrawScene() {
    // sky
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    glColor4f(0.35f, 0.98f, 0.88f, 0.8f);
    glVertex2d(0, 0);
    glColor4f(0.35f, 0.98f, 0.88f, 0.8f);
    glVertex2d(800, 0);
    glColor4f(0.97, 0.96f, 0.96f, 0.8f);
    glVertex2d(800, 525);
    glColor4f(0.97, 0.96f, 0.96f, 0.8f);
    glVertex2d(0, 525);
    glEnd();

    // desert
    glColor4f(1, 0.81f, 0.21f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2d(0, 525);
    glVertex2d(800, 525);
    glVertex2d(800, 600);
    glVertex2d(0, 600);
    glEnd();

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00ff);
    glShadeModel(GL_SMOOTH);
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_LINES);
    glVertex2i(0, 525);
    glVertex2i(800, 525);
    glEnd();

    // sun
    glColor4f(0.96f, 0.8f, 0.16f, 0.8f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 64; ++i) {
        double angle = (double)i * Y_PI / 32;
        glVertex2d((600) + 20 * cos(angle), (100) + 20 * sin(angle));
    }
    glEnd();
}

void DinosaurGame::DrawEnd(int score) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(800, 0);
    glVertex2i(800, 600);
    glVertex2i(0, 600);
    glEnd();
    glColor3f(1, 0, 0);
    glRasterPos2d(300.0, 300.0);
    YsGlDrawFontBitmap16x20("You Dead !");
    glRasterPos2d(280.0, 330.0);
    YsGlDrawFontBitmap16x20("Your score is: ");
    glRasterPos2d(530.0, 330.0);
    YsGlDrawFontBitmap20x28(std::to_string(score).c_str());
    glRasterPos2d(230, 360);
    YsGlDrawFontBitmap16x20("Press Esc back to the house");
}
void DinosaurGame::DrawDinosaur(double x, double y, int nLifes) {
    // Setting color based on nLifes
    float colorValue = nLifes / 100.0f;
    glColor3f(1 - colorValue, colorValue - 0.2f, 0);
    // head
    glBegin(GL_QUADS);
    glVertex2i(x, 600 - y);
    glVertex2i(x + 20, 600 - y);
    glVertex2i(x + 20, 600 - (y + 10));
    glVertex2i(x, 600 - (y + 10));
    glEnd();
    // body
    glBegin(GL_QUADS);
    glVertex2i(x + 5, 600 - y);
    glVertex2i(x - 13, 600 - y);
    glVertex2i(x - 13, 600 - (y - 20));
    glVertex2i(x + 5, 600 - (y - 20));
    glEnd();
    // tail
    glBegin(GL_QUADS);
    glVertex2i(x - 13, 600 - (y - 20));
    glVertex2i(x - 13, 600 - (y - 18));
    glVertex2i(x - 25, 600 - (y - 18));
    glVertex2i(x - 25, 600 - (y - 20));
    glEnd();
    // leg
    glBegin(GL_QUADS);
    glVertex2i(x - 5, 600 - (y - 20));
    glVertex2i(x - 7, 600 - (y - 20));
    glVertex2i(x - 7, 600 - (y - 25));
    glVertex2i(x - 5, 600 - (y - 25));
    glEnd();
    glBegin(GL_QUADS);
    glVertex2i(x - 1, 600 - (y - 20));
    glVertex2i(x - 3, 600 - (y - 20));
    glVertex2i(x - 3, 600 - (y - 25));
    glVertex2i(x - 1, 600 - (y - 25));
    glEnd();
    // arm
    glBegin(GL_QUADS);
    glVertex2i(x + 5, 600 - (y - 5));
    glVertex2i(x + 10, 600 - (y - 5));
    glVertex2i(x + 10, 600 - (y - 7));
    glVertex2i(x + 5, 600 - (y - 7));
    glEnd();
    // eye
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 64; ++i) {
        double angle = (double)i * Y_PI / 32;
        glVertex2d((x + 5) + 2 * cos(angle), (600 - (y + 5)) + 2 * sin(angle));
    }
    glEnd();
    // mouse
    glBegin(GL_QUADS);
    glVertex2i(x + 10, 600 - (y + 2));
    glVertex2i(x + 20, 600 - (y + 2));
    glVertex2i(x + 20, 600 - (y + 4));
    glVertex2i(x + 10, 600 - (y + 4));
    glEnd();
}

void DinosaurGame::DrawObs(double x, double y, double w, double h, int obst_state) {
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    if (obst_state == 1) {
        glBegin(GL_QUADS);
        glVertex2i(x, 600 - y);
        glVertex2i(x + w, 600 - y);
        glVertex2i(x + w, 600 - (y + h));
        glVertex2i(x, 600 - (y + h));
        glEnd();
    }
}

bool DinosaurGame::CheckCollision(double x, double y, double tx, double ty, double tw, double th) {
    return (x >= tx && x <= tx + tw && y <= ty + th);
}

bool DinosaurGame::CheckPassing(double x, double y, double tx, double ty, double tw, double th) {
    return (x >= tx && x <= tx + 6 && y >= ty + th + 5);
}

void DinosaurGame::generateObs(double (&obst_x)[nObs], double (&obst_y)[nObs], double (&obst_w)[nObs], double (&obst_h)[nObs], double (&obst_state)[nObs], double (&obst_v)[nObs], int score) {
    for (int i = 0; i < nObs; ++i) {
        obst_state[i] = 1;
        obst_v[i] = 7 + score * 0.2;
        obst_h[i] = (rand() % 30 + 30);
        obst_w[i] = (rand() % 10 + 10);
        if (i == 0) {
            obst_x[i] = rand() % 50 + 800;
        } else {
            obst_x[i] = obst_x[i - 1] + (rand() % 3) * 100 + 300;
        }
        obst_y[i] = 75;
    }
}

void DinosaurGame::run() {
    YsSoundPlayer player;
    YsSoundPlayer::SoundData wav_0;
    std::string wav0 = "U.N.wav";
    if (YSOK != wav_0.LoadWav(wav0.c_str())) {
        std::cout << "Failed to read " << wav0 << std::endl;
    }
    player.Start();
    player.PlayOneShot(wav_0);
    generateObs(obst_x, obst_y, obst_w, obst_h, obst_state, obst_v, score);

    while (true) {
        double dt = 0.05;
        FsPollDevice();
        auto key = FsInkey();
        if (FSKEY_ESC == key) {
            break;
        }
        switch (key) {
            case FSKEY_SPACE:
                if (pstate == 0) {
                    pstate = 1;
                    ball_vy = 200;
                }
                break;

            case FSKEY_LEFT:
                if (ball_x > 10 || ball_x < 790) {
                    ball_x -= 3;
                }
                break;

            case FSKEY_RIGHT:
                if (ball_x > 10 || ball_x < 790) {
                    ball_x += 3;
                }
                break;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DrawScene();
        DrawHUD(score, nLifes);

        if (nLifes > 0) {
            for (int i = 0; i < nObs; i++) {
                if (0 != obst_state[i] && CheckCollision(ball_x, ball_y, obst_x[i], obst_y[i], obst_w[i], obst_h[i])) {
                    obst_state[i] = 0;
                    pstate = 2;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    pstate = 1;
                    pstate = 2;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    pstate = 0;
                    nLifes -= 20;
                }
            }
            for (int i = 0; i < nObs; i++) {
                if (0 != obst_state[i] && CheckPassing(ball_x, ball_y, obst_x[i], obst_y[i], obst_w[i], obst_h[i])) {
                    score++;
                }
            }

            for (int i = 0; i < nObs; i++) {
                obst_x[i] -= obst_v[i];

                if (0 > obst_x[i]) {
                    int distance = MIN_DISTANCE_BETWEEN_OBSTACLES + (rand() % (MAX_DISTANCE_BETWEEN_OBSTACLES - MIN_DISTANCE_BETWEEN_OBSTACLES));
                    if (i == 0) {
                        obst_x[i] = obst_x[nObs - 1] + distance;  // Assuming circular queue of obstacles
                    } else {
                        obst_x[i] = obst_x[i - 1] + distance;
                    }
                    obst_state[i] = 1;
                }
            }

            for (int i = 0; i < nObs; i++) {
                DrawObs(obst_x[i], obst_y[i], obst_w[i], obst_h[i], obst_state[i]);
            }

            if (pstate < 2) {
                DrawDinosaur(ball_x, ball_y, nLifes);
                ball_x += ball_vx * dt;
                ball_y += ball_vy * dt;
                ball_vy -= g;
                if (ball_y < 95) {
                    pstate = 0;
                    ball_y = 95;
                }
            }
        } else {
            DrawEnd(score);
        }
        FsSwapBuffers();
        FsSleep(20);
    }
    player.End();
}
