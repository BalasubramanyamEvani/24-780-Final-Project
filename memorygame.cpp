#define GL_SILENCE_DEPRECATION

#include "memorygame.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <iostream>
#include <string>
#include <vector>

#include "fssimplewindow.h"
#include "ysglfontdata.h"

const double YsPi = 3.1415927;
const double G = 98;

MultiplicationQuiz::MultiplicationQuiz() {}

MultiplicationQuiz::~MultiplicationQuiz() {}

void MultiplicationQuiz::initialize_quiz() {
    for (int i = 0; i < numQuestions; ++i) {
        int n1 = generateRandomNumber();
        int n2 = generateRandomNumber();

        num1.push_back(n1);
        num2.push_back(n2);

        int correct = num1[i] * num2[i];

        correctAnswer.push_back(correct);
    }
}

void MultiplicationQuiz::runQuiz_printed_maths() {
    for (int i = 0; i < numQuestions; ++i) {
        int answer;
        std::string questionMessage = "Question " + std::to_string(i + 1) + ": " +
                                      std::to_string(num1[i]) + " x " + std::to_string(num2[i]) + " = ";
        std::cout << questionMessage;
        std::cin >> answer;

        userAnswer.push_back(answer);

        if (answer == correctAnswer[i]) {
            std::cout << "Correct! Nice job.\n";
            score += 1;
        } else {
            std::cout << "Incorrect. The correct answer is: " << correctAnswer[i] << "\n";
        }
    }
    std::cout << "\nYour maths score: " << score * 40 << " out of " << numQuestions << "\n";
}

void MultiplicationQuiz::runQuiz_printed_demo() {
    // Define the questions and answers
    std::string memory_questions[] = {"How many flower petals are there in the first flower? ",
                                      "How many butterflies are there? ",
                                      "How many times did the lightning strike? "};

    int correct_answers[] = {5, 3, 3};

    // Initialize score
    memory_score = 0;

    // Ask the user the questions and check the answers
    for (int i = 0; i < sizeof(memory_questions) / sizeof(memory_questions[0]); ++i) {
        int user_answer;
        std::cout << memory_questions[i];
        std::cin >> user_answer;

        userAnswer_memory_quiz.push_back(user_answer);
        correctAnswer_memory_quiz.push_back(correct_answers[i]);

        // Check if the user's answer is correct
        if (user_answer == correct_answers[i]) {
            std::cout << "Correct!" << std::endl;
            memory_score += 1;
        } else {
            std::cout << "Incorrect. The correct answer is: " << correct_answers[i] << std::endl;
        }
    }

    // Print the final score
    std::cout << "Your demo quiz score: " << memory_score * 40 << " out of " << sizeof(memory_questions) / sizeof(memory_questions[0]) << std::endl;
}

void MultiplicationQuiz::message_draw(double pos_x, double pos_y, std::string message) {
    glColor3f(0, 0, 0);
    glRasterPos2i(pos_x, pos_y);
    for (int i = 0; i < message.length(); ++i) {
        char c[2] = {message[i], 0};
        YsGlDrawFontBitmap6x7(c);
    }
}

void MultiplicationQuiz::runQuiz_drawn_maths() {
    double pos_x = 60.0, pos_y = 60.0;
    for (int i = 0; i < numQuestions; ++i) {
        std::string questionMessage = "Question " + std::to_string(i + 1) + ": " +
                                      std::to_string(num1[i]) + " x " + std::to_string(num2[i]) + " = " + std::to_string(userAnswer[i]);
        message_draw(pos_x, pos_y, questionMessage);
        if (userAnswer[i] == correctAnswer[i]) {
            std::string CongratsMessage = "Correct! Nice Job.";
            message_draw(pos_x, pos_y + 20, CongratsMessage);
        } else {
            std::string IncorrectMessage = "Incorrect. The correct answer is: " + std::to_string(correctAnswer[i]);
            message_draw(pos_x, pos_y + 20, IncorrectMessage);
        }
        pos_y += 50;
    }
    std::string FinalMessage = "Maths Quiz Complete! Your final score is: " + std::to_string(score) + " out of " + std::to_string(numQuestions);
    message_draw(50, 450, FinalMessage);
}

