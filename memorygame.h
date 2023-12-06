#ifndef Nature_Game_hpp
#define Nature_Game_hpp

#include <stdio.h>

#include <string>
#include <vector>

class MultiplicationQuiz {
   public:
    MultiplicationQuiz();
    ~MultiplicationQuiz();

    int numQuestions;
    int numQuestions_demo;
    int score;
    int memory_score;

    // for maths quiz part
    std::vector<int> num1;
    std::vector<int> num2;
    std::vector<int> userAnswer;
    std::vector<int> correctAnswer;

    // for demo memory quiz part
    std::vector<int> userAnswer_memory_quiz;
    std::vector<int> correctAnswer_memory_quiz;

    std::string message1;
    std::string message2;

    int generateRandomNumber() {
        return rand() % 10 + 1;  // Generate a random number between 1 and 10
    }
    MultiplicationQuiz(int num) : numQuestions(num), score(0) {}

    void initialize_quiz();

    void runQuiz_printed_maths();
    void message_draw(double pos_x, double pos_y, std::string message);
    void runQuiz_drawn_maths();  // will be adjusted later, so that user input will be shown on the window too.
    void runQuiz_printed_demo();
    void runQuiz_drawn_demo();
};

class NatureDemo : public MultiplicationQuiz {
   protected:
    // Part 1 set up: Defining various parameters for rendering and drawing.
    // Defining dimensions

   public:
    NatureDemo();
    ~NatureDemo();

    void DrawWhitePaper(double alpha);
    void DrawLightning(double x, double y, double a, double b, double c, double d, double e);
    void Draw_helix(float init_x, float init_y);
    void Draw_wind(int num_x, int num_y, float init_x, float init_y);
    void DrawOval_rainbow(double cx, double cy, double rad1, double rad2, double degree, int r, int g, int b, int r_change, int g_change, int b_change);
    void DrawOval(double cx, double cy, double rad1, double rad2, double degree, double r, double g, double b);
    void DrawCircle(double cx, double cy, double rad, int r, int g, int b);
    void DrawRain(double cx, double cy, int num_rx, int num_ry, double rain_length, double space);
    void DrawAnt(double cx, double cy, double a, double b);
    void DrawButterfly(double cx, double cy, double a, double b, double degree);
    void DrawCloud(int x, int y);
    void DrawSun(double sun_x, double sun_y, double sun_r, double sun_xl, double sun_yl);
    void Initialize();
    void Run();

    double cx = 200.0, cy = 450.0, r_c = 10;  // circle for flower1's pistil
    double cx2 = 600.0, cy2 = 450.0;          // circle for flower2's pistil
    double light_x = 500.0, light_y = 300.0;  // lighting position
    double light_a = 40, light_b = 3 * light_a, light_c = 2 * light_a, light_d = 1.5 * light_a, light_e = 0.4 * light_a;
    double r_ox = 40, r_oy = 10;
    int num_petals = 0;
    int num_petals2 = 0;
    double ant_x = 120, ant_y = 530, antsize_a = 20, antsize_b = 10;
    double butterfly_x = 300, butterfly_y = 300, butterfly_a = 10, butterfly_b = 5;
    double sun_x = 100.0, sun_y = 100.0, sun_r = 60.0, sun_x1 = 80.0, sun_y1 = 80.0;
    double cloud_x = 500.0, cloud_y = 200.0;
    double wind_x = 300.0, wind_y = 200.0, wind_end_time = 100.0;
    int flower_state = 0, flower2_state = 0, butterfly_state = 0, sun_state = 0, wind_state = 0;
    int cloud_state = 1;

    // Time interval
    double dt = 0.05;
    int rain_state = 1;
    double rain_x = 400, rain_y = 200;
    int rain2_state = 0;
    double rain2_x = 200, rain2_y = 200;
    double antmove_x = 0.3;
    int ant_state = 1;
    double start_time;
    double lightning_start_time = 50.0, lightning_end_time = 60.0, scene_start_time = 5.0, scene_end_time = 125.0;
    double demo_end_time = 135.0;
    double alpha = 0;

    double speed_scale = 5;

    std::string message1 = "How many flower petals are there in the first flower?";
    std::string message2 = "How many butterflies are there?";
    std::string message3 = "How many times did the lightning strike?";

    std::string message4 = "There are also some other questions, please enjoy~";
};

class QuizBox {
   public:
    int pos_x = 30;
    int pos_y = 200;
    int score = 0;

    int Question_x = 330;
    int Question_y = 150;
    double leng = 100;

    QuizBox();
    ~QuizBox();
    void Initialize();

    void DrawBox(double pos_x, double pos_y);
    void DrawBox_colorful(int color, double pos_x, double pos_y);
    void DrawMessage(double pos_x, double pos_y, std::string message);
    void DrawMessageBig(double pos_x, double pos_y, std::string message);
    void DrawMessageWhite(double pos_x, double pos_y, std::string message);

    bool PositionChecker_1(double mx, double my);
    bool PositionChecker_3(double mx, double my);
    bool PositionChecker_5(double mx, double my);

    void AnswerChecker_1(double mx, double my);
    void AnswerChecker_3(double mx, double my);
    void AnswerChecker_5(double mx, double my);

    int RunQuizBox();
};

#endif /* Nature_Game_hpp */
