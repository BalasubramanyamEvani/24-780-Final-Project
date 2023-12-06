#pragma once
#ifndef SNAKEGAME_H_IS_INCLUDED
#define SNAKEGAME_H_IS_INCLUDED

class Food {
   public:
    double x;
    double y;
    int type;
    double radius;
    int state;
    double colorR;
    double colorG;
    double colorB;
    void InitializeFood();
    void DrawFood();
    bool CheckHitFood(double snake_x, double snake_y, double food_x, double food_y, double snake_width, double snake_height, double food_rad);
};

class Missile {
   public:
    int state;
    double x, y;
    double w, h;
    void DrawMissile();
    void MoveMissile(double& x, double& y, double speed);
    int CheckHitMissile(double snake_x, double snake_y, double missile_x, double missile_y);
};

class Bar {
   public:
    int state;
    double x, y;
    double w, h;
    void DrawBar();
    int CheckHitBar(double snake_x, double snake_y, double bar_x, double bar_y, double barsizeX, double barsizeY);
};

class Cannon {
   public:
    double cannonAngle;
    void Cannon1();
    void Cannon2();
};

class CannonBall {
   public:
    double cx, cy;
    double rad;
    double vel;
    int state;
    void Ball();
    bool CheckHitBall(int ball_x, int ball_y, int snake_x, int snake_y, int snakeLength);
};

class Snake {
   public:
    Snake();
    ~Snake();

    void DrawSnake(double x, double y);
    void MoveSnake(int direction);
    void MoveBody();
    void HandleInput(int key);

    double snakeLength;
    const int maxLength = 1000;
    double snakeX[1000];
    double snakeY[1000];
    int snakeDirection[1000];

    double snakeWidth;
    double snakeHeight;
};

class SnakeGame {
    const double gravity = 98.1;
    static const int nFood = 200;  // Number of food generated each time
    double score = 0;              // Count the score of the game

    Snake snake;
    Food foods[nFood];
    Bar bar1, bar2;
    Missile missile1, missile3;
    Cannon cannon1, cannon2;
    CannonBall ball1, ball2;
    // SnakeGame game;

   public:
    SnakeGame();
    void Init();
    int Play();
    void DrawBoundary();
    void DrawBlueRegion();
    void DrawPinkRegion();
    void DrawYellowRegion();
    void DrawGreenRegion();
    void DrawStoneShape();
    int CheckHitWall(double snake_x, double snake_y, double wall_x, double wall_y, double wallsizeX, double wallsizeY);
};

#endif  // !SNAKEGAME_H_IS_INCLUDED
