#define GL_SILENCE_DEPRECATION

#include "snakegame.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"

using namespace std;
const double pi = 3.1415927;

void DrawCircle(double cx, double cy, double rad) {
    const double YS_PI = 3.1415927;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 64; i++) {
        double angle = (double)i * YS_PI / 32.0;
        double x = (double)cx + cos(angle) * (double)rad;
        double y = (double)cy + sin(angle) * (double)rad;
        glVertex2d(x, y);
    }
    glEnd();
}

void Food::InitializeFood() {
    x = rand() % 750 + 25;
    y = rand() % 550 + 25;
    type = rand() % 4 + 1;
    radius = 5;
    state = 1;

    switch (type) {
        case 1:
            colorR = 0;  // black food
            colorG = 0;
            colorB = 0;
            break;
        case 2:
            colorR = 1.0;  // red food
            colorG = 0.0;
            colorB = 0.0;
            break;
        case 3:
            colorR = 0.0;  // green food
            colorG = 1.0;
            colorB = 0.0;
            break;
        case 4:
            colorR = 0.0;  // blue food
            colorG = 0.0;
            colorB = 1.0;
            break;
    }
}

void Food::DrawFood() {
    glColor3f(colorR, colorG, colorB);
    DrawCircle(x, y, radius);
}

bool Food::CheckHitFood(double snake_x, double snake_y, double food_x, double food_y, double snake_width, double snake_height, double food_rad) {
    return ((snake_x - food_x) >= -(snake_width + food_rad) && (snake_x - food_x) <= food_rad && (snake_y - food_y) >= -(snake_height + food_rad) && (snake_y - food_y) <= food_rad);
}

void Missile::DrawMissile() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x - 15, y + 20);
    glVertex2f(x - 15, y + 65);
    glVertex2f(x + 15, y + 65);
    glVertex2f(x + 15, y + 20);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(x - 15, y + 68);
    glVertex2i(x - 15, y + 75);

    glVertex2i(x - 5, y + 68);
    glVertex2i(x - 5, y + 75);

    glVertex2i(x + 5, y + 68);
    glVertex2i(x + 5, y + 75);

    glVertex2i(x + 15, y + 68);
    glVertex2i(x + 15, y + 75);
    glEnd();
}

void Missile::MoveMissile(double& x, double& y, double speed) {
    y -= speed;
    if (y < -100) {
        y = 220;
    }
}

int Missile::CheckHitMissile(double snake_x, double snake_y, double missile_x, double missile_y) {
    double relativeX, relativeY;
    relativeX = snake_x - missile_x;
    relativeY = snake_y - missile_y;
    if (-15 <= relativeX && relativeX <= 15 && 0 <= relativeY && relativeY < 75)
        return 1;
    else
        return 0;
}

void Bar::DrawBar() {
    glColor3ub(138, 43, 226);
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + w, y);
    glVertex2i(x + w, y + h);
    glVertex2i(x, y + h);
    glEnd();
}

int Bar::CheckHitBar(double snake_x, double snake_y, double bar_x, double bar_y, double barsizeX, double barsizeY) {
    double relativeX, relativeY;
    relativeX = snake_x - bar_x;
    relativeY = snake_y - bar_y;
    if (0 <= relativeX && relativeX < barsizeX && 0 <= relativeY && relativeY < barsizeY)
        return 1;
    else
        return 0;
}

void Cannon::Cannon1() {
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2i(420, 550);
    glVertex2i(450, 550);
    glVertex2i(450, 580);
    glVertex2i(420, 580);
    glEnd();

    glLineWidth(2);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(450, 550);
    glVertex2d(450 + 25 * cos(cannonAngle), 550 - 25 * sin(cannonAngle));
    glEnd();
}

void Cannon::Cannon2() {
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2i(740, 550);
    glVertex2i(770, 550);
    glVertex2i(770, 580);
    glVertex2i(740, 580);
    glEnd();

    glLineWidth(2);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(740, 550);
    glVertex2d(740 - 25 * cos(cannonAngle), 550 - 25 * sin(cannonAngle));
    glEnd();
}

