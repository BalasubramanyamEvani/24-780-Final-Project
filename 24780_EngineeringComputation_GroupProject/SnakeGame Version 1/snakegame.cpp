#include "snakegame.h"
#include "fssimplewindow.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

const double pi = 3.1415927;
//using namespace std;
void DrawCircle(double cx, double cy, double rad)
{
	const double YS_PI = 3.1415927;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 64; i++)
	{
		double angle = (double)i * YS_PI / 32.0;
		double x = (double)cx + cos(angle) * (double)rad;
		double y = (double)cy + sin(angle) * (double)rad;
		glVertex2d(x, y);
	}
	glEnd();
}

void Food::InitializeFood() {
	x = rand() % 750 + 25;
	y = rand() % 550 + 25;
	type = rand() % 4 + 1;
	radius = 5;
	state = 1;

	switch (type) {
	case 1:
		colorR = 0; // black food
		colorG = 0;
		colorB = 0;
		break;
	case 2:
		colorR = 1.0; // red food
		colorG = 0.0;
		colorB = 0.0;
		break;
	case 3:
		colorR = 0.0; // green food
		colorG = 1.0;
		colorB = 0.0;
		break;
	case 4:
		colorR = 0.0; // blue food
		colorG = 0.0;
		colorB = 1.0;
		break;
	}
}
void Food::DrawFood()
{
	glColor3f(colorR, colorG, colorB);
	DrawCircle(x, y, radius);
}
bool Food::CheckHitFood(double snake_x, double snake_y, double food_x, double food_y, double snake_width, double snake_height, double food_rad)
{
	return ((snake_x - food_x) >= -(snake_width + food_rad) && (snake_x - food_x) <= food_rad && (snake_y - food_y) >= -(snake_height + food_rad) && (snake_y - food_y) <= food_rad);
}

void Missile::DrawMissile()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x - 15, y + 20);
	glVertex2f(x - 15, y + 65);
	glVertex2f(x + 15, y + 65);
	glVertex2f(x + 15, y + 20);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(x - 15, y + 68);
	glVertex2i(x - 15, y + 75);

	glVertex2i(x - 5, y + 68);
	glVertex2i(x - 5, y + 75);

	glVertex2i(x + 5, y + 68);
	glVertex2i(x + 5, y + 75);

	glVertex2i(x + 15, y + 68);
	glVertex2i(x + 15, y + 75);
	glEnd();
}
void Missile::MoveMissile(double& x, double& y, double speed)
{
	y -= speed;
	if (y < -100)
	{
		y = 220;
	}
}
int Missile::CheckHitMissile(double snake_x, double snake_y, double missile_x, double missile_y)
{
	double relativeX, relativeY;
	relativeX = snake_x - missile_x;
	relativeY = snake_y - missile_y;
	if (-15 <= relativeX && relativeX <= 15 && 0 <= relativeY && relativeY < 75)
		return 1;
	else
		return 0;
}

void Bar::DrawBar()
{
	glColor3ub(138, 43, 226);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();
}
int Bar::CheckHitBar(double snake_x, double snake_y, double bar_x, double bar_y, double barsizeX, double barsizeY)
{
	double relativeX, relativeY;
	relativeX = snake_x - bar_x;
	relativeY = snake_y - bar_y;
	if (0 <= relativeX && relativeX < barsizeX && 0 <= relativeY && relativeY < barsizeY)
		return 1;
	else
		return 0;
}

void Cannon::Cannon1()
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2i(420, 550);
	glVertex2i(450, 550);
	glVertex2i(450, 580);
	glVertex2i(420, 580);
	glEnd();

	glLineWidth(2);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2i(450, 550);
	glVertex2d(450 + 25 * cos(cannonAngle), 550 - 25 * sin(cannonAngle));
	glEnd();
}
void Cannon::Cannon2()
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2i(740, 550);
	glVertex2i(770, 550);
	glVertex2i(770, 580);
	glVertex2i(740, 580);
	glEnd();

	glLineWidth(2);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2i(740, 550);
	glVertex2d(740 - 25 * cos(cannonAngle), 550 - 25 * sin(cannonAngle));
	glEnd();
}

void CannonBall::Ball()
{
	glColor3ub(255, 255, 0);
	glBegin(GL_POLYGON);

	int i;
	for (i = 0; i < 64; i++)
	{
		double angle = (double)i * pi / 32.0;
		double x = (double)cx + cos(angle) * (double)rad;
		double y = (double)cy + sin(angle) * (double)rad;
		glVertex2d(x, y);
	}
	glEnd();
}
bool CannonBall::CheckHitBall(int ball_x, int ball_y, int snake_x, int snake_y, int snakeLength)
{
	return (ball_x >= snake_x && ball_x <= (snake_x + 13) && ball_y >= snake_y && ball_y <= (snake_y + 13));
}