void MultiplicationQuiz::runQuiz_drawn_demo() {
    double pos_x = 360.0, pos_y = 60.0;

    std::string memory_questions[] = {"How many flower petals are there in the first flower? ",
                                      "How many butterflies are there? ",
                                      "How many times did the lightning strike? "};
    numQuestions_demo = 3;
    for (int i = 0; i < numQuestions_demo; ++i) {
        std::string questionMessage = memory_questions[i];
        message_draw(pos_x, pos_y, questionMessage);
        if (userAnswer_memory_quiz[i] == correctAnswer_memory_quiz[i]) {
            std::string CongratsMessage = "Correct! Nice job.";
            message_draw(pos_x + 150, pos_y + 20, CongratsMessage);
        } else {
            std::string IncorrectMessage = "Incorrect. The correct answer is: " + std::to_string(correctAnswer_memory_quiz[i]);
            message_draw(pos_x + 150, pos_y + 20, IncorrectMessage);
        }
        pos_y += 50;
    }

    std::string FinalMessage = "Memory quiz Complete! Your final score is: " + std::to_string(memory_score) + " out of " + std::to_string(numQuestions_demo);
    message_draw(50, 500, FinalMessage);
}

NatureDemo::NatureDemo(){};

NatureDemo::~NatureDemo(){};

void NatureDemo::DrawWhitePaper(double alpha) {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(255, 255, 255, alpha);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(0, 0);
    glVertex2i(800, 0);
    glVertex2i(800, 600);
    glVertex2i(0, 600);
    glEnd();
}

void NatureDemo::DrawLightning(double x, double y, double a, double b, double c, double d, double e) {
    glColor3f(255, 255, 0);  // yellow for lighting
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x, y);
    glVertex2d(x - a, y);
    glVertex2d(x - a + d, y + b);
    glVertex2d(x - a + d - e, y + b - c);
    glVertex2d(x + d - e, y + b - c);
    glVertex2d(x - e, y - c);
    glEnd();
}

void NatureDemo::Draw_helix(float init_x, float init_y) {
    const float numTurns = 3.0;  // Number of turns in the helix
    float radius_a = 1.0, radius_b = 0.2;
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 0);
    float x, y;
    for (float t = 0; t < numTurns * 2 * YsPi; t += 0.4) {
        x = init_x + radius_a * exp(radius_b * t) * cos(t);
        y = init_y + radius_a * exp(radius_b * t) * sin(t);  // Increase the y-coordinate as you move along the helix
        glVertex2d(x, y);
    }
    glEnd();
}

void NatureDemo::Draw_wind(int num_x, int num_y, float init_x, float init_y) {
    for (int x = 0; x < num_x; x++)
        for (int y = 0; y < num_y; y++)
            Draw_helix(init_x + x * 60, init_y + y * 60);
}

// Draw oval function. By using oval function multiple times, the flower petals, butterfly can be drawn.
void NatureDemo::DrawOval_rainbow(double cx, double cy, double rad1, double rad2, double degree, int r, int g, int b, int r_change, int g_change, int b_change)  // degree stands for rotational degree
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 64; ++i) {
        double ang = YsPi * (double)i / 32.0;
        double s = sin(ang);
        double c = cos(ang);
        double x_new = rad1 * c * cos(degree / 180 * YsPi) - rad2 * s * sin(degree / 180 * YsPi);
        double y_new = rad1 * c * sin(degree / 180 * YsPi) + rad2 * s * cos(degree / 180 * YsPi);
        x_new += cx;
        y_new += cy;
        glColor3f(r, g, b);
        r += r_change;
        g -= g_change;
        b += b_change;
        glVertex2d(x_new, y_new);
    }
    glEnd();
}

