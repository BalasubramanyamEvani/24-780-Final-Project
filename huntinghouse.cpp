#define GL_SILENCE_DEPRECATION

#include "huntinghouse.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "air_battle.h"
#include "dinosaur.h"
#include "floor.h"
#include "fssimplewindow.h"
#include "ladder.h"
#include "maze.h"
#include "ysglfontdata.h"

/**
 * @brief Shape game
 *
 */

// Constants
const int windowWidth = 800;
const int windowHeight = 600;
const float ballRadius = 20.0f;
const float triangleSide = 40.0f;
const float initialSpeed = 2.0f;
const float sideLength = 30.0f;

// Ball and triangle positions
float ballX1 = 100.0f, ballY1 = 100.0f;
float ballX2 = 300.0f, ballY2 = 300.0f;
float ballX3 = 500.0f, ballY3 = 500.0f;
float triangleX1 = 200.0f, triangleY1 = 200.0f;
float triangleX2 = 400.0f, triangleY2 = 400.0f;
float squareX1 = 50.0f, squareY1 = 50.0f;

// Ball and triangle velocities
float ballVX1 = 15.f, ballVY1 = 20.f;
float ballVX2 = 20.f, ballVY2 = -10.f;
float ballVX3 = -25.f, ballVY3 = 15.f;
float triangleVX1 = 12.f, triangleVY1 = 10.f;
float triangleVX2 = 20.f, triangleVY2 = 22.f;
float squareVX1 = 30.f, squareVY1 = 20.f;

float fastForward = 1.0f;

bool isShapeShown[6] = {true, true, true, true, true, true};

// Function to draw a ball with color gradation and alpha blending
void drawBall(float x, float y) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.1415926 / 180.0;
        float xPos = x + ballRadius * cos(angle);
        float yPos = y + ballRadius * sin(angle);

        // Calculate a gradient color based on the angle
        float r = cos(angle) * 0.5 + 0.5;  // Red component
        float g = 0.0f;                    // Green component
        float b = sin(angle) * 0.5 + 0.5;  // Blue component

        // Set the color with alpha blending (0.5f for semi-transparency)
        glColor4f(r, g, b, 0.5f);

        glVertex2f(xPos, yPos);
    }
    glEnd();
}
// Function to draw a ball with color gradation and alpha blending
void drawBallMaze(float x, float y, int ballRadiusMaze) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.1415926 / 180.0;
        float xPos = x + ballRadiusMaze * cos(angle);
        float yPos = y + ballRadiusMaze * sin(angle);

        // Calculate a gradient color based on the angle
        float r = cos(angle) * 0.5 + 0.5;  // Red component
        float g = 0.0f;                    // Green component
        float b = sin(angle) * 0.5 + 0.5;  // Blue component

        // Set the color with alpha blending (0.5f for semi-transparency)
        glColor4f(r, g, b, 0.5f);

        glVertex2f(xPos, yPos);
    }
    glEnd();
}
// Function to draw a triangle with color gradation and alpha blending
void drawTriangle(float x, float y) {
    glBegin(GL_TRIANGLES);

    // Calculate colors for the three vertices of the triangle
    float r1 = 0.0f;              // Red component of vertex 1
    float g1 = y / windowHeight;  // Green component based on Y position
    float b1 = 1.0f;              // Blue component of vertex 1

    glColor4f(r1, g1, b1, 0.5f);
    glVertex2f(x, y);

    float r2 = x / windowWidth;  // Red component based on X position
    float g2 = 0.0f;             // Green component of vertex 2
    float b2 = 1.0f;             // Blue component of vertex 2

    glColor4f(r2, g2, b2, 0.5f);
    glVertex2f(x + triangleSide, y);

    float r3 = 1.0f;  // Red component of vertex 3
    float g3 = 1.0f;  // Green component of vertex 3
    float b3 = 1.0f;  // Blue component of vertex 3

    // Set colors with alpha blending (0.5f for semi-transparency)
    glColor4f(r2, g1, b3, 0.5f);
    glVertex2f(x, y + triangleSide);

    glEnd();
}

