#ifndef MOVEMENT_H
#define MOVEMENT_H




char idle[15] = "img\\d1.bmp";
char walkRight[4][20] = { "img\\r1.bmp", "img\\r2.bmp", "img\\r3.bmp", "img\\r4.bmp" };
char walkLeft[4][20] = { "img\\l1.bmp", "img\\l2.bmp", "img\\l3.bmp", "img\\l4.bmp" };
char walkUp[4][20] = { "img\\u1.bmp", "img\\u2.bmp", "img\\u3.bmp", "img\\u4.bmp" };
char walkDown[4][20] = { "img\\d1.bmp", "img\\d2.bmp", "img\\d3.bmp", "img\\d4.bmp" };

double charX = 400;
double charY = 220;
int charIndex = 0;
bool idlePosition = true;
int idleCounter = 0;
int char_x_direction = 0;
int char_y_direction = 0;
const double CHAR_SPEED = 5;



































#endif