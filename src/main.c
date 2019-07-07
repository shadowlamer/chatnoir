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

#define DATA_START 0xf000
#define WALL_BUFFER_START DATA_START
#define WALL_BUFFER_SIZE SCREEN_CHAR_WIDTH

#define MAP_WIDTH 32
#define MAP_HEIGHT 32

char *screen;
char *screenAttrs;
char wallRenderBuffer[WALL_BUFFER_SIZE];

#include <bush0.h>

const char map[MAP_HEIGHT][MAP_WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

const char sine[256] = {
       0,   3,   6,   9,  12,  16,  19,  22,  25,  28,  31,  34,  37,  40,  43,  46,
      49,  51,  54,  57,  60,  63,  65,  68,  71,  73,  76,  78,  81,  83,  85,  88,
      90,  92,  94,  96,  98, 100, 102, 104, 106, 107, 109, 110, 112, 113, 115, 116,
     117, 118, 120, 121, 122, 122, 123, 124, 125, 125, 126, 126, 126, 127, 127, 127,
     127, 127, 127, 127, 126, 126, 126, 125, 125, 124, 123, 122, 122, 121, 120, 118,
     117, 116, 115, 113, 112, 111, 109, 107, 106, 104, 102, 100,  98,  96,  94,  92,
      90,  88,  85,  83,  81,  78,  76,  73,  71,  68,  65,  63,  60,  57,  54,  51,
      49,  46,  43,  40,  37,  34,  31,  28,  25,  22,  19,  16,  12,   9,   6,   3,
       0,  -3,  -6,  -9, -12, -16, -19, -22, -25, -28, -31, -34, -37, -40, -43, -46,
     -49, -51, -54, -57, -60, -63, -65, -68, -71, -73, -76, -78, -81, -83, -85, -88,
     -90, -92, -94, -96, -98,-100,-102,-104,-106,-107,-109,-110,-112,-113,-115,-116,
    -117,-118,-120,-121,-122,-122,-123,-124,-125,-125,-126,-126,-126,-127,-127,-127,
    -127,-127,-127,-127,-126,-126,-126,-125,-125,-124,-123,-122,-122,-121,-120,-118,
    -117,-116,-115,-113,-112,-111,-109,-107,-106,-104,-102,-100, -98, -96, -94, -92,
     -90, -88, -85, -83, -81, -78, -76, -73, -71, -68, -65, -63, -60, -57, -54, -51,
     -49, -46, -43, -40, -37, -34, -31, -28, -25, -22, -19, -16, -12,  -9,  -6,  -3
};

const unsigned char bushColors[SCREEN_CHAR_HEIGHT / 2] = {
1};

const unsigned char wallSizes[8] = {4, 3, 2, 2, 1, 1, 1, 1};
const unsigned int  wallSpriteOffsets[8] = {0, 512, 848, 1040, 1200, 1264, 1312, 1344};

const unsigned char bushSprite[8] = {104, 88, 40, 8, 18, 22, 26, 84};
const unsigned char bushTopSprite[8] = {85, 85, 73, 42, 42, 42, 20, 72};
const unsigned char textureSprite[8] = {0, 0, 0, 0, 0, 0, 0, 0};
char *font;

__sfr __banked __at 0xf7fe joystickKeysPort;

unsigned int playerX;
unsigned int playerY;

unsigned char playerAngle;

void fillScreen(char pattern);
void fastFillScreenWithSprite(char *sprite, unsigned char height);
void fillScreenAttrs(char pattern, unsigned char startLine, unsigned char lines);
void drawColumnOfAttrs(unsigned char left, unsigned char top, unsigned char bottom);
void drawSpriteColumn(unsigned char left, unsigned char distance);
void renderWalls();
void calculateWalls();
unsigned int traceRay(unsigned int myX, unsigned int myY, unsigned char angle);
char getMapAt(unsigned int x, unsigned int y);
void putSprite(unsigned char x, unsigned char y, char *sprite);

void printNumAt(unsigned char x, unsigned char num);

unsigned char canExit = 0;

void main()
{
    unsigned char scanline;

    unsigned int newX;
    unsigned int newY;


    screen = (char *)SCREEN_BUFFER_START;
    screenAttrs = (char *)ATTRS_BUFFER_START;
    font = (char *)0x3c00;


    playerX = 0x0180;
    playerY = 0x0180;
    playerAngle = 0x00;

    calculateWalls();
    renderWalls();

    while (!canExit) {

        scanline = joystickKeysPort & 0x0f ^ 0x0f;

        if (scanline != 0) {
             if (scanline & 0b00000100) {
                 newX = playerX + sine[(playerAngle + 64) & 0xff];
                 newY = playerY + sine[playerAngle];
                 if (getMapAt( newX, newY) != 1) {
                     playerX = newX;
                     playerY = newY;
                 }
             }
             if (scanline & 0b00001000) {
                 newX = playerX - sine[(playerAngle + 64) & 0xff];
                 newY = playerY - sine[playerAngle];
                 if (getMapAt( newX, newY) != 1) {
                     playerX = newX;
                     playerY = newY;
                 }
             }
             if (scanline & 0b00000010) {
                 playerAngle += 5;
                 playerAngle &= 0xff;
             }
             if (scanline & 0b00000001) {
                 playerAngle -= 5;
                 playerAngle &= 0xff;
             }
             calculateWalls();
             renderWalls();
        }
    }
}

void printNumAt(unsigned char x, unsigned char num) {
//    screenAttrs[SCREEN_CHAR_WIDTH * 0 + x] = 0b01000111;
    putSprite(x, 2, font + (('0' + (num % 10)) * 8));
    num = num / 10;
//    screenAttrs[SCREEN_CHAR_WIDTH * 1 + x] = 0b01000111;
    putSprite(x, 1, font + (('0' + (num % 10)) * 8));
    num = num / 10;
//    screenAttrs[SCREEN_CHAR_WIDTH * 2 + x] = 0b01000111;
    putSprite(x, 0, font + (('0' + (num % 10)) * 8));
}


void fastFillScreenWithSprite(char *sprite, unsigned char height) {
    unsigned char i;
    char *p = screen;
    for (i=0; i < height; i++) {
        memset(p, sprite[i & 0x07], 0x0100);
        p+=0x0100;
    }
}

void putSprite(unsigned char x, unsigned char y, char *sprite) {

    unsigned int pos;
    unsigned int i;

    pos = ((y & 0b00000111) << 5) | ((y & 0b00011000) << 8) | x;

    for (i = 0; i < 8; i++ ) {
        screen[pos] = sprite[i];
        pos += 0x0100;
    }
}


unsigned int traceRay(unsigned int myX, unsigned int myY, unsigned char angle) {
    unsigned int x = myX;
    unsigned int y = myY;
    unsigned char effAngle = angle + playerAngle - (SCREEN_CHAR_WIDTH / 2);
    unsigned int ray = 0;
    unsigned int sin = sine[effAngle];
    unsigned int cos = sine[(effAngle + 64) & 0xff];
    unsigned char screenCoef = sine[(angle * 2) + 32];
    while (getMapAt(x, y) == 0 && ray < 0x10) {
        x += cos;
        y += sin;
        ray++;
    }
//    return ray;
    return (ray * screenCoef) >> 7;
}

char getMapAt(unsigned int x, unsigned int y){
    unsigned char mapX = ( x >> 8 ) & 0xff;
    unsigned char mapY = ( y >> 8 ) & 0xff;
    return map[mapY][mapX];
}


void renderWalls() {
    int i;
    unsigned char wallDistance;
    unsigned char wallSize;
//    fillScreenAttrs(j0x00, 0, SCREEN_CHAR_HEIGHT);
    fillScreen(0x00);
    fillScreenAttrs(0b00000100, 0, 16);
//    fillScreenAttrs(0xb00000100, 0, SCREEN_CHAR_HEIGHT);
    for (i=0; i<SCREEN_CHAR_WIDTH; ) {
        wallDistance = wallRenderBuffer[i];
        if (wallDistance > 7) wallDistance = 7;
        wallSize = wallSizes[wallDistance];
//        drawColumnOfAttrs(i, wallDistance, SCREEN_CHAR_HEIGHT - wallDistance - 1);
        drawSpriteColumn(i, wallDistance);
        i += wallSize;
    }
}


void calculateWalls() {
    int i;
    for (i=0; i<SCREEN_CHAR_WIDTH; i++) {
        wallRenderBuffer[i] = traceRay(playerX, playerY, i);
    }
}


void drawSpriteColumn(unsigned char left, unsigned char distance){
    unsigned char i;
    unsigned int pos = left;
    unsigned char width = wallSizes[distance];
    unsigned int spritePos = wallSpriteOffsets[distance];
//    unsigned int spritePos = 0;
    if (( left + width ) > SCREEN_CHAR_WIDTH)
        width = SCREEN_CHAR_WIDTH - left;
    for (i = 0; i < 64; i++) {
        if (((pos >> 5) & 0x07) >= distance) {
            memcpy(screen + pos, bush0 + spritePos, width);
            spritePos += width;
        }
        pos += SCREEN_CHAR_WIDTH;
    }
    for (i = 0; i < 64; i++) {
        if (((pos >> 5) & 0x07) <= (7 - distance)) {
            memcpy(screen + pos, bush0 + spritePos, width);
            spritePos += width;
        }
        pos += SCREEN_CHAR_WIDTH;
    }
//    printNumAt(left, distance);
}
void drawColumnOfAttrs(unsigned char left, unsigned char top, unsigned char bottom) {
    unsigned char y;
    unsigned char attr;

    for (y = top; y < bottom; y++ ){
//        attr = ((y > top) && (y < bottom + 1)) ? bushColors[top] : (char)0b00000000;
//        screenAttrs[left + (SCREEN_CHAR_WIDTH * y)] = attr;
        screenAttrs[left + (SCREEN_CHAR_WIDTH * y)] = bushColors[top];
    }
}

void fillScreen(char pattern) {
    memset(screen, pattern, SCREEN_BUFFER_SIZE);
}

void fillScreenAttrs(char pattern, unsigned char startLine, unsigned char lines) {
    memset(screenAttrs + startLine * SCREEN_CHAR_WIDTH, pattern, lines * SCREEN_CHAR_WIDTH);
}
