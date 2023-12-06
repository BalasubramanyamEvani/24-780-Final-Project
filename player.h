#ifndef PLAYER_H_IS_INCLUDED
#define PLAYER_H_IS_INCLUDED

#include "beammissile.h"
#include "floor.h"
#include "ladder.h"
#include "maze.h"
#include "obstacle.h"

class Player : public Obstacle {
   public:
    int windowHeight, floorHeight, floor, yFloor;
    int climb;
    int CurrentFloor[5];   //: which floor the player is on
    int CurrentLadder[4];  //: which ladder the player is on
    int point;
    int direction;  // 0:left, 1:right
    BeamMissile missile;
    bool alive = true;

    Player();
    ~Player();
    void Init(int init_x, int init_floor, int init_state, int init_width, int init_height, int init_windowHeight, int climb);  // void Player::Init(int init_x, int init_floor, int init_state, int init_width, int init_height, int init_windowHeight)
    void Rendar();
    void RendarPoint(int x, int y);
    bool ObstacleColisionCheck(Obstacle obstacle);
    void PositionCheck(Floor f[], Ladder l[]);
    void Move(int key, Ladder l[], int bossState);
    void ShootMissile(void);
    void CheckHitFrom(BeamMissile &incoming);
};

#endif