void CannonBall::Ball() {
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);

    int i;
    for (i = 0; i < 64; i++) {
        double angle = (double)i * pi / 32.0;
        double x = (double)cx + cos(angle) * (double)rad;
        double y = (double)cy + sin(angle) * (double)rad;
        glVertex2d(x, y);
    }
    glEnd();
}
bool CannonBall::CheckHitBall(int ball_x, int ball_y, int snake_x, int snake_y, int snakeLength) {
    return (ball_x >= snake_x && ball_x <= (snake_x + 13) && ball_y >= snake_y && ball_y <= (snake_y + 13));
}

Snake::Snake() {
    snakeLength = 1;
    snakeWidth = 10;
    snakeHeight = 10;

    snakeX[0] = 30;
    snakeY[0] = 560;
    snakeDirection[0] = 0;  // Initialize direction
}

void Snake::DrawSnake(double x, double y) {
    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex2f(x, y);

    glColor3ub(0, 255, 0);
    glVertex2f(x + snakeWidth, y);

    glColor3ub(0, 0, 255);
    glVertex2f(x + snakeWidth, y + snakeHeight);

    glColor3ub(255, 255, 0);
    glVertex2f(x, y + snakeHeight);
    glEnd();
}

void Snake::HandleInput(int key) {
    switch (key) {
        case FSKEY_UP:
            if (snakeDirection[0] != 2)
                snakeDirection[0] = 1;  // Go up
            break;
        case FSKEY_DOWN:
            if (snakeDirection[0] != 1)
                snakeDirection[0] = 2;  // Go down
            break;
        case FSKEY_RIGHT:
            if (snakeDirection[0] != 4)
                snakeDirection[0] = 3;  // Go right
            break;
        case FSKEY_LEFT:
            if (snakeDirection[0] != 3)
                snakeDirection[0] = 4;  // Go left
            break;
    }
}

void Snake::MoveBody() {
    for (int i = snakeLength - 1; i > 0; --i) {
        if (snakeLength > maxLength)
            snakeLength = maxLength;

        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
}

void Snake::MoveSnake(int direction) {
    MoveBody();
    switch (direction) {
        case 1:
            snakeY[0] -= 3;  // Snake moving speed
            break;
        case 2:
            snakeY[0] += 3;
            break;
        case 3:
            snakeX[0] += 3;
            break;
        case 4:
            snakeX[0] -= 3;
            break;
    }
}
Snake::~Snake() {
    // Empty destructor
    // No dynamic memory allocation to clean up
}

SnakeGame::SnakeGame() {
}

void SnakeGame::Init() {
    Snake snake;

    // Because something goes wrong with the initial location of snake, I initialize them here at snakegame3
    snake.snakeX[0] = 300;
    snake.snakeY[0] = 550;
    snake.snakeDirection[0] = 0;
}

void SnakeGame::DrawBoundary() {
    for (int i = 0; i < 800; i += 15) {
        glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_TRIANGLES);
        glVertex2i(i, 0);
        glVertex2i(i + 20, 0);
        glVertex2i(i + 10, 20);

        glBegin(GL_TRIANGLES);
        glVertex2i(0, i);
        glVertex2i(0, i + 20);
        glVertex2i(20, i + 10);

        glBegin(GL_TRIANGLES);
        glVertex2i(i, 600);
        glVertex2i(i + 20, 600);
        glVertex2i(i + 10, 600 - 20);

        glBegin(GL_TRIANGLES);
        glVertex2i(800, i);
        glVertex2i(800, i + 20);
        glVertex2i(800 - 20, i + 10);
    }
    glEnd();
}

void SnakeGame::DrawBlueRegion() {
    glColor4ub(202, 235, 216, 0);  // Green
    glBegin(GL_POLYGON);
    glVertex2i(0, 0);
    glVertex2i(400, 0);
    glVertex2i(400, 300);
    glVertex2i(0, 300);
    glEnd();
}

void SnakeGame::DrawPinkRegion() {
    glColor4ub(255, 235, 205, 0);  // Yellow
    glBegin(GL_POLYGON);
    glVertex2i(400, 0);
    glVertex2i(800, 0);
    glVertex2i(800, 300);
    glVertex2i(400, 300);
    glEnd();
}

void SnakeGame::DrawYellowRegion() {
    glColor4ub(244, 164, 95, 0);  // Deep Yellow
    glBegin(GL_POLYGON);
    glVertex2i(0, 300);
    glVertex2i(400, 300);
    glVertex2i(400, 600);
    glVertex2i(0, 600);
    glEnd();
}

