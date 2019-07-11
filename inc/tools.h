//
// Created by sl on 11.07.19.
//

#ifndef YRGB2019_TOOLS_H
#define YRGB2019_TOOLS_H

#define RANDOM_BUFFER_START 0x1234

#define RANDOM(x) random[x]

extern __at (RANDOM_BUFFER_START) char random[];

unsigned char rand();

#endif //YRGB2019_TOOLS_H
