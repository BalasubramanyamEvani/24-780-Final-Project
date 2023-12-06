#ifndef bossplayer_h
#define bossplayer_h

#include "beammissile.h"
#include "obstacle.h"
#include "yspng.h"

class BossPlayer : public Obstacle {
   public:
    int windowHeight, floorHeight, floor, yFloor;
    int CurrentFloor;  //: which floor the player is on
    int point;
    int direction;  // 0:left, 1:right
    BeamMissile missile;

    BossPlayer();
    ~BossPlayer();
    void Init(int init_x, int init_width, int init_height, int init_windowHeight);
    void Rendar();
    void RendarPoint(int x, int y);
    void ShootMissile(void);
    void HitFrom(BeamMissile &incomingMissile);
};

#endif /* bossplayer_h */
