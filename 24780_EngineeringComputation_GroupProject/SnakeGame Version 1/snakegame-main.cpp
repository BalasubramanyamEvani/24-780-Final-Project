#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include "ysglfontdata.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "snakegame.h"
using namespace std;
const double pi = 3.1415927;
int main(void)
{
	YsSoundPlayer player;
	YsSoundPlayer::SoundData bgm;
	string fileName = "bgm.wav";
	player.PlayBackground(bgm);
	if (YSOK != bgm.LoadWav(fileName.c_str()))
	{
		std::cout << "Cannot load wave file." << std::endl;
		return 1;
	}
	player.Start();
	player.PlayBackground(bgm);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	srand(time(NULL));
	FsOpenWindow(16, 16, 800, 600, 0);

	time_t lastHitTime1 = 0;
	time_t lastHitTime3 = 0;
	const double gravity = 98.1;
	const int nFood = 200;  // Number of food generated each time
	double score = 0;   // Count the score of the game

	Snake snake;
	Food foods[nFood];
	Bar bar1, bar2;
	Missile missile1, missile3;
	Cannon cannon1, cannon2;
	CannonBall ball1, ball2;
	SnakeGame game;

	bar1.x = 400;
	bar1.y = 100;
	bar1.w = 50;
	bar1.h = 20;
	bar1.state = 1;
	bar2.x = 750;
	bar2.y = 200;
	bar2.w = 50;
	bar2.h = 20;
	bar2.state = 1;
	int direction1 = 1, direction2 = -1;

	cannon1.cannonAngle = 45 * pi / 180;
	cannon2.cannonAngle = 45 * pi / 180;
	ball1.vel = 200;
	ball2.vel = 350;
	ball1.rad = 3;
	ball2.rad = 3;
	ball1.state = 0;
	ball2.state = 0;
	double dt = 0.05;
	int balls = 0;   // number of cannonball shoot

	double vball1_x, vball1_y;   // ball velocity on horizontal axis and vertical axis
	double vball2_x, vball2_y;
	ball1.cx = 450 + 25 * cos(cannon1.cannonAngle);
	ball1.cy = 550 - 25 * sin(cannon1.cannonAngle);
	ball2.cx = 740 - 25 * cos(cannon2.cannonAngle);
	ball2.cy = 550 - 25 * sin(cannon2.cannonAngle);

	missile1.state = 1;
	missile3.state = 1;
	missile1.y = 220;
	missile1.x = 105;
	missile3.y = 220;
	missile3.x = 305;
	int terminate = 0;

	time_t start_time = time(NULL);
	bool hitWall = false;
	bool hitBoundary = false;
	time_t hitWallTime;
	time_t hitBoundaryTime;
	time_t currentTime;

	for (int i = 0; i < nFood; ++i)
	{
		foods[i].InitializeFood();
		foods[i].state = 1;
	}

	while (0 == terminate)
	{
		FsPollDevice();
		player.KeepPlaying();
		int key = FsInkey();

		if (key == FSKEY_ESC)
		{
			terminate = 1;
			printf("Gameover! A total score is %f.", score);
			break;
		}
		snake.HandleInput(key);
		snake.MoveSnake(snake.snakeDirection[0]);


		if (snake.snakeX[0] <= 15 || snake.snakeX[0] >= 785 || snake.snakeY[0] <= 15 || snake.snakeY[0] >= 585)
		{
			terminate = 1;   // The game will be over if the snake touches the boundary
			printf("Gameover! The total score is %.1f.", score);
			string scoreString = "Total Score: " + to_string(score);
			const char* scoreStr = scoreString.c_str();
			glColor3ub(0, 0, 0);
			glRasterPos2i(360, 300);
			YsGlDrawFontBitmap12x16("Game over!");
			glRasterPos2i(300, 340);
			YsGlDrawFontBitmap12x16(scoreStr);
			player.Stop(bgm);
		}

		// If snake eats the food, the length of the snake will increase 1 unit, the current food is eliminated, and new food is generated
		for (int i = 0; i < nFood; ++i)
		{
			if (foods[i].state == 1 && foods[i].CheckHitFood(snake.snakeX[0], snake.snakeY[0], foods[i].x, foods[i].y, snake.snakeWidth, snake.snakeHeight, foods[i].radius))
			{
				switch (foods[i].type) {
				case 1:
					snake.snakeLength += 0.5;
					score += 0.5;
					break;
				case 2:
					snake.snakeLength += 1;
					score += 1;
					break;
				case 3:
					snake.snakeLength += 1.5;
					score += 1.5;
					break;
				case 4:
					snake.snakeLength += 2;
					score += 2;
					break;
				}
				foods[i].state = 0;
				foods[i].x = rand() % 750 + 25;
				foods[i].y = rand() % 550 + 25;
				foods[i].state = 1;
			}
		}

		if (bar1.x >= 730)
		{
			direction1 = -1;
		}
		else if (bar1.x <= 400)
		{
			direction1 = 1;
		}
		bar1.x += direction1 * 8;

		if (bar2.x >= 730)
		{
			direction2 = -1;
		}
		else if (bar2.x <= 400)
		{
			direction2 = 1;
		}
		bar2.x += direction2 * 8;

		if (0 == ball1.state)
		{
			ball1.state = 1;
			vball1_x = ball1.vel * cos(cannon1.cannonAngle);
			vball1_y = ball1.vel * sin(cannon1.cannonAngle);
		}
		if (ball1.state != 0)   // Apply Euler¡¯s method to update ball position
		{
			ball1.cx += vball1_x * dt;
			ball1.cy -= vball1_y * dt;
			vball1_y -= gravity * dt;

			if (ball1.cx > 800 || ball1.cy <= 300)
			{
				ball1.state = 0;
				balls++;
				ball1.cx = 450 + 25 * cos(cannon1.cannonAngle);
				ball1.cy = 550 - 25 * sin(cannon1.cannonAngle);
			}
		}
		if (0 == ball2.state)
		{
			ball2.state = 1;
			vball2_x = ball2.vel * cos(cannon2.cannonAngle);
			vball2_y = ball2.vel * sin(cannon2.cannonAngle);
		}
		if (ball2.state != 0)   // Apply Euler¡¯s method to update ball position
		{
			ball2.cx -= vball2_x * dt;
			ball2.cy -= vball2_y * dt;
			vball2_y -= gravity * dt;

			if (ball2.cx <= 400 || ball2.cy <= 300)
			{
				ball2.state = 0;
				balls++;
				ball2.cx = 740 - 25 * cos(cannon2.cannonAngle);
				ball2.cy = 550 - 25 * sin(cannon2.cannonAngle);
			}
		}

		for (int i = 0; i < snake.snakeLength; ++i)
		{
			if (bar1.CheckHitBar(snake.snakeX[i], snake.snakeY[i], bar1.x, bar1.y, bar1.w, bar1.h) == true)
			{
				if (bar1.state == 1)
				{
					snake.snakeLength -= 2;
					bar1.state = 0;
					score -= 2;
				}
			}
		}
		for (int i = 0; i < snake.snakeLength; ++i)
		{
			if (bar2.CheckHitBar(snake.snakeX[i], snake.snakeY[i], bar2.x, bar2.y, bar2.w, bar2.h) == true)
			{
				if (bar2.state == 1)
				{
					snake.snakeLength -= 2;
					bar2.state = 0;
					score -= 2;
				}
			}
		}

		for (int i = 0; i < snake.snakeLength; ++i)
		{
			if (missile1.CheckHitMissile(snake.snakeX[i], snake.snakeY[i], missile1.x, missile1.y) == 1)
			{
				if (missile1.state == 1)
				{
					snake.snakeLength -= 3;
					missile1.state = 0;
					score -= 3;
					missile1.y = 220;
					lastHitTime1 = time(NULL);
					missile1.state = 1;
				}
			}
		}

		for (int i = 0; i < snake.snakeLength; ++i)
		{
			if (missile3.CheckHitMissile(snake.snakeX[i], snake.snakeY[i], missile3.x, missile3.y) == 1)
			{
				if (missile3.state == 1)
				{
					snake.snakeLength -= 3;
					missile3.state = 0;
					score -= 3;
					missile3.y = 220;
					lastHitTime3 = time(NULL);
					missile3.state = 1;
				}
			}
		}

		for (int i = 0; i < snake.snakeLength; ++i)
		{
			if (ball1.CheckHitBall(ball1.cx, ball1.cy, snake.snakeX[i], snake.snakeY[i], snake.snakeLength))
			{
				ball1.state = 0;
				snake.snakeLength -= 1;
				if (snake.snakeLength <= 1)
				{
					snake.snakeLength = 1;
				}
				ball1.cx = 450 + 25 * cos(cannon1.cannonAngle);
				ball1.cy = 550 - 25 * sin(cannon1.cannonAngle);
				score -= 1;
			}
		}

		for (int i = 0; i < snake.snakeLength; ++i)
		{
			if (ball2.CheckHitBall(ball2.cx, ball2.cy, snake.snakeX[i], snake.snakeY[i], snake.snakeLength))
			{
				ball2.state = 0;
				snake.snakeLength -= 1;
				if (snake.snakeLength <= 1)
				{
					snake.snakeLength = 1;
				}
				ball2.cx = 740 - 25 * cos(cannon2.cannonAngle);
				ball2.cy = 550 - 25 * sin(cannon2.cannonAngle);
				score -= 1;
			}
		}
		time_t current_time = time(NULL);
		double elapsed_time = difftime(current_time, start_time);
		if (elapsed_time <= 5.0)
		{

			glRasterPos2i(320, 300);
			YsGlDrawFontBitmap12x16("Gluttonous Snake");
			glRasterPos2i(50, 340);
			YsGlDrawFontBitmap12x16("Black: +0.5pt; Red: +1.0pt; Green: +1.5pt; Blue: +2.0pt");
			glRasterPos2i(50, 380);
			YsGlDrawFontBitmap12x16("Cannon Ball: -1pt; Bar: -2pt; Missile: -3pt; Wall: Game Over");
			glRasterPos2i(175, 420);
			YsGlDrawFontBitmap12x16("You have 30 seconds to get enough points!");
		}
		else
		{
			game.DrawBlueRegion();
			game.DrawYellowRegion();
			game.DrawPinkRegion();
			game.DrawGreenRegion();

			for (int i = 0; i < nFood; ++i)
			{
				if (foods[i].state == 1)
				{
					foods[i].DrawFood();
				}
			}
			for (int i = 0; i < snake.snakeLength; ++i)
			{
				snake.DrawSnake(snake.snakeX[i], snake.snakeY[i]);
			}

			game.DrawStoneShape();
			if (bar1.state == 1)
			{
				bar1.DrawBar();
			}
			if (bar2.state == 1)
			{
				bar2.DrawBar();
			}

			cannon1.Cannon1();
			cannon2.Cannon2();
			time_t currentTime1 = time(NULL);
			if (currentTime1 - lastHitTime1 >= 2)
			{
				if (missile1.state != 0)
				{
					missile1.DrawMissile();
					missile1.MoveMissile(missile1.x, missile1.y, 1);
				}
			}

			time_t currentTime3 = time(NULL);
			if (currentTime3 - lastHitTime3 >= 2)
			{
				if (missile3.state != 0)
				{
					missile3.DrawMissile();
					missile3.MoveMissile(missile3.x, missile3.y, 3);
				}
			}

			if (ball1.state != 0)
			{
				ball1.Ball();
			}

			if (ball2.state != 0)
			{
				ball2.Ball();
			}
			for (int i = 0; i < snake.snakeLength; ++i)
			{
				if (game.CheckHitWall(snake.snakeX[i], snake.snakeY[i], 50, 450, 90, 60) == true)
				{
					hitWall = true;
					hitWallTime = time(NULL);
					terminate = 1;   // The game will be over if the snake touches the boundary
					printf("Gameover! The total score is %f.", score);
				}
				if (hitWall)
				{
					time_t currentTime = time(NULL);
					double elapsedTime = difftime(currentTime, hitWallTime);

					if (elapsedTime <= 5.0)
					{
						string scoreString = "Total Score: " + to_string(score);
						const char* scoreStr = scoreString.c_str();
						glColor3ub(0, 0, 0);
						glRasterPos2i(360, 300);
						YsGlDrawFontBitmap12x16("Game over!");
						glRasterPos2i(300, 340);
						YsGlDrawFontBitmap12x16(scoreStr);
					}
					else
					{
						player.Stop(bgm);
						break;
					}
				}
			}

			for (int i = 0; i < snake.snakeLength; ++i)
			{
				if (game.CheckHitWall(snake.snakeX[i], snake.snakeY[i], 260, 320, 120, 75) == true)
				{
					hitWall = true;
					hitWallTime = time(NULL);
					terminate = 1;   // The game will be over if the snake touches the boundary
					printf("Gameover! The total score is %.1f.", score);
				}
				if (hitWall)
				{
					time_t currentTime = time(NULL);
					double elapsedTime = difftime(currentTime, hitWallTime);

					if (elapsedTime <= 5.0)
					{
						string scoreString = "Total Score: " + to_string(score);
						const char* scoreStr = scoreString.c_str();
						glColor3ub(0, 0, 0);
						glRasterPos2i(360, 300);
						YsGlDrawFontBitmap12x16("Game over!");
						glRasterPos2i(300, 340);
						YsGlDrawFontBitmap12x16(scoreStr);
					}
					else
					{
						player.Stop(bgm);
						break;
					}
				}
			}

			for (int i = 0; i < snake.snakeLength; ++i)
			{
				time_t currentTime = time(NULL);
				double duration = difftime(currentTime, start_time);

				if (duration == 35.0) {
					string scoreString = "Total Score: " + to_string(score);
					const char* scoreStr = scoreString.c_str();
					glColor3ub(0, 0, 0);
					glRasterPos2i(360, 300);
					YsGlDrawFontBitmap12x16("Game over!");
					glRasterPos2i(300, 340);
					YsGlDrawFontBitmap12x16(scoreStr);
				}
				if (duration > 35)
				{
					printf("Gameover! The total score is %.1f.", score);
					player.Stop(bgm);
					FsCloseWindow();
					break;
				}
			}

			game.DrawBoundary();
			glColor3ub(0, 0, 0);
			glRasterPos2i(10, 35);
			char scoreStr[50];
			sprintf(scoreStr, "Score: %.1f", score);
			YsGlDrawFontBitmap20x32(scoreStr);
		}
		glFlush();
		//FsSwapBuffers();
		FsSleep(10);
	}
	return 0;
}