// Function to draw a square with color gradation and alpha blending
void drawSquare(float x, float y) {
    glBegin(GL_QUADS);

    // Calculate gradient colors for the four vertices of the square
    float r1 = 0.0f;              // Red component of vertex 1
    float g1 = y / windowHeight;  // Green component based on Y position
    float b1 = x / windowWidth;   // Blue component based on X position

    float r2 = 1.0f - b1;  // Red component of vertex 2
    float g2 = 1.0f - g1;  // Green component of vertex 2
    float b2 = 1.0f;       // Blue component of vertex 2

    float r3 = 1.0f - r1;  // Red component of vertex 3
    float g3 = 1.0f;       // Green component of vertex 3
    float b3 = 1.0f - b1;  // Blue component of vertex 3

    float r4 = 1.0f;       // Red component of vertex 4
    float g4 = 1.0f - r1;  // Green component of vertex 4
    float b4 = 1.0f - g1;  // Blue component of vertex 4

    // Set colors with alpha blending (0.5f for semi-transparency)
    glColor4f(r1, g1, b1, 0.5f);
    glVertex2f(x, y);

    glColor4f(r2, g2, b2, 0.5f);
    glVertex2f(x + sideLength, y);

    glColor4f(r3, g3, b3, 0.5f);
    glVertex2f(x + sideLength, y + sideLength);

    glColor4f(r4, g4, b4, 0.5f);
    glVertex2f(x, y + sideLength);

    glEnd();
}

// function to check shapes collision
bool isCollision(float x1, float y1, float x2, float y2, float radius1, float radius2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    float distance = sqrt(dx * dx + dy * dy);
    return distance <= (radius1 + radius2);
}

// function to check triangle collision to destroy ball
bool isTriangleCollision(float x1, float y1, float x2, float y2, float radius1, float traingleSide) {
    if ((x1 + radius1 >= x2 && x1 + radius1 <= x2 + triangleSide) || (x1 - radius1 <= x2 + triangleSide && x1 - radius1 >= x2)) {
        if ((y1 + radius1 >= y2 && y1 + radius1 <= y2 + triangleSide) || (y1 - radius1 <= y2 + triangleSide && y1 - radius1 >= y2)) {
            return true;
        }
    }
    return false;
}

