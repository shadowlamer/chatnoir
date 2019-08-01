#include <string.h>

#include <zgraph.h>
#include <zevent.h>
#include <trig.h>
#include <zmap.h>
#include <zchat.h>
#include <zjoy.h>
#include <sound.h>

unsigned char canExit;
unsigned char *msg;

const Note melody[10] = {
        {.tone = 0,  .time=2000},
        {.tone = 1,  .time=2000},
        {.tone = 2,  .time=2000},
        {.tone = 3,  .time=2000},
        {.tone = 4,  .time=2000},
        {.tone = 5,  .time=2000},
        {.tone = 6,  .time=2000},
        {.tone = 7,  .time=2000},
//        {.tone = 9,  .time=2000},
        {.tone = 255, .time=0},
};

void main()
{
    unsigned char joyAction;

    unsigned int newX;
    unsigned int newY;

    canExit = 0;

    playerX = 0x0180;
    playerY = 0x0180;
    playerAngle = 0x00;

    initEvents();
    initSound();

    calculateWalls();
    renderWalls();

    while (!canExit) {
//        if (!isPlaying(0)) play(0, melody);
//        processSound();
        if ((joyAction = getJoy()) != JOY_IDLE ) {
            switch (joyAction) {
                case JOY_FORWARD:
                    newX = playerX + COS(playerAngle);
                    newY = playerY + SIN(playerAngle);
                    if (getMapAt(newX, newY) != 1) {
                        playerX = newX;
                        playerY = newY;
//                        castEvent(EVT_MOVE_FORWARD);
                    } else {
//                        castEvent(EVT_STUCK_FORWARD);
                    }
                    break;
                case JOY_BACKWARD:
                    newX = playerX - COS(playerAngle);
                    newY = playerY - SIN(playerAngle);
                    if (getMapAt(newX, newY) != 1) {
                        playerX = newX;
                        playerY = newY;
//                        castEvent(EVT_MOVE_BACKWARD);
                    } else {
//                        castEvent(EVT_STUCK_BACKWARD);
                    }
                    break;
                case JOY_RIGHT:
                    playerAngle += 8;
                    playerAngle &= 0xff;
//                    castEvent(EVT_TURN_RIGHT);
                    break;
                case JOY_LEFT:
                    playerAngle -= 8;
                    playerAngle &= 0xff;
//                    castEvent(EVT_TURN_LEFT);
                    break;
            }

            calculateWalls();
//            while ((msg=describeEvent()) != null) {
//                printOneLine(msg);
//            }
            renderWalls();
       }
    }
}