void NatureDemo::DrawOval(double cx, double cy, double rad1, double rad2, double degree, double r, double g, double b)  // degree stands for rotational degree
{
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glColor3f(12,122,0);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 64; ++i) {
        double ang = YsPi * (double)i / 32.0;
        double s = sin(ang);
        double c = cos(ang);
        double x = cx + rad1 * c;
        double y = cy + rad2 * s;
        double x_new = rad1 * c * cos(degree / 180 * YsPi) - rad2 * s * sin(degree / 180 * YsPi);
        double y_new = rad1 * c * sin(degree / 180 * YsPi) + rad2 * s * cos(degree / 180 * YsPi);
        x_new += cx;
        y_new += cy;
        glColor3f(r, g, b);
        glVertex2d(x_new, y_new);
    }
    glEnd();
}

// Draw circle function
void NatureDemo::DrawCircle(double cx, double cy, double rad, int r, int g, int b) {
    glColor3f(r, g, b);  // red
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 64; ++i) {
        double ang = YsPi * (double)i / 32.0;
        double s = sin(ang);
        double c = cos(ang);
        double x = cx + rad * c;
        double y = cy + rad * s;
        glVertex2d(x, y);
    }
    glEnd();
}

// Draw raindrops function
void NatureDemo::DrawRain(double cx, double cy, int num_rx, int num_ry, double rain_length, double space)
// num_rx and num_ry are numbers of raindrops in horizontal and vertical directions
// space represents the distance between each raindrop
{
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    for (int i = 0; i < num_rx; ++i) {
        for (int j = 0; j < num_ry; ++j) {
            glVertex2i(cx + i * space, cy + j * space);
            glVertex2i(cx + rain_length / sqrt(2) + i * space, cy - rain_length / sqrt(2) + j * space);
        }
    }
    glEnd();
}

