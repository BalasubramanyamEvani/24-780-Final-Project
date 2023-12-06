#ifndef HUNTINGHOUSE_H_IS_INCLUDED
#define HUNTINGHOUSE_H_IS_INCLUDED

#include <string>

#include "air_battle.h"
#include "baseobject.h"
#include "bossplayer.h"
#include "dinosaur.h"
#include "floor.h"
#include "ladder.h"
#include "maze.h"
#include "memorygame.h"
#include "obstacle.h"
#include "player.h"
#include "snakegame.h"
#include "wam.h"
#include "yssimplesound.h"

class HuntingHouse {
   public:
    int state;
    void Init();
    std::string bgMusic = "mainbgmusic.wav";
    YsSoundPlayer bgPlayer;
    YsSoundPlayer::SoundData bgWav;

    Maze m;
    Floor f[5];
    Ladder l[4];

    Player p;
    BossPlayer bossPlayer;
    std::string p_image_left, p_image_right, mainBgImage;
    YsRawPngDecoder p_left_png, p_right_png, mainBgImageDecoder;
    int pointX, pointY;

    Obstacle Ob_wam, Ob_nature, Ob_snake, Ob_airbt, Ob_Dinosaur, Ob_Abd;
    std::string Ob_wam_image, Ob_nature_image, Ob_snake_image, Ob_airbt_image, Ob_Dinosaur_image;  // Images to rendar the obstacles on the maze (These should be in the 'Obstacle' Object, but I cannot put them in the class..There was an error.)(Nov.25th, Yuhei)
    YsRawPngDecoder Ob_wam_png, Ob_nature_png, Ob_snake_png, Ob_airbt_png, Ob_Dinosaur_png;        // PNG decoder to rendar the obstacles on the maze (These should be in the 'Obstacle' Object, but I cannot put them in the class..There was an error.)(Nov.25th, Yuhei)

    Obstacle Goal;
    std::string Goal_image;
    YsRawPngDecoder Goal_png;

    // Bala_Game
    WamGameScene sub_wam;

    // Ziyi_Game
    MultiplicationQuiz quiz_nature;
    NatureDemo sub_nature;
    QuizBox box_nature;

    // Jierui_Game
    SnakeGame sub_snake;

    // Yumeng_Game
    AirBattleGame sub_airbt;

    // Alex_Game
    DinosaurGame sub_dinosaur;

    HuntingHouse();
    HuntingHouse(int init_state);
    ~HuntingHouse();

    int RunOneStep(void);  // This function runs the game
};

#endif