// Function to update the positions and velocities of objects
void update() {
    // Update ball positions
    ballX1 += ballVX1;
    ballY1 += ballVY1;
    ballX2 += ballVX2;
    ballY2 += ballVY2;
    ballX3 += ballVX3;
    ballY3 += ballVY3;

    // Update triangle positions
    triangleX1 += triangleVX1;
    triangleY1 += triangleVY1;
    triangleX2 += triangleVX2;
    triangleY2 += triangleVY2;

    // Update square positions
    squareX1 += squareVX1;
    squareY1 += squareVY1;

    // Checking Collision
    if (isCollision(ballX1, ballY1, ballX2, ballY2, ballRadius, ballRadius)) {
        std::swap(ballVX1, ballVX2);
        std::swap(ballVY1, ballVY2);
    }
    if (isCollision(ballX1, ballY1, ballX3, ballY3, ballRadius, ballRadius)) {
        std::swap(ballVX1, ballVX3);
        std::swap(ballVY1, ballVY3);
    }
    if (isTriangleCollision(ballX1, ballY1, triangleX1, triangleY1, ballRadius, triangleSide)) {
        std::swap(ballVX1, triangleVX1);
        std::swap(ballVY1, triangleVY1);
    }
    if (isTriangleCollision(ballX1, ballY1, triangleX2, triangleY2, ballRadius, triangleSide)) {
        std::swap(ballVX1, triangleVX2);
        std::swap(ballVY1, triangleVY2);
    }
    if (isCollision(ballX1, ballY1, squareX1, squareY1, ballRadius, sideLength)) {
        std::swap(ballVX1, squareVX1);
        std::swap(ballVY1, squareVY1);
    }
    if (isCollision(ballX2, ballY2, ballX3, ballY3, ballRadius, ballRadius)) {
        std::swap(ballVX2, ballVX3);
        std::swap(ballVY2, ballVY3);
    }
    if (isTriangleCollision(ballX2, ballY2, triangleX1, triangleY1, ballRadius, triangleSide)) {
        std::swap(ballVX2, triangleVX1);
        std::swap(ballVY2, triangleVY1);
    }
    if (isTriangleCollision(ballX2, ballY2, triangleX2, triangleY2, ballRadius, triangleSide)) {
        std::swap(ballVX2, triangleVX2);
        std::swap(ballVY2, triangleVY2);
    }
    if (isCollision(ballX2, ballY2, squareX1, squareY1, ballRadius, sideLength)) {
        std::swap(ballVX2, squareVX1);
        std::swap(ballVY2, squareVY1);
    }
    if (isTriangleCollision(ballX3, ballY3, triangleX1, triangleY1, triangleSide, triangleSide)) {
        std::swap(ballVX3, triangleVX1);
        std::swap(ballVY3, triangleVY1);
    }
    if (isTriangleCollision(ballX3, ballY3, triangleX2, triangleY2, ballRadius, ballRadius)) {
        std::swap(ballVX3, triangleVX2);
        std::swap(ballVY3, triangleVY2);
    }
    if (isCollision(ballX3, ballY3, squareX1, squareY1, ballRadius, ballRadius)) {
        std::swap(ballVX3, squareVX1);
        std::swap(ballVY3, squareVY1);
    }
    if (isCollision(triangleX1, triangleY1, triangleX2, triangleY2, ballRadius, ballRadius)) {
        std::swap(triangleVX1, triangleVX2);
        std::swap(triangleVY1, triangleVY2);
    }
    if (isCollision(triangleX1, triangleY1, squareX1, squareY1, ballRadius, sideLength)) {
        std::swap(triangleVX1, squareVX1);
        std::swap(triangleVY1, squareVY1);
    }
    if (isCollision(triangleX2, triangleY2, squareX1, squareY1, ballRadius, sideLength)) {
        std::swap(triangleVX2, squareVX1);
        std::swap(triangleVY2, squareVY1);
    }

    // Check for collisions with window edges
    if (ballX1 + ballRadius >= windowWidth || ballX1 - ballRadius <= 0) {
        ballVX1 = -ballVX1;  // Bounce horizontally
    }
    if (ballY1 + ballRadius >= windowHeight || ballY1 - ballRadius <= 0) {
        ballVY1 = -ballVY1;  // Bounce vertically
    }

    if (ballX2 + ballRadius >= windowWidth || ballX2 - ballRadius <= 0) {
        ballVX2 = -ballVX2;  // Bounce horizontally
    }
    if (ballY2 + ballRadius >= windowHeight || ballY2 - ballRadius <= 0) {
        ballVY2 = -ballVY2;  // Bounce vertically
    }

    if (ballX3 + ballRadius >= windowWidth || ballX3 - ballRadius <= 0) {
        ballVX3 = -ballVX3;  // Bounce horizontally
    }
    if (ballY3 + ballRadius >= windowHeight || ballY3 - ballRadius <= 0) {
        ballVY3 = -ballVY3;  // Bounce vertically
    }

    if (triangleX1 + triangleSide >= windowWidth || triangleX1 <= 0) {
        triangleVX1 = -triangleVX1;  // Bounce horizontally
    }
    if (triangleY1 + triangleSide >= windowHeight || triangleY1 <= 0) {
        triangleVY1 = -triangleVY1;  // Bounce vertically
    }

    if (triangleX2 + triangleSide >= windowWidth || triangleX2 <= 0) {
        triangleVX2 = -triangleVX2;  // Bounce horizontally
    }
    if (triangleY2 + triangleSide >= windowHeight || triangleY2 <= 0) {
        triangleVY2 = -triangleVY2;  // Bounce vertically
    }

    if (squareX1 + sideLength >= windowWidth || squareX1 <= 0) {
        squareVX1 = -squareVX1;  // Bounce horizontally
    }
    if (squareY1 + sideLength >= windowHeight || squareY1 <= 0) {
        squareVY1 = -squareVY1;  // Bounce vertically
    }
}

