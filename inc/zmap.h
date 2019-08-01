//
// Created by sl on 11.07.19.
//

#ifndef YRGB2019_MAP_H
#define YRGB2019_MAP_H

#include <tools.h>
#include <zgraph.h>
#include <trig.h>

#define WALL_BUFFER_SIZE SCREEN_CHAR_WIDTH

#define MAP_WIDTH 32
#define MAP_HEIGHT 32

extern unsigned int playerX;
extern unsigned int playerY;
extern unsigned char playerAngle;

void drawSpriteColumn(unsigned char left, unsigned char distance, unsigned char width, unsigned char *spite);
void renderWalls();
void calculateWalls();
unsigned int traceRay(unsigned int myX, unsigned int myY, unsigned char angle);
char getMapAt(unsigned int x, unsigned int y);

#endif //YRGB2019_MAP_H