void SnakeGame::DrawGreenRegion() {
    glColor4ub(255, 192, 203, 0);  // Pink
    glBegin(GL_POLYGON);
    glVertex2i(400, 300);
    glVertex2i(800, 300);
    glVertex2i(800, 600);
    glVertex2i(400, 600);
    glEnd();
}

void SnakeGame::DrawStoneShape() {
    glLineWidth(2.0);

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(50, 450);
    glVertex2i(140, 450);
    glVertex2i(140, 510);
    glVertex2i(50, 510);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(50, 450);
    glVertex2i(140, 450);

    glVertex2i(70, 450);
    glVertex2i(70, 470);

    glVertex2i(120, 450);
    glVertex2i(120, 470);

    glVertex2i(50, 470);
    glVertex2i(140, 470);

    glVertex2i(95, 470);
    glVertex2i(95, 490);

    glVertex2i(50, 490);
    glVertex2i(140, 490);

    glVertex2i(70, 490);
    glVertex2i(70, 510);

    glVertex2i(120, 490);
    glVertex2i(120, 510);

    glVertex2i(140, 510);
    glVertex2i(50, 510);
    glEnd();

    glLineWidth(2.0);

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(260, 320);
    glVertex2i(380, 320);
    glVertex2i(380, 395);
    glVertex2i(260, 395);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(260, 320);
    glVertex2i(380, 320);

    glVertex2i(300, 320);
    glVertex2i(300, 345);

    glVertex2i(340, 320);
    glVertex2i(340, 345);

    glVertex2i(260, 345);
    glVertex2i(380, 345);

    glVertex2i(320, 345);
    glVertex2i(320, 370);

    glVertex2i(260, 370);
    glVertex2i(380, 370);

    glVertex2i(300, 370);
    glVertex2i(300, 395);

    glVertex2i(340, 370);
    glVertex2i(340, 395);

    glVertex2i(380, 395);
    glVertex2i(260, 395);
    glEnd();
}

int SnakeGame::CheckHitWall(double snake_x, double snake_y, double wall_x, double wall_y, double wallsizeX, double wallsizeY) {
    double relativeX, relativeY;
    relativeX = snake_x - wall_x;
    relativeY = snake_y - wall_y;
    if (0 <= relativeX && relativeX < wallsizeX && 0 <= relativeY && relativeY < wallsizeY)
        return 1;
    else
        return 0;
}

