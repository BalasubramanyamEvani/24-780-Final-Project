#define GL_SILENCE_DEPRECATION

#include "wam.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "yssimplesound.h"

// Play the game
int WamGameScene::play() {
    YsSoundPlayer player;
    YsSoundPlayer::SoundData wav;
    // Initialize points
    points = 0;
    // Start playing the background music

    FsChangeToProgramDir();
    std::string toPlay = "gamebackgroundmusic.wav";
    if (wav.LoadWav(toPlay.c_str()) != YSOK) {
        // if unable to load background music return control to main
        // with points
        return points;
    }
    // Starts player
    player.Start();
    player.PlayBackground(wav);
    // Clear Game Objects
    gameObjects.clear();
    int numEvilMolesAdded = 0;
    // Add game objects: good and evil moles
    for (int i = 0; i < numGoodMoles + numEvilMoles; ++i) {
        if (i % 2 == 0 && numEvilMolesAdded < numEvilMoles) {
            // push back evil moles
            gameObjects.push_back(std::make_unique<WamEvilMole>(0, 0));
            numEvilMolesAdded += 1;
        } else {
            // push back good moles
            gameObjects.push_back(std::make_unique<WamGoodMole>(0, 0));
        }
    }
    for (auto& obj : gameObjects) {
        if (!obj->Initialize()) {
            return points;
        }
    }
    // Initialize the game objects positions
    Initialize();
    // Variables to keep track of timer and mouse events
    auto curr = 0;
    auto currRandTime = 600 + (rand() % 400);
    auto currtimer = 0;
    unsigned long long passedTime = 0;
    int lb, mb, rb, mx, my;
    int mouseEvent;
    bool checkHit = false;
    while (FsInkey() != FSKEY_ESC) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(15.0f / 255.0f, 255.0f / 255.0f, 80.0f / 255.0f, 1.0f);
        FsPollDevice();
        passedTime = FsPassedTime();
        curr += passedTime;
        currtimer += passedTime;
        if (currtimer - 1000 >= 0) {
            timer -= 1;
            currtimer = 0;
        }
        // If game timer exhausted then return control to main
        // with points earned
        if (timer == 0) {
            break;
        }
        // Capture Mouse Events
        mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
        switch (mouseEvent) {
            case FSMOUSEEVENT_LBUTTONDOWN:
                checkHit = true;
                break;
            default:
                break;
        }
        // Render Background
        RenderBackground();
        // Render game objects
        for (auto& object : gameObjects) {
            object->Draw();
        }
        // Check if any gameobject was hit
        if (checkHit) {
            for (auto& object : gameObjects) {
                points += object->Hit(mx, my);
            }
        }
        RenderInfo();
        // Check if need to re initialize based on random time event
        if (curr - currRandTime > 0) {
            Initialize();
            curr = 0;
            currRandTime = 600 + (rand() % 400);
        }
        // Swap buffers
        FsSwapBuffers();
        // Sleep to save cpu cycles
        FsSleep(20);
        checkHit = false;
    }
    return points;
}

// Render the background of the game scene
void WamGameScene::RenderBackground() {
    int winWid, winHei;
    FsGetWindowSize(winWid, winHei);
    glRasterPos2d(0.0, (double)(winHei - 1));
}

// Render the game information like the title, timer, and points
void WamGameScene::RenderInfo() {
    int winWid, winHei;
    FsGetWindowSize(winWid, winHei);

    // Set the color and position to draw the game title
    glColor3ub(0, 0, 0);
    glRasterPos2i(winWid / 2 - 180, 80);
    YsGlDrawFontBitmap32x48(title.c_str());

    // Set the color and position to draw the timer title
    glColor3ub(0, 0, 0);
    glRasterPos2i(80, winHei - 30);
    YsGlDrawFontBitmap16x24(timerTitle.c_str());

    // Set the color and position to draw the timer value
    glColor3ub(255, 0, 0);
    glRasterPos2i(200, winHei - 30);
    YsGlDrawFontBitmap16x24(std::to_string(timer).c_str());

    // Draw coins as ellipses to represent points
    drawCoinEllipse(winWid - 130, winHei - 55, 30, 40, 64);
    drawCoinEllipse(winWid - 120, winHei - 55, 30, 40, 64);

    // Set the color and position to draw the points value
    glColor3ub(0, 0, 0);
    glRasterPos2i(winWid - 250, winHei - 30);
    YsGlDrawFontBitmap16x24(std::to_string(points).c_str());
    YsGlDrawFontBitmap16x24(" x");
}

