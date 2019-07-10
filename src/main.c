#include <string.h>

#include <zgraph.h>
#include <zevent.h>
#include <trig.h>
#include <zmap.h>
#include <zchat.h>
#include <zjoy.h>

unsigned char canExit;
unsigned char *msg;

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

    calculateWalls();
    renderWalls();

    while (!canExit) {

        if ((joyAction = getJoy()) != JOY_IDLE ) {
            switch (joyAction) {
                case JOY_FORWARD:
                    newX = playerX + COS(playerAngle);
                    newY = playerY + SIN(playerAngle);
                    if (getMapAt(newX, newY) != 1) {
                        playerX = newX;
                        playerY = newY;
                        castEvent(EVT_MOVE_FORWARD);
                    } else {
                        castEvent(EVT_STUCK_FORWARD);
                    }
                    break;
                case JOY_BACKWARD:
                    newX = playerX - COS(playerAngle);
                    newY = playerY - SIN(playerAngle);
                    if (getMapAt(newX, newY) != 1) {
                        playerX = newX;
                        playerY = newY;
                        castEvent(EVT_MOVE_BACKWARD);
                    } else {
                        castEvent(EVT_STUCK_BACKWARD);
                    }
                    break;
                case JOY_RIGHT:
                    playerAngle += 32;
                    playerAngle &= 0xff;
                    castEvent(EVT_TURN_RIGHT);
                    break;
                case JOY_LEFT:
                    playerAngle -= 32;
                    playerAngle &= 0xff;
                    castEvent(EVT_TURN_LEFT);
                    break;
            }

            calculateWalls();
            while ((msg=describeEvent()) != null) {
                printOneLine(msg);
            }
            renderWalls();
       }
    }
}