// reversing direction of shapes
void reverseAll() {
    ballVX1 *= -1;
    ballVY1 *= -1;
    ballVX2 *= -1;
    ballVY2 *= -1;
    ballVX3 *= -1;
    ballVY3 *= -1;
    triangleVX1 *= -1;
    triangleVY1 *= -1;
    triangleVX2 *= -1;
    triangleVY2 *= -1;
    squareVX1 *= -1;
    squareVY1 *= -1;
}

// Function to display the scene
void display() {
    // Draw balls, squares and triangles
    if (isShapeShown[0]) {
        drawBall(ballX1, ballY1);
    }
    if (isShapeShown[1]) {
        drawBall(ballX2, ballY2);
    }
    if (isShapeShown[2]) {
        drawBall(ballX3, ballY3);
    }
    drawTriangle(triangleX1, triangleY1);
    drawTriangle(triangleX2, triangleY2);
    drawSquare(squareX1, squareY1);
}

int CheckPoint(int mx, int my) {
    int width = 50;
    int height = 50;

    if (ballX1 - width / 2 <= mx && mx <= ballX1 + width / 2 && ballY1 - height / 2 <= my && my <= ballY1 + height / 2) {
        return 1;
    } else if (ballX2 - width / 2 <= mx && mx <= ballX2 + width / 2 && ballY2 - height / 2 <= my && my <= ballY2 + height / 2) {
        return 1;
    } else if (ballX3 - width / 2 <= mx && mx <= ballX3 + width / 2 && ballY3 - height / 2 <= my && my <= ballY3 + height / 2) {
        return 1;
    } else if (triangleX1 - width / 2 <= mx && mx <= triangleX1 + width / 2 && triangleY1 - height / 2 <= my && my <= triangleY1 + height / 2) {
        return 1;
    } else if (triangleX2 - width / 2 <= mx && mx <= triangleX2 + width / 2 && triangleY2 - height / 2 <= my && my <= triangleY2 + height / 2) {
        return 1;
    } else if (squareX1 - width / 2 <= mx && mx <= squareX1 + width / 2 && squareY1 - height / 2 <= my && my <= squareY1 + height / 2) {
        return 1;
    } else {
        return 0;
    }
}

int Abd_game(void) {
    int tempVar = 0;

    unsigned long currTime = 0;
    unsigned long endTimer = 20;
    unsigned long start_time = 0;

    bool endAnimation = false;

    int lb, mb, rb, mx, my;
    int mouseEvent;
    int point = 0;
    bool clickCheck = false;

    while (true) {  // running animation in a while loop
        FsPollDevice();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        currTime = FsPassedTime();
        start_time += currTime;
        switch (FsInkey()) {  // made program interactive
            case FSKEY_DOWN:
                fastForward += fastForward >= 1.5f ? 0.0f : 0.5f;
                break;
            case FSKEY_ESC:
                endAnimation = true;
                break;
            case FSKEY_R:
                reverseAll();
                break;
        }

        if (endAnimation) {
            break;
        }

        mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
        switch (mouseEvent) {
            case FSMOUSEEVENT_LBUTTONDOWN:
                clickCheck = true;
                break;
            default:
                break;
        }
        if (true == clickCheck) {
            point += CheckPoint(mx, my);
        }

        display();

        if (tempVar == 16 * fastForward) {
            tempVar = 0;
            update();
        }
        tempVar++;
        clickCheck = false;
        if (start_time >= 1000) {
            endTimer -= 1;
            start_time = 0;
        }

        glColor3ub(255, 255, 255);  // Rendar the values with black
        glRasterPos2i(10, 30);
        YsGlDrawFontBitmap16x24("Your time: ");
        std::stringstream ss;
        ss << endTimer;
        std::string str = ss.str();
        const char* c = str.c_str();
        YsGlDrawFontBitmap16x24(c);

        glRasterPos2i(10, 60);
        YsGlDrawFontBitmap16x24("Your Point: ");
        std::stringstream ss2;
        ss2 << point;
        std::string str2 = ss2.str();
        const char* c2 = str2.c_str();
        YsGlDrawFontBitmap16x24(c2);

        glRasterPos2i(200, 200);
        YsGlDrawFontBitmap8x12("Click the objects!!");
        glRasterPos2i(200, 160);
        YsGlDrawFontBitmap8x12("You can use 'R' key.");

        FsSwapBuffers();  // swappping front and back buffers (double buffering)
        if (endTimer == 0) {
            break;
        }
    }
    return point;
}
/** Shape game end **/

