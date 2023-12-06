#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

#include "fssimplewindow.h"
#include "huntinghouse.h"
#include "maze.h"
#include "menu.h"
#include "ysglfontdata.h"

int main(void) {
    FsChangeToProgramDir();
    FsOpenWindow(0, 0, 800, 600, 1);

    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));

    // GameMenu menu
    GameMenu menu;
    int ret = 1;
    unsigned long currTime = 0;
    while (ret == 1 && currTime <= 7000) {
        ret = menu.RunOneStep();
        currTime += FsPassedTime();
    }
    // ESC selected exit
    if (ret == 0) {
        return 0;
    }
    HuntingHouse game(0);
    int state = 0;

    game.Init();
    while (2 != state) {
        state = game.RunOneStep();
    }
    return 0;
}