int SnakeGame::Play(void) {
    YsSoundPlayer player;
    YsSoundPlayer::SoundData bgm;

    FsChangeToProgramDir();
    string fileName = "bgm.wav";
    if (YSOK != bgm.LoadWav(fileName.c_str())) {
        std::cout << "Cannot load wave file." << std::endl;
        return 1;
    }
    player.Start();
    player.PlayBackground(bgm);

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // FsOpenWindow(16, 16, 800, 600, 0);

    time_t lastHitTime1 = 0;
    time_t lastHitTime3 = 0;
    /* Moved to 'SnakeGam::Init();
    const double gravity = 98.1;
    const int nFood = 200;  // Number of food generated each time
    double score = 0;   // Count the score of the game

    Snake snake;
    Food foods[nFood];
    Bar bar1, bar2;
    Missile missile1, missile3;
    Cannon cannon1, cannon2;
    CannonBall ball1, ball2;
    SnakeGame game;
    */

    bar1.x = 400;
    bar1.y = 100;
    bar1.w = 50;
    bar1.h = 20;
    bar1.state = 1;
    bar2.x = 750;
    bar2.y = 200;
    bar2.w = 50;
    bar2.h = 20;
    bar2.state = 1;
    int direction1 = 1, direction2 = -1;

    cannon1.cannonAngle = 45 * pi / 180;
    cannon2.cannonAngle = 45 * pi / 180;
    ball1.vel = 200;
    ball2.vel = 350;
    ball1.rad = 3;
    ball2.rad = 3;
    ball1.state = 0;
    ball2.state = 0;
    double dt = 0.05;
    int balls = 0;  // number of cannonball shoot

    double vball1_x, vball1_y;  // ball velocity on horizontal axis and vertical axis
    double vball2_x, vball2_y;
    ball1.cx = 450 + 25 * cos(cannon1.cannonAngle);
    ball1.cy = 550 - 25 * sin(cannon1.cannonAngle);
    ball2.cx = 740 - 25 * cos(cannon2.cannonAngle);
    ball2.cy = 550 - 25 * sin(cannon2.cannonAngle);

    missile1.state = 1;
    missile3.state = 1;
    missile1.y = 220;
    missile1.x = 105;
    missile3.y = 220;
    missile3.x = 305;
    int terminate = 0;

    time_t start_time = time(NULL);
    bool hitWall = false;
    bool hitBoundary = false;
    time_t hitWallTime;
    time_t hitBoundaryTime;
    time_t currentTime;

    for (int i = 0; i < nFood; ++i) {
        foods[i].InitializeFood();
        foods[i].state = 1;
    }

    // Because something goes wrong with the initial location of snake, I initialize them here at snakegame3
    snake.snakeX[0] = 300;
    snake.snakeY[0] = 550;
    snake.snakeDirection[0] = 0;

    while (0 == terminate) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        FsPollDevice();
        player.KeepPlaying();
        int key = FsInkey();

        if (key == FSKEY_ESC) {
            terminate = 1;
            return score;
        }

        // set background color to white
        glColor3f(255, 255, 255);
        // rendar background
        glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(0, 600);
        glVertex2i(800, 600);
        glVertex2i(800, 0);
        glEnd();

        if (snake.snakeX[0] <= 15 || snake.snakeX[0] >= 785 || snake.snakeY[0] <= 15 || snake.snakeY[0] >= 585) {
            terminate = 1;  // The game will be over if the snake touches the boundary
            string scoreString = "Total Score: " + to_string(score);
            const char* scoreStr = scoreString.c_str();
            glColor3ub(0, 0, 0);
            glRasterPos2i(360, 300);
            YsGlDrawFontBitmap12x16("Game over!");
            glRasterPos2i(300, 340);
            YsGlDrawFontBitmap12x16(scoreStr);
            player.Stop(bgm);
        }

        // If snake eats the food, the length of the snake will increase 1 unit, the current food is eliminated, and new food is generated
        for (int i = 0; i < nFood; ++i) {
            if (foods[i].state == 1 && foods[i].CheckHitFood(snake.snakeX[0], snake.snakeY[0], foods[i].x, foods[i].y, snake.snakeWidth, snake.snakeHeight, foods[i].radius)) {
                switch (foods[i].type) {
                    case 1:
                        snake.snakeLength += 0.5;
                        score += 0.5;
                        break;
                    case 2:
                        snake.snakeLength += 1;
                        score += 1;
                        break;
                    case 3:
                        snake.snakeLength += 1.5;
                        score += 1.5;
                        break;
                    case 4:
                        snake.snakeLength += 2;
                        score += 2;
                        break;
                }
                foods[i].state = 0;
                foods[i].x = rand() % 750 + 25;
                foods[i].y = rand() % 550 + 25;
                foods[i].state = 1;
            }
        }

        if (bar1.x >= 730) {
            direction1 = -1;
        } else if (bar1.x <= 400) {
            direction1 = 1;
        }
        bar1.x += direction1 * 8;

        if (bar2.x >= 730) {
            direction2 = -1;
        } else if (bar2.x <= 400) {
            direction2 = 1;
        }
        bar2.x += direction2 * 8;

        if (0 == ball1.state) {
            ball1.state = 1;
            vball1_x = ball1.vel * cos(cannon1.cannonAngle);
            vball1_y = ball1.vel * sin(cannon1.cannonAngle);
        }
        if (ball1.state != 0)  // Apply Euler��s method to update ball position
        {
            ball1.cx += vball1_x * dt;
            ball1.cy -= vball1_y * dt;
            vball1_y -= gravity * dt;

            if (ball1.cx > 800 || ball1.cy <= 300) {
                ball1.state = 0;
                balls++;
                ball1.cx = 450 + 25 * cos(cannon1.cannonAngle);
                ball1.cy = 550 - 25 * sin(cannon1.cannonAngle);
            }
        }
        if (0 == ball2.state) {
            ball2.state = 1;
            vball2_x = ball2.vel * cos(cannon2.cannonAngle);
            vball2_y = ball2.vel * sin(cannon2.cannonAngle);
        }
        if (ball2.state != 0)  // Apply Euler��s method to update ball position
        {
            ball2.cx -= vball2_x * dt;
            ball2.cy -= vball2_y * dt;
            vball2_y -= gravity * dt;

            if (ball2.cx <= 400 || ball2.cy <= 300) {
                ball2.state = 0;
                balls++;
                ball2.cx = 740 - 25 * cos(cannon2.cannonAngle);
                ball2.cy = 550 - 25 * sin(cannon2.cannonAngle);
            }
        }

        for (int i = 0; i < snake.snakeLength; ++i) {
            if (bar1.CheckHitBar(snake.snakeX[i], snake.snakeY[i], bar1.x, bar1.y, bar1.w, bar1.h) == true) {
                if (bar1.state == 1) {
                    snake.snakeLength -= 2;
                    bar1.state = 0;
                    score -= 2;
                }
            }
        }
        for (int i = 0; i < snake.snakeLength; ++i) {
            if (bar2.CheckHitBar(snake.snakeX[i], snake.snakeY[i], bar2.x, bar2.y, bar2.w, bar2.h) == true) {
                if (bar2.state == 1) {
                    snake.snakeLength -= 2;
                    bar2.state = 0;
                    score -= 2;
                }
            }
        }

        for (int i = 0; i < snake.snakeLength; ++i) {
            if (missile1.CheckHitMissile(snake.snakeX[i], snake.snakeY[i], missile1.x, missile1.y) == 1) {
                if (missile1.state == 1) {
                    snake.snakeLength -= 3;
                    missile1.state = 0;
                    score -= 3;
                    missile1.y = 220;
                    lastHitTime1 = time(NULL);
                    missile1.state = 1;
                }
            }
        }

        for (int i = 0; i < snake.snakeLength; ++i) {
            if (missile3.CheckHitMissile(snake.snakeX[i], snake.snakeY[i], missile3.x, missile3.y) == 1) {
                if (missile3.state == 1) {
                    snake.snakeLength -= 3;
                    missile3.state = 0;
                    score -= 3;
                    missile3.y = 220;
                    lastHitTime3 = time(NULL);
                    missile3.state = 1;
                }
            }
        }

        for (int i = 0; i < snake.snakeLength; ++i) {
            if (ball1.CheckHitBall(ball1.cx, ball1.cy, snake.snakeX[i], snake.snakeY[i], snake.snakeLength)) {
                ball1.state = 0;
                snake.snakeLength -= 1;
                if (snake.snakeLength <= 1) {
                    snake.snakeLength = 1;
                }
                ball1.cx = 450 + 25 * cos(cannon1.cannonAngle);
                ball1.cy = 550 - 25 * sin(cannon1.cannonAngle);
                score -= 1;
            }
        }

        for (int i = 0; i < snake.snakeLength; ++i) {
            if (ball2.CheckHitBall(ball2.cx, ball2.cy, snake.snakeX[i], snake.snakeY[i], snake.snakeLength)) {
                ball2.state = 0;
                snake.snakeLength -= 1;
                if (snake.snakeLength <= 1) {
                    snake.snakeLength = 1;
                }
                ball2.cx = 740 - 25 * cos(cannon2.cannonAngle);
                ball2.cy = 550 - 25 * sin(cannon2.cannonAngle);
                score -= 1;
            }
        }
        time_t current_time = time(NULL);
        double elapsed_time = difftime(current_time, start_time);
        if (elapsed_time <= 5.0) {
            glColor3f(0, 0, 0);
            glRasterPos2i(320, 300);
            YsGlDrawFontBitmap12x16("Gluttonous Snake");
            glRasterPos2i(50, 340);
            YsGlDrawFontBitmap12x16("Black: +0.5pt; Red: +1.0pt; Green: +1.5pt; Blue: +2.0pt");
            glRasterPos2i(50, 380);
            YsGlDrawFontBitmap12x16("Cannon Ball: -1pt; Bar: -2pt; Missile: -3pt; Wall: Game Over");
            glRasterPos2i(175, 420);
            YsGlDrawFontBitmap12x16("You have 20 seconds to get enough points!");
        } else {
            // Moved the key input here from the beginning of main code
            snake.HandleInput(key);
            snake.MoveSnake(snake.snakeDirection[0]);

            /*
            game.DrawBlueRegion();
            game.DrawYellowRegion();
            game.DrawPinkRegion();
            game.DrawGreenRegion();
            */
            DrawBlueRegion();
            DrawYellowRegion();
            DrawPinkRegion();
            DrawGreenRegion();

            for (int i = 0; i < nFood; ++i) {
                if (foods[i].state == 1) {
                    foods[i].DrawFood();
                }
            }
            for (int i = 0; i < snake.snakeLength; ++i) {
                snake.DrawSnake(snake.snakeX[i], snake.snakeY[i]);
            }

            // game.DrawStoneShape();
            DrawStoneShape();
            if (bar1.state == 1) {
                bar1.DrawBar();
            }
            if (bar2.state == 1) {
                bar2.DrawBar();
            }

            cannon1.Cannon1();
            cannon2.Cannon2();
            time_t currentTime1 = time(NULL);
            if (currentTime1 - lastHitTime1 >= 2) {
                if (missile1.state != 0) {
                    missile1.DrawMissile();
                    missile1.MoveMissile(missile1.x, missile1.y, 1);
                }
            }

            time_t currentTime3 = time(NULL);
            if (currentTime3 - lastHitTime3 >= 2) {
                if (missile3.state != 0) {
                    missile3.DrawMissile();
                    missile3.MoveMissile(missile3.x, missile3.y, 3);
                }
            }

            if (ball1.state != 0) {
                ball1.Ball();
            }

            if (ball2.state != 0) {
                ball2.Ball();
            }
            for (int i = 0; i < snake.snakeLength; ++i) {
                if (CheckHitWall(snake.snakeX[i], snake.snakeY[i], 50, 450, 90, 60) == true) {
                    hitWall = true;
                    hitWallTime = time(NULL);
                    terminate = 1;  // The game will be over if the snake touches the boundary
                }
                if (hitWall) {
                    time_t currentTime = time(NULL);
                    double elapsedTime = difftime(currentTime, hitWallTime);

                    if (elapsedTime <= 5.0) {
                        string scoreString = "Total Score: " + to_string(score);
                        const char* scoreStr = scoreString.c_str();
                        glColor3ub(0, 0, 0);
                        glRasterPos2i(360, 300);
                        YsGlDrawFontBitmap12x16("Game over!");
                        glRasterPos2i(300, 340);
                        YsGlDrawFontBitmap12x16(scoreStr);
                    } else {
                        player.Stop(bgm);
                        break;
                    }
                }
            }

            for (int i = 0; i < snake.snakeLength; ++i) {
                // if (game.CheckHitWall(snake.snakeX[i], snake.snakeY[i], 260, 320, 120, 75) == true)
                if (CheckHitWall(snake.snakeX[i], snake.snakeY[i], 260, 320, 120, 75) == true) {
                    hitWall = true;
                    hitWallTime = time(NULL);
                    terminate = 1;  // The game will be over if the snake touches the boundary
                }
                if (hitWall) {
                    time_t currentTime = time(NULL);
                    double elapsedTime = difftime(currentTime, hitWallTime);

                    if (elapsedTime <= 5.0) {
                        string scoreString = "Total Score: " + to_string(score);
                        const char* scoreStr = scoreString.c_str();
                        glColor3ub(0, 0, 0);
                        glRasterPos2i(360, 300);
                        YsGlDrawFontBitmap12x16("Game over!");
                        glRasterPos2i(300, 340);
                        YsGlDrawFontBitmap12x16(scoreStr);
                    } else {
                        player.Stop(bgm);
                        break;
                    }
                }
            }

            for (int i = 0; i < snake.snakeLength; ++i) {
                time_t currentTime = time(NULL);
                double duration = difftime(currentTime, start_time);

                if (duration == 20.0) {
                    string scoreString = "Total Score: " + to_string(score);
                    const char* scoreStr = scoreString.c_str();
                    glColor3ub(0, 0, 0);
                    glRasterPos2i(360, 300);
                    YsGlDrawFontBitmap12x16("Game over!");
                    glRasterPos2i(300, 340);
                    YsGlDrawFontBitmap12x16(scoreStr);
                }
                if (duration > 20) {
                    player.Stop(bgm);
                    return score;
                }
            }

            // game.DrawBoundary();
            DrawBoundary();
            glColor3ub(0, 0, 0);
            glRasterPos2i(10, 35);
            char scoreStr[50];
            sprintf(scoreStr, "Score: %.1f", score);
            YsGlDrawFontBitmap20x32(scoreStr);
        }
        // glFlush();
        FsSwapBuffers();
        FsSleep(10);
    }
    return score;
}
