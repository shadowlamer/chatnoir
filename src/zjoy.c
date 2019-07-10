//
// Created by sl on 11.07.19.
//

#include <zjoy.h>
__sfr __banked __at 0xf7fe joystickKeysPort;

unsigned char getJoy() {
    unsigned char scanline;
    scanline = joystickKeysPort & 0x0f ^ 0x0f;
    if (scanline & 0b00000100) return JOY_FORWARD;
    if (scanline & 0b00001000) return JOY_BACKWARD;
    if (scanline & 0b00000010) return JOY_RIGHT;
    if (scanline & 0b00000001) return JOY_LEFT;
    if (scanline & 0b00010000) return JOY_ACTION;
    return JOY_IDLE;
}

