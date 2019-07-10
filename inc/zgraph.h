//
// Created by sl on 10.07.19.
//

#ifndef YRGB2019_GRAPH_H
#define YRGB2019_GRAPH_H

#include <string.h>

#define SCREEN_PIXEL_WIDTH 256
#define SCREEN_PIXEL_HEIGHT 192
#define PIXELS_PER_LINE 8
#define LINES_PER_CHAR 8
#define SCREEN_CHAR_WIDTH 32
#define SCREEN_CHAR_HEIGHT 16

#define SCREEN_BUFFER_START 0x4000
#define SCREEN_BUFFER_SIZE  SCREEN_CHAR_WIDTH * SCREEN_PIXEL_HEIGHT

#define ATTRS_BUFFER_START SCREEN_BUFFER_START + SCREEN_BUFFER_SIZE
#define ATTRS_BUFFER_SIZE SCREEN_CHAR_WIDTH * SCREEN_CHAR_HEIGHT

extern __at (SCREEN_BUFFER_START)  char screen[];
extern __at (ATTRS_BUFFER_START)  char screenAttrs[];


void fillScreen(char pattern);
void fillScreenAttrs(char pattern, unsigned char startLine, unsigned char lines);
void putSprite(unsigned char x, unsigned char y, char *sprite);
void fastFillScreenWithSprite(char *sprite, unsigned char height);


#endif //YRGB2019_GRAPH_H