void NatureDemo::DrawAnt(double cx, double cy, double a, double b) {
    DrawOval(cx, cy, 0.67 * a, b, 0, 0.647, 0.165, 0.165);
    DrawOval(cx - 5 / 3 * a, cy, a, b, 0, 0.647, 0.165, 0.165);
    DrawOval(cx + 3 / 2 * a, cy, 1.4 * a, 1.5 * b, 0, 0.647, 0.165, 0.165);
    DrawCircle(cx - 1.6 * a, cy, 0.5 * b, 0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(cx, cy - 0.67 * b);
    glVertex2i(cx + 0.67 * a, cy - 3.67 * b);
    glVertex2i(cx + 0.67 * a, cy - 3.67 * b);
    glVertex2i(cx + 1.8 * a, cy - 3.67 * b);
    glVertex2i(cx, cy + 0.67 * b);
    glVertex2i(cx + 0.67 * a, cy + 3.67 * b);
    glVertex2i(cx + 0.67 * a, cy + 3.67 * b);
    glVertex2i(cx + 1.8 * a, cy + 3.67 * b);
    glEnd();
}

void NatureDemo::DrawButterfly(double cx, double cy, double a, double b, double degree)  // cx and cy are the central points'coordinates; a and b are the length of the middle ovals
{
    // DrawOval
    DrawOval_rainbow(cx - 2.5 * a / sqrt(2), cy - 2.5 * a / sqrt(2), 2.5 * a, 3 * b, 45 + degree, 0, 255, 0, 20, 20, 20);
    DrawOval_rainbow(cx + 2.5 * a / sqrt(2), cy - 2.5 * a / sqrt(2), 2.5 * a, 3 * b, 135 + degree, 0, 255, 0, 20, 20, 20);

    // DrawOval
    DrawOval_rainbow(cx + 1.5 * a / sqrt(2), cy + 1.5 * a / sqrt(2), 1.5 * a, 2 * b, -135 + degree, 0, 0, 255, 40, 40, 40);
    DrawOval_rainbow(cx - 1.5 * a / sqrt(2), cy + 1.5 * a / sqrt(2), 1.5 * a, 2 * b, -45 + degree, 0, 0, 255, 40, 40, 40);

    // Middle red
    DrawOval_rainbow(cx - a, cy, a, b, 0 + degree, 255, 0, 0, 60, 60, 60);
    DrawOval_rainbow(cx + a, cy, a, b, 0 + degree, 255, 0, 0, 60, 60, 60);
}

void NatureDemo::DrawCloud(int x, int y) {
    double R = 60.0;  // R stands for the radius of middle circle
    DrawCircle(x, y, R, 0, 0, 255);
    DrawCircle(x - R, y, 0.5 * R, 0, 0, 255);
    DrawCircle(x + 1.2 * R, y, 0.5 * R, 0, 0, 255);
}

void NatureDemo::DrawSun(double sun_x, double sun_y, double sun_r, double sun_xl, double sun_yl) {
    DrawCircle(sun_x, sun_y, sun_r, 255, 255, 0);
    glColor3f(255, 255, 0);
    for (int m = 0; m < 4; m++) {
        glBegin(GL_LINES);
        glVertex2i(sun_x, sun_y);
        glVertex2i(sun_x + sin(YsPi * 0.5 * m) * sun_xl, sun_y + cos(YsPi * 0.5 * m) * sun_yl);
        glVertex2i(sun_x, sun_y);
        glVertex2i(sun_x + sin(YsPi * 0.5 * m + YsPi * 0.25) * sun_xl, sun_y + cos(YsPi * 0.5 * m + YsPi * 0.25) * sun_yl);
        glEnd();
    }
}

void NatureDemo::Initialize() {
    //  Time-related initialization
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = time(NULL);  // Record the starting time
    start_time = static_cast<double>(time(NULL)) / CLOCKS_PER_SEC;
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void NatureDemo::Run() {
    while (true) {
        FsPollDevice();
        double real_time = time(NULL);
        real_time = ((double)(real_time - start_time)) * speed_scale;
        auto key = FsInkey();
        if (FSKEY_ESC == key) {
            break;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (real_time <= scene_start_time) {
            glRasterPos2i(140, 200);
            YsGlDrawFontBitmap16x20("Please watch the video carefully");
            glRasterPos2i(140, 280);
            YsGlDrawFontBitmap16x20("Then answer questions afterwards");
        }

        if (real_time > scene_start_time) {
            for (int i = 0; i < num_petals; i++) {
                DrawCircle(cx, cy, r_c, 1, 0, 0);  // flower pistil
                DrawOval_rainbow(cx + cos(2 * YsPi / num_petals * i) * (r_c + r_ox), cy + sin(2 * YsPi / num_petals * i) * (r_c + r_ox), r_ox, r_oy, 360 / num_petals * i, 0, 255, 122, 20, 20, 20);
            }

            for (int i = 0; i < num_petals2; i++) {
                DrawCircle(cx2, cy2, r_c, 1, 0, 0);  // flower pistil 2
                DrawOval_rainbow(cx2 + cos(2 * YsPi / num_petals2 * i) * (r_c + r_ox), cy2 + sin(2 * YsPi / num_petals2 * i) * (r_c + r_ox), r_ox, r_oy, 360 / num_petals2 * i, 122, 180, 122, 40, 40, 40);
            }

            glFlush();

            if (cloud_state != 0) {
                DrawCloud(cloud_x, cloud_y);
            }
            // DrawButterfly(butterfly_x, butterfly_y, butterfly_a, butterfly_b,0);
            // for drawing flower1's stem
            glColor3ub(0, 0, 0);
            glBegin(GL_LINES);
            glVertex2i(cx, cy);
            glVertex2i(cx, cy + 200);
            glEnd();

            if (rain_state != 0) {
                if (rain_y > cy + 200 & num_petals < 5) {
                    rain_x = 400;
                    rain_y = 200;
                    num_petals += 1;
                }
                rain_x -= dt * 22 * speed_scale;
                rain_y += dt * 20 * speed_scale;
                DrawRain(rain_x, rain_y, 12, 8, 10, 20);
            }

            if (num_petals == 5) {
                rain_state = 0;
                rain2_state = 1;
            }

            if (rain2_state != 0)  // ask Connor or Charllot why it runs only one time.
            {
                rain2_x += dt * 10 * speed_scale;
                rain2_y += dt * 20.0 * speed_scale;
                // for drawing flower1's stem
                glColor3ub(0, 0, 0);
                glBegin(GL_LINES);
                glVertex2i(cx2, cy2);
                glVertex2i(cx2, cy2 + 200);
                glEnd();
                DrawRain(rain2_x, rain2_y, 12, 8, 10, 20);
                if (rain2_y > cy2 + 200 & num_petals2 < 5) {
                    rain2_x = 400;
                    rain2_y = 200;
                    num_petals2 += 1;
                }
            }

            if (num_petals2 == 5) {
                rain2_state = 0;
            }

            // The ants appear near the ground and moves forward.

            for (int num_ant = 0; num_ant < 5; num_ant++) {
                DrawAnt(ant_x + 50 * num_ant, ant_y - 50 * num_ant, antsize_a, antsize_b);
            }

            if (ant_state != 0) {
                ant_x -= antmove_x * speed_scale;
                if (ant_x < 0) {
                    ant_x = 800;
                }
            }

            // Lightning will appear each 5 seconds after raining is finished.

            if (real_time >= lightning_start_time && (int)real_time % 1 == 0 && real_time <= lightning_end_time) {
                DrawLightning(light_x, light_y, light_a, light_b, light_c, light_d, light_e);
                ant_x += antmove_x * speed_scale;
            }

            else {
                ant_state = 1;
            }

            if (real_time >= lightning_end_time) {
                sun_state = 1;
                rain2_state = 0;
                wind_state = 1;
            }

            if (real_time >= lightning_end_time & (int)real_time % 1 == 0 & real_time < wind_end_time) {
                if (wind_state != 0) {
                    Draw_wind(3, 3, wind_x, wind_y);
                    wind_x += 0.2 * speed_scale;
                }
            }

            if (sun_state != 0) {
                DrawSun(sun_x, sun_y, sun_r, sun_x1, sun_y1);
                cloud_x += 0.1 * speed_scale;
                if (cloud_x >= 800) {
                    cloud_state = 0;
                    wind_state = 0;
                    butterfly_state = 1;
                    wind_state = 0;
                }
            }

            // The butterfly appears after raining.
            if (butterfly_state != 0) {
                butterfly_x += 0.02;
                butterfly_y -= 0.02 * cos(YsPi / 6) * speed_scale;
                DrawButterfly(butterfly_x, butterfly_y, butterfly_a, butterfly_b, 0);
                DrawButterfly(butterfly_x + 80, butterfly_y + 80, butterfly_a, butterfly_b, 0);
                DrawButterfly(butterfly_x + 160, butterfly_y, butterfly_a, butterfly_b, 0);
            }

            if (real_time > scene_end_time - 5.0 & alpha <= 1.0) {
                alpha += 0.003 * speed_scale;
            }
            DrawWhitePaper(alpha);
        }

        if (real_time > scene_end_time) {
            glColor3f(0, 0, 0);
            glRasterPos2i(90, 100);

            for (int i = 0; i < message1.length(); ++i) {
                char c[2] = {message1[i], 0};
                YsGlDrawFontBitmap12x16(c);
            }

            glColor3f(0, 0, 0);
            glRasterPos2i(90, 140);

            for (int i = 0; i < message2.length(); ++i) {
                char c[2] = {message2[i], 0};
                YsGlDrawFontBitmap12x16(c);
            }

            glColor3f(0, 0, 0);
            glRasterPos2i(90, 180);

            for (int i = 0; i < message3.length(); ++i) {
                char c[2] = {message3[i], 0};
                YsGlDrawFontBitmap12x16(c);
            }

            glColor3f(0, 0, 0);
            glRasterPos2i(90, 220);

            for (int i = 0; i < message4.length(); ++i) {
                char c[2] = {message4[i], 0};
                YsGlDrawFontBitmap12x16(c);
            }
        }

        if (real_time > demo_end_time) {
            break;
        }
        FsSwapBuffers();
    }
}

QuizBox::QuizBox() {
}
QuizBox::~QuizBox() {
}
void QuizBox::Initialize() {
}

void QuizBox::DrawBox(double pos_x, double pos_y) {
    int leng = 100;
    glColor3f(0, 0, 255);  // red
    glBegin(GL_QUADS);
    glVertex2d(pos_x, pos_y);
    glVertex2d(pos_x + leng, pos_y);
    glVertex2d(pos_x + leng, pos_y + leng);
    glVertex2d(pos_x, pos_y + leng);
    glEnd();
}

void QuizBox::DrawBox_colorful(int color, double pos_x, double pos_y) {
    int leng = 100;
    if (color == 1)  // correct answer turns green
    {
        glColor3f(0, 255, 0);
    }

    if (color == 2) {
        glColor3f(255, 0, 0);  // incorrect answer turns red
    }
    glBegin(GL_QUADS);
    glVertex2d(pos_x, pos_y);
    glVertex2d(pos_x + leng, pos_y);
    glVertex2d(pos_x + leng, pos_y + leng);
    glVertex2d(pos_x, pos_y + leng);
    glEnd();
}

void QuizBox::DrawMessage(double pos_x, double pos_y, std::string message) {
    glColor3f(0, 0, 0);
    glRasterPos2i(pos_x, pos_y);
    for (int i = 0; i < message.length(); ++i) {
        char c[2] = {message[i], 0};
        YsGlDrawFontBitmap8x12(c);
    }
}

void QuizBox::DrawMessageBig(double pos_x, double pos_y, std::string message) {
    glColor3f(0, 0, 0);
    glRasterPos2i(pos_x, pos_y);
    for (int i = 0; i < message.length(); ++i) {
        char c[2] = {message[i], 0};
        YsGlDrawFontBitmap12x16(c);
    }
}

void QuizBox::DrawMessageWhite(double pos_x, double pos_y, std::string message) {
    glColor3f(140, 180, 255);
    glRasterPos2i(pos_x, pos_y);
    for (int i = 0; i < message.length(); ++i) {
        char c[2] = {message[i], 0};
        YsGlDrawFontBitmap8x12(c);
    }
}

bool QuizBox::PositionChecker_1(double mx, double my) {
    if (mx >= pos_x && mx <= pos_x + leng && my >= pos_y && my <= pos_y + leng) {
        return true;
    }
    return false;
}

bool QuizBox::PositionChecker_3(double mx, double my) {
    if (mx >= pos_x + 280 && mx <= pos_x + leng + 280 && my >= pos_y && my <= pos_y + leng) {
        return true;
    }
    return false;
}

bool QuizBox::PositionChecker_5(double mx, double my) {
    if (mx >= pos_x + 280 * 2 && mx <= pos_x + leng + 280 * 2 && my >= pos_y && my <= pos_y + leng) {
        return true;
    }
    return false;
}

void QuizBox::AnswerChecker_1(double mx, double my) {
    if (PositionChecker_5(mx, my) == true) {
        DrawBox_colorful(2, pos_x + 560, pos_y);
    }
    if (PositionChecker_1(mx, my) == true) {
        DrawBox_colorful(1, pos_x, pos_y);
        score++;
    }

    if (PositionChecker_3(mx, my) == true) {
        DrawBox_colorful(2, pos_x + 280, pos_y);
    }
}

void QuizBox::AnswerChecker_3(double mx, double my) {
    if (PositionChecker_5(mx, my) == true) {
        DrawBox_colorful(2, pos_x + 560, pos_y);
    }
    if (PositionChecker_1(mx, my) == true) {
        DrawBox_colorful(2, pos_x, pos_y);
    }
    if (PositionChecker_3(mx, my) == true) {
        DrawBox_colorful(1, pos_x + 280, pos_y);
        score++;
    }
}

void QuizBox::AnswerChecker_5(double mx, double my) {
    if (PositionChecker_5(mx, my) == true) {
        DrawBox_colorful(1, pos_x + 560, pos_y);
        score++;
    }
    if (PositionChecker_1(mx, my) == true) {
        DrawBox_colorful(2, pos_x, pos_y);
    }

    if (PositionChecker_3(mx, my) == true) {
        DrawBox_colorful(2, pos_x + 280, pos_y);
    }
}

int QuizBox::RunQuizBox() {
    int question_num = 0;
    int answer_num = 0;
    int question_counter = 0;
    std::string memory_questions[] = {
        "How many flower petals are there in the left flower? ",
        "How many butterflies are there? ",
        "How many times did the lightning strike? ",
        "How many bugs are there?",
        "What is the angle in radians between each flower?",
    };
    std::string memory_answers[] = {"A : 1 B: 3 C: 5",            // Question 1: 5
                                    "A : 1 B: 3 C: 5",            // Question 2: 3
                                    "A : 6 B: 3 C: 5",            // Question 3: 3
                                    "A : 1 B: 3 C: 5",            // Question 4: 5
                                    "A: 1.256 B: 3.14 C: 6.28"};  // Question 5: 1
    std::string Choices[] = {"A", "B", "C"};

    std::string memory_answers_a[] = {"A:1 ", "A: 1", "A: 6", "A: 1", "A: 1.256"};
    std::string memory_answers_b[] = {"B:3", "B:3", "B:1", "B: 3", "B: 3.14"};
    std::string memory_answers_c[] = {"C: 5", "C: 5", "C: 5", "C: 5", "C: 6.28"};
    for (;;) {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        std::string score_info = "The score is " + std::to_string(score * 40);
        auto key = FsInkey();
        int lb, mb, rb, mx, my;
        int event = FsGetMouseEvent(lb, mb, rb, mx, my);
        if (FSKEY_ESC == key) {
            return score;
        }

        DrawMessageBig(Question_x, Question_y + 300, memory_answers[question_num]);
        DrawMessageBig(Question_x, Question_y + 400, score_info);

        if (question_counter == 0) {
            DrawMessageBig(Question_x - 250, Question_y, memory_questions[question_num]);
        }
        if (question_counter == 1) {
            DrawMessageBig(Question_x - 150, Question_y, memory_questions[question_num]);
        }
        if (question_counter == 2) {
            DrawMessageBig(Question_x - 140, Question_y, memory_questions[question_num]);
        }
        if (question_counter == 3) {
            DrawMessageBig(Question_x - 100, Question_y, memory_questions[question_num]);
        }
        if (question_counter == 4) {
            DrawMessageBig(Question_x - 245, Question_y, memory_questions[question_num]);
        }

        for (int i = 0; i < 3; i++) {
            DrawBox(pos_x + i * 280, pos_y);
        }

        if (event == FSMOUSEEVENT_LBUTTONDOWN && (PositionChecker_1(mx, my) == true || PositionChecker_3(mx, my) == true || PositionChecker_5(mx, my) == true)) {
            if (question_num == 0) {
                AnswerChecker_5(mx, my);
            }
            if (question_num == 1) {
                AnswerChecker_3(mx, my);
            }

            if (question_num == 2) {
                AnswerChecker_3(mx, my);
            }

            if (question_num == 3) {
                AnswerChecker_5(mx, my);
            }
            if (question_num == 4) {
                AnswerChecker_1(mx, my);
                break;
            }
            question_num++;
            answer_num++;
            question_counter++;
        }
        DrawMessageWhite(pos_x + 20, pos_y + 20, memory_answers_a[question_num]);
        DrawMessageWhite(pos_x + 300, pos_y + 20, memory_answers_b[question_num]);
        DrawMessageWhite(pos_x + 580, pos_y + 20, memory_answers_c[question_num]);

        glFlush();
        FsSwapBuffers();
        FsSleep(20);
    }

    return score;
}
