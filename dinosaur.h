#ifndef DINOSAUR_GAME_H
#define DINOSAUR_GAME_H

class DinosaurGame {
   public:
    void run();  // Starts the game loop
    static const int nObs = 5;
    int pstate = 0;
    int nLifes = 100;
    double ball_x = 50;
    double ball_y = 95;
    double ball_vx = 0;
    double ball_vy = 0;
    double angle = 90 * (Y_PI) / 180;
    double starting_x = 50, starting_y = 95;
    int score = 0;
    double obst_x[nObs], obst_y[nObs], obst_h[nObs],
        obst_w[nObs], obst_state[nObs], obst_v[nObs];

   protected:
    const double Y_PI = 3.1415926;
    const double g = 9.8;
    const int MIN_DISTANCE_BETWEEN_OBSTACLES = 150;
    const int MAX_DISTANCE_BETWEEN_OBSTACLES = 400;
    void DrawHUD(int score, int nLifes);
    void DrawScene();
    void DrawEnd(int score);
    void DrawObs(double x, double y, double w, double h, int obst_state);
    void DrawDinosaur(double x, double y, int nLifes);
    bool CheckCollision(double x, double y, double tx, double ty, double tw, double th);
    bool CheckPassing(double x, double y, double tx, double ty, double tw, double th);
    void generateObs(double (&obst_x)[nObs], double (&obst_y)[nObs], double (&obst_w)[nObs],
                     double (&obst_h)[nObs], double (&obst_state)[nObs], double (&obst_v)[nObs], int score);
};

#endif