Snake::Snake()
{
	snakeLength = 1;
	snakeWidth = 10;
	snakeHeight = 10;

	snakeX[0] = 30;
	snakeY[0] = 560;
	snakeDirection[0] = 0; // Initialize direction
}
void Snake::DrawSnake(double x, double y) {
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	glColor3ub(255, 0, 0);
	glVertex2f(x, y);

	glColor3ub(0, 255, 0);
	glVertex2f(x + snakeWidth, y);

	glColor3ub(0, 0, 255);
	glVertex2f(x + snakeWidth, y + snakeHeight);

	glColor3ub(255, 255, 0);
	glVertex2f(x, y + snakeHeight);
	glEnd();
}
void Snake::HandleInput(int key) {
	switch (key) {
	case FSKEY_UP:
		if (snakeDirection[0] != 2)
			snakeDirection[0] = 1;    // Go up
		break;
	case FSKEY_DOWN:
		if (snakeDirection[0] != 1)
			snakeDirection[0] = 2;    // Go down
		break;
	case FSKEY_RIGHT:
		if (snakeDirection[0] != 4)
			snakeDirection[0] = 3;    // Go right
		break;
	case FSKEY_LEFT:
		if (snakeDirection[0] != 3)
			snakeDirection[0] = 4;    // Go left
		break;
	}
}
void Snake::MoveBody() {
	for (int i = snakeLength - 1; i > 0; --i) {
		if (snakeLength > maxLength)
			snakeLength = maxLength;

		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
	}
}
void Snake::MoveSnake(int direction) {
	MoveBody();
	switch (direction) {
	case 1:
		snakeY[0] -= 3; // Snake moving speed
		break;
	case 2:
		snakeY[0] += 3;
		break;
	case 3:
		snakeX[0] += 3;
		break;
	case 4:
		snakeX[0] -= 3;
		break;
	}
}
Snake::~Snake() {
	// Empty destructor
	// No dynamic memory allocation to clean up
}

void SnakeGame::DrawBoundary()
{

	for (int i = 0; i < 800; i += 15)
	{
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_TRIANGLES);
		glVertex2i(i, 0);
		glVertex2i(i + 20, 0);
		glVertex2i(i + 10, 20);

		glBegin(GL_TRIANGLES);
		glVertex2i(0, i);
		glVertex2i(0, i + 20);
		glVertex2i(20, i + 10);

		glBegin(GL_TRIANGLES);
		glVertex2i(i, 600);
		glVertex2i(i + 20, 600);
		glVertex2i(i + 10, 600 - 20);

		glBegin(GL_TRIANGLES);
		glVertex2i(800, i);
		glVertex2i(800, i + 20);
		glVertex2i(800 - 20, i + 10);

	}
	glEnd();
}
void SnakeGame::DrawBlueRegion()
{
	glColor4ub(202, 235, 216, 0);   // Green
	glBegin(GL_POLYGON);
	glVertex2i(0, 0);
	glVertex2i(400, 0);
	glVertex2i(400, 300);
	glVertex2i(0, 300);
	glEnd();
}
void SnakeGame::DrawPinkRegion()
{
	glColor4ub(255, 235, 205, 0);   // Yellow
	glBegin(GL_POLYGON);
	glVertex2i(400, 0);
	glVertex2i(800, 0);
	glVertex2i(800, 300);
	glVertex2i(400, 300);
	glEnd();
}
void SnakeGame::DrawYellowRegion()
{
	glColor4ub(244, 164, 95, 0);   // Deep Yellow
	glBegin(GL_POLYGON);
	glVertex2i(0, 300);
	glVertex2i(400, 300);
	glVertex2i(400, 600);
	glVertex2i(0, 600);
	glEnd();
}
void SnakeGame::DrawGreenRegion()
{
	glColor4ub(255, 192, 203, 0);   // Pink
	glBegin(GL_POLYGON);
	glVertex2i(400, 300);
	glVertex2i(800, 300);
	glVertex2i(800, 600);
	glVertex2i(400, 600);
	glEnd();
}
void SnakeGame::DrawStoneShape()
{
	glLineWidth(2.0);

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex2i(50, 450);
	glVertex2i(140, 450);
	glVertex2i(140, 510);
	glVertex2i(50, 510);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(50, 450);
	glVertex2i(140, 450);

	glVertex2i(70, 450);
	glVertex2i(70, 470);

	glVertex2i(120, 450);
	glVertex2i(120, 470);

	glVertex2i(50, 470);
	glVertex2i(140, 470);

	glVertex2i(95, 470);
	glVertex2i(95, 490);

	glVertex2i(50, 490);
	glVertex2i(140, 490);

	glVertex2i(70, 490);
	glVertex2i(70, 510);

	glVertex2i(120, 490);
	glVertex2i(120, 510);

	glVertex2i(140, 510);
	glVertex2i(50, 510);
	glEnd();


	glLineWidth(2.0);

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex2i(260, 320);
	glVertex2i(380, 320);
	glVertex2i(380, 395);
	glVertex2i(260, 395);
	glEnd();


	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(260, 320);
	glVertex2i(380, 320);

	glVertex2i(300, 320);
	glVertex2i(300, 345);

	glVertex2i(340, 320);
	glVertex2i(340, 345);

	glVertex2i(260, 345);
	glVertex2i(380, 345);

	glVertex2i(320, 345);
	glVertex2i(320, 370);

	glVertex2i(260, 370);
	glVertex2i(380, 370);

	glVertex2i(300, 370);
	glVertex2i(300, 395);

	glVertex2i(340, 370);
	glVertex2i(340, 395);

	glVertex2i(380, 395);
	glVertex2i(260, 395);
	glEnd();
}
int SnakeGame::CheckHitWall(double snake_x, double snake_y, double wall_x, double wall_y, double wallsizeX, double wallsizeY)
{
	double relativeX, relativeY;
	relativeX = snake_x - wall_x;
	relativeY = snake_y - wall_y;
	if (0 <= relativeX && relativeX < wallsizeX && 0 <= relativeY && relativeY < wallsizeY)
		return 1;
	else
		return 0;
}