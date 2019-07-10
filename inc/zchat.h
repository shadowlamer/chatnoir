//
// Created by sl on 11.07.19.
//

#ifndef YRGB2019_CHAT_H
#define YRGB2019_CHAT_H

#include <zgraph.h>

#define TEXT_BUFFER_START SCREEN_BUFFER_START + 0x1000
#define DEFAULT_FONT_START 0x3c00

void printNumAt(unsigned char x, unsigned char num);
void printOneLine(unsigned char *s);
void scrollText();

#endif //YRGB2019_CHAT_H
