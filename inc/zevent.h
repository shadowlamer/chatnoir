//
// Created by sl on 09.07.19.
//

#ifndef YRGB2019_EVENT_H
#define YRGB2019_EVENT_H

#include <tools.h>

#define EVT_MAX_SENTENCES 4

enum {
    EVT_MASK_MOVEMENT   = 0b1000000000000000,
    EVT_MASK_TROUBLE    = 0b0100000000000000,
    EVT_MASK_REPEAT     = 0b0010000000000000,
    EVT_MASK_FORWARD    = 0b0000000000000001,
    EVT_MASK_BACKWARD   = 0b0000000000000010,
    EVT_MASK_LEFT       = 0b0000000000000100,
    EVT_MASK_RIGHT      = 0b0000000000001000,
};

enum {
    EVT_IDLE            = 0b0000000000000000,
    EVT_MOVE_FORWARD    = EVT_MASK_MOVEMENT | EVT_MASK_FORWARD,
    EVT_STUCK_FORWARD   = EVT_MASK_TROUBLE  | EVT_MASK_FORWARD,
    EVT_MOVE_BACKWARD   = EVT_MASK_MOVEMENT | EVT_MASK_BACKWARD,
    EVT_STUCK_BACKWARD  = EVT_MASK_TROUBLE  | EVT_MASK_BACKWARD,
    EVT_TURN_LEFT       = EVT_MASK_MOVEMENT | EVT_MASK_LEFT,
    EVT_TURN_RIGHT      = EVT_MASK_MOVEMENT | EVT_MASK_RIGHT,
};

typedef struct {
    const unsigned int mask;
    const unsigned char prob;
    const char *quote;
} Quote;

void initEvents();
void castEvent(unsigned int event);
char *describeEvent();
char *findQuote(unsigned int event);

#endif //YRGB2019_EVENT_H
