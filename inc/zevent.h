//
// Created by sl on 09.07.19.
//

#ifndef YRGB2019_EVENT_H
#define YRGB2019_EVENT_H

#define null (void *)0x0000

#define EVT_MAX_SENTENCES 4

enum {
    EVT_IDLE=0,
    EVT_MOVE_FORWARD,
    EVT_STUCK_FORWARD,
    EVT_MOVE_BACKWARD,
    EVT_STUCK_BACKWARD,
    EVT_TURN_LEFT,
    EVT_TURN_RIGHT,
    EVT_LOOK_NORTH,
    EVT_LOOK_SOUTH,
    EVT_LOOK_EAST,
    EVT_LOOK_WEST,
    EVT_NUM_EVENTS
};

enum {
    EVT_FIRST_TIME=0,
    EVT_SECOND_TIME,
    EVT_THIRD_TIME,
    EVT_MANY_TIMES,
    EVT_NUM_REPETITIONS
};

void initEvents();
void castEvent(unsigned char event);
char *describeEvent();

#endif //YRGB2019_EVENT_H