void HuntingHouse::Init() {
}

HuntingHouse::HuntingHouse() {
}

HuntingHouse::HuntingHouse(int init_state) {
    // Initialize the game state
    state = init_state;
    // Initialize map object
    m.Init(0, 0, 1);
    // Initialize floor object
    for (int i = 0; i < 5; ++i) {
        f[i].Init(600 - 600 / 5 * i, 600, 13, i + 1);
    }
    // Initialize ladder object
    l[0].Init(800 - 150 * 1, 0, 60, 600);
    l[1].Init(150 * 1, 1, 60, 600);
    l[2].Init(800 - 150 * 1, 2, 60, 600);
    l[3].Init(150 * 1, 3, 60, 600);

    p_image_left = "player_resize_left.png";    // File name for object's image
    p_image_right = "player_resize_right.png";  // File name for object's image
    mainBgImage = "gamebgimage.png";

    if (p_left_png.Decode(p_image_left.c_str()) == YSOK) {
        p_left_png.Flip();
    }

    if (p_right_png.Decode(p_image_right.c_str()) == YSOK) {
        p_right_png.Flip();
    }

    // Initialize player object
    bossPlayer.Init(800 - 300, 102, 102, 600);
    p.Init(150, 1, 0, p_left_png.wid, p_left_png.hei, 600, 1);

    if (mainBgImageDecoder.Decode(mainBgImage.c_str()) == YSOK) {
        mainBgImageDecoder.Flip();
    }

    pointX = 20;  // The position to show the point in the window
    pointY = 20;  // The position to show the point

    // Initialize the sub-games
    sub_nature.Initialize();
    quiz_nature.initialize_quiz();
    sub_snake.Init();
    sub_airbt.Init();

    // Initialize the icon object of each sub-game in the maze
    Ob_wam.Init(450, f[2].y - 57, 1, 100, 100);
    Ob_nature.Init(250, f[2].y - 57, 1, 100, 100);
    Ob_snake.Init(550, f[1].y - 57, 1, 100, 100);
    Ob_airbt.Init(300, f[1].y - 57, 1, 100, 100);
    Ob_Dinosaur.Init(500, f[3].y - 60, 1, 100, 100);
    Ob_Abd.Init(300, f[3].y - 60, 1, 100, 100);
    Goal.Init(700, f[4].y - 60, 1, 100, 100);

    // Load each png. for the icons
    FsChangeToProgramDir();
    Ob_wam_image = "mole_resize.png";  // File name for object's image
    if (Ob_wam_png.Decode(Ob_wam_image.c_str()) == YSOK) {
        Ob_wam_png.Flip();
    }
    Ob_nature_image = "nature_resize.png";  // File name for object's image
    if (Ob_nature_png.Decode(Ob_nature_image.c_str()) == YSOK) {
        Ob_nature_png.Flip();
    }
    Ob_snake_image = "snake_resize.png";  // File name for object's image
    if (Ob_snake_png.Decode(Ob_snake_image.c_str()) == YSOK) {
        Ob_snake_png.Flip();
    }
    Ob_airbt_image = "airbattle_resize.png";  // File name for object's image
    if (Ob_airbt_png.Decode(Ob_airbt_image.c_str()) == YSOK) {
        Ob_airbt_png.Flip();
    }
    Ob_Dinosaur_image = "dinosaur_resize.png";  // File name for object's image
    if (Ob_Dinosaur_png.Decode(Ob_Dinosaur_image.c_str()) == YSOK) {
        Ob_Dinosaur_png.Flip();
    }
    Goal_image = "goal_resize.png";  // File name for object's image
    if (Goal_png.Decode(Goal_image.c_str()) == YSOK) {
        Goal_png.Flip();
    }

    if (bgWav.LoadWav(bgMusic.c_str()) == YSOK) {
        bgPlayer.Start();
        bgPlayer.PlayBackground(bgWav);
    }
}

