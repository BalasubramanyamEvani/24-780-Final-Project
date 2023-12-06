#ifndef missile_hpp
#define missile_hpp

class BeamMissile {
   public:
    int x, y;
    int state = 0;
    int v = 4;
    void Shoot(int sx, int sy, bool reverse);
    void Disappear(void);

    void Move(void);
    void Draw(void);
};

#endif /* missile_hpp */
