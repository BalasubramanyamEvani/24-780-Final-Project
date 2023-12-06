#define GL_SILENCE_DEPRECATION

#include "menu.h"

#include <iostream>
#include <string>

#include "fssimplewindow.h"
#include "ysglfontdata.h"

GameMenu::GameMenu() {
    if (png.Decode(logoPng.c_str()) == YSOK) {
        png.Flip();
    }
}

GameMenu::~GameMenu() {
}

int GameMenu::RunOneStep(void) {
    FsPollDevice();
    auto key = FsInkey();
    if (FSKEY_ESC == key) {
        return 0;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRasterPos2i(0, 599);
    glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

    glColor3ub(255, 0, 0);
    glRasterPos2i(100, 100);
    YsGlDrawFontBitmap16x24("Help the warrior snail reach its goal!");

    glRasterPos2i(200, 500);
    YsGlDrawFontBitmap16x24("Press ESC to exit anytime");

    FsSwapBuffers();
    FsSleep(20);
    return 1;
}