HuntingHouse::~HuntingHouse() {
}

int HuntingHouse::RunOneStep(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(255.0, 255.0, 255.0, 1.0);

    glRasterPos2d(0, 599);
    glDrawPixels(mainBgImageDecoder.wid, mainBgImageDecoder.hei, GL_RGBA, GL_UNSIGNED_BYTE, mainBgImageDecoder.rgba);

    FsPollDevice();
    int key = FsInkey();
    if (key == FSKEY_ESC) {
        return 2;
    }

    //________Player_Position_Check_(which floor?/ which ladder?)________//
    p.PositionCheck(f, l);

    //________Player-Obstacle_Collision_Check________//
    if (true == p.ObstacleColisionCheck(Ob_wam) && 1 == Ob_wam.state) {
        state = 1;
    } else if (true == p.ObstacleColisionCheck(Ob_nature) && 1 == Ob_nature.state) {
        state = 2;
    } else if (true == p.ObstacleColisionCheck(Ob_snake) && 1 == Ob_snake.state) {
        state = 3;
    } else if (true == p.ObstacleColisionCheck(Ob_airbt) && 1 == Ob_airbt.state) {
        state = 4;
    } else if (true == p.ObstacleColisionCheck(Ob_Dinosaur) && 1 == Ob_Dinosaur.state) {
        state = 5;
    } else if (true == p.ObstacleColisionCheck(Ob_Abd) && 1 == Ob_Abd.state) {
        state = 6;
    } else if (true == p.ObstacleColisionCheck(Goal) && 1 == Goal.state) {
        state = 7;
    } else {
        state = 0;
    }

    //________Game_state_transition________//
    switch (state) {
        case 0: {                              // case 0: The player doesn't encount any enemy
            p.Move(key, l, bossPlayer.state);  // The player moves
            for (int i = 0; i < 5; ++i)        // Rendar the floors
            {
                f[i].Rendar();
            }
            for (int i = 0; i < 4; ++i)  // Rendar the ladders
            {
                l[i].Rendar();
            }
            if (1 == Ob_wam.state)  // Rendar the icon for the wam game
            {
                Ob_wam.Rendar();
                glRasterPos2d(Ob_wam.x - Ob_wam_png.wid / 2, Ob_wam.y + Ob_wam_png.hei / 2);
                glDrawPixels(Ob_wam_png.wid, Ob_wam_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, Ob_wam_png.rgba);
            }
            if (1 == Ob_nature.state)  // Rendar the icon for the nature game
            {
                Ob_nature.Rendar();
                glRasterPos2d(Ob_nature.x - Ob_nature_png.wid / 2, Ob_nature.y + Ob_nature_png.hei / 2);
                glDrawPixels(Ob_nature_png.wid, Ob_nature_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, Ob_nature_png.rgba);
            }
            if (1 == Ob_snake.state)  // Rendar the icon for the snake game
            {
                Ob_snake.Rendar();
                glRasterPos2d(Ob_snake.x - Ob_snake_png.wid / 2, Ob_snake.y + Ob_snake_png.hei / 2);
                glDrawPixels(Ob_snake_png.wid, Ob_snake_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, Ob_snake_png.rgba);
            }
            if (1 == Ob_airbt.state)  // Rendar the icon for the air battle game
            {
                Ob_airbt.Rendar();
                glRasterPos2d(Ob_airbt.x - Ob_airbt_png.wid / 2, Ob_airbt.y + Ob_airbt_png.hei / 2);
                glDrawPixels(Ob_airbt_png.wid, Ob_airbt_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, Ob_airbt_png.rgba);
            }
            if (1 == Ob_Dinosaur.state)  // Rendar the icon for the dinosaur game
            {
                Ob_Dinosaur.Rendar();
                glRasterPos2d(Ob_Dinosaur.x - Ob_Dinosaur_png.wid / 2, Ob_Dinosaur.y + Ob_Dinosaur_png.hei / 2);
                glDrawPixels(Ob_Dinosaur_png.wid, Ob_Dinosaur_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, Ob_Dinosaur_png.rgba);
            }
            if (1 == Ob_Abd.state)  // Rendar the icon for the goal
            {
                Ob_Abd.Rendar();
                drawBallMaze(Ob_Abd.x, Ob_Abd.y, Ob_Abd.width / 2);
            }
            if (1 == Goal.state)  // Rendar the icon for the goal
            {
                Goal.Rendar();
                glRasterPos2d(Goal.x - Goal_png.wid / 2, Goal.y + Goal_png.hei / 2);
                glDrawPixels(Goal_png.wid, Goal_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, Goal_png.rgba);
            }
            bossPlayer.Rendar();
            p.Rendar();  // Rendar the player
            glRasterPos2d(p.x - p_left_png.wid / 2, p.y + p.height / 2 - 1);
            if (0 == p.direction && p.alive) {
                glDrawPixels(p_left_png.wid, p_left_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, p_left_png.rgba);
            } else if (1 == p.direction && p.alive) {
                glDrawPixels(p_right_png.wid, p_right_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, p_right_png.rgba);
            }
            if (bossPlayer.state == 0) {
                bossPlayer.HitFrom(p.missile);
            }
            p.CheckHitFrom(bossPlayer.missile);
            if (!p.alive) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glRasterPos2i(250, 300);
                YsGlDrawFontBitmap16x20("Game Ended. You Lost!");

                FsSwapBuffers();
                FsSleep(3000);
                return 2;  // Stop Running the Game
            }
            break;
        }
        case 1: {  // case 1: The player encounts the wam icon. The wam game runs.
            bgPlayer.Stop(bgWav);
            p.point += sub_wam.play();
            state = 0;
            Ob_wam.state = 0;
            bgPlayer.PlayBackground(bgWav);
            break;
        }
        case 2: {  // case 2: The player encounts the nature icon. The nature game runs.
            quiz_nature.initialize_quiz();
            sub_nature.Initialize();
            sub_nature.start_time = time(NULL);
            sub_nature.Run();
            state = 0;
            Ob_nature.state = 0;
            box_nature.RunQuizBox();
            p.point += box_nature.score;
            break;
        }
        case 3: {  // case 3: The player encounts the snake icon. The snake game runs.
            bgPlayer.Stop(bgWav);
            double gpoints = sub_snake.Play();
            p.point += gpoints > 0 ? (int)gpoints : 0;
            state = 0;
            Ob_snake.state = 0;
            bgPlayer.PlayBackground(bgWav);
            break;
        }
        case 4: {  // case 4: The player encounts the air battle icon. The air battle game runs.
            bgPlayer.Stop(bgWav);
            p.point += sub_airbt.run();
            state = 0;
            Ob_airbt.state = 0;
            bgPlayer.PlayBackground(bgWav);
            break;
        }
        case 5: {  // case 5: The player encounts the dinosaur icon. The dinosaur game runs.
            bgPlayer.Stop(bgWav);
            sub_dinosaur.nLifes = 100;  // The player HP for the last dinosaur game equals to the point the player got in the other games
            sub_dinosaur.run();
            state = 0;
            Ob_Dinosaur.state = 0;
            p.point += sub_dinosaur.score;
            bgPlayer.PlayBackground(bgWav);
            break;
        }
        case 6: {  // case 6: The player encounts Abds game
            p.point += Abd_game();
            state = 0;
            Ob_Abd.state = 0;
            break;
        }
        case 7: {  // When the player reach the goal, the ending starts.
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glRasterPos2i(300, 300);
            YsGlDrawFontBitmap16x20("Game Ended");

            FsSwapBuffers();
            FsSleep(3000);
            return 2;  // Stop Running the Game
        }
    }
    FsSwapBuffers();
    FsSleep(20);

    return 0;
}