// Draws ellipses to represent a coin
void WamGameScene::drawCoinEllipse(int cx, int cy, int rx, int ry, int num_segments) {
    // Draw black boundary of the coin
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0.0, 0.0, 0.0);
    glVertex2d(cx, cy);

    for (int i = 0; i <= num_segments; i++) {
        double theta = (2.0 * PI * i) / num_segments;
        double x = rx * std::cos(theta);
        double y = ry * std::sin(theta);
        glVertex2d(x + cx, y + cy);
    }
    glEnd();

    // Draw inner gold part of the coin
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1.0, 0.84, 0);
    glVertex2d(cx, cy);

    for (int i = 0; i <= num_segments; i++) {
        double theta = (2.0 * PI * i) / num_segments;
        double x = (rx - 5) * std::cos(theta);
        double y = (ry - 5) * std::sin(theta);
        glVertex2d(x + cx, y + cy);
    }
    glEnd();
}

// Initialize the game scene with shuffled positions for game objects
void WamGameScene::Initialize() {
    std::random_device rd;  // Random device to provide seed for the generator
    std::mt19937 g(rd());

    // Shuffle x and y values to randomize positions
    std::shuffle(x_values.begin(), x_values.end(), g);
    std::shuffle(y_values.begin(), y_values.end(), g);

    // Prepare a vector to store pairs of x and y coordinates
    std::vector<std::pair<int, int>> pairs;
    // Create all possible pairs of x and y values
    for (auto x : x_values) {
        for (auto y : y_values) {
            pairs.push_back(std::make_pair(x, y));
        }
    }
    // Assign these random positions to each game object
    auto pairIterator = pairs.begin();
    for (auto& gameObject : gameObjects) {
        if (pairIterator != pairs.end()) {
            gameObject->UpdatePos(pairIterator->first, pairIterator->second);
            ++pairIterator;
        }
    }
}

// Constructor for a "Good Mole" object
WamGoodMole::WamGoodMole(int x, int y) {
    this->x = x;
    this->y = y;
    image = "goodmole.png";
    hitPoints = -5;
    prevhit = false;
}

// Constructor for an "Evil Mole" object
WamEvilMole::WamEvilMole(int x, int y) {
    this->x = x;
    this->y = y;
    image = "evilmole.png";
    hitPoints = 5;
    prevhit = false;
}

// Initialize the game object by loading its PNG image
bool WamGameObject::Initialize() {
    // successfully loaded png
    if (png.Decode(image.c_str()) == YSOK) {
        png.Flip();
        return true;
    }
    // failed to load png
    return false;
}

// The hit logic of a gameo bject
int WamGameObject::Hit(double mouseX, double mouseY) {
    // if previousy hit then silently return
    if (prevhit) {
        return 0;
    }
    // if mouse click happens in the vicinity of the image then its a hit
    if ((mouseX >= x && mouseX <= (x + png.wid)) && (mouseY <= y && mouseY >= (y - png.hei))) {
        prevhit = true;
        playHitMusic();
        return hitPoints;
    }
    // if mouse click not on this object
    return 0;
}

// Function to play hit sound effect
void WamGameObject::playHitMusic() {
    // Load the WAV file for the hit sound
    if (wav.LoadWav(hitMusic.c_str()) == YSOK) {
        // If loading is successful, start the sound player
        player.Start();
        // Play the loaded sound effect once
        player.PlayOneShot(wav);
    }
}

// Function to draw the game object
void WamGameObject::Draw() {
    // Set the raster position to the object's current coordinates
    glRasterPos2d(x, y);
    // Draw the object's image as pixels
    glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
}

// Function to update the position of the game object
void WamGameObject::UpdatePos(int x, int y) {
    // Update the object's x and y coordinates
    this->x = x;
    this->y = y;

    // Reset the 'prevhit' flag to false as the position is updated
    this->prevhit = false;
}
