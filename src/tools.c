//
// Created by sl on 11.07.19.
//

#include <tools.h>

__at (RANDOM_BUFFER_START) char random[];

unsigned int seedPointer;

unsigned char rand() {
    seedPointer &= 0x07ff;
    seedPointer++;
    return RANDOM(seedPointer);
}