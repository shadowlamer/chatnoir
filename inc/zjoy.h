//
// Created by sl on 11.07.19.
//

#ifndef YRGB2019_JOY_H
#define YRGB2019_JOY_H

enum {
    JOY_IDLE = 0,
    JOY_FORWARD,
    JOY_BACKWARD,
    JOY_LEFT,
    JOY_RIGHT,
    JOY_ACTION
};

unsigned char getJoy();

#endif //YRGB2019_JOY_H
