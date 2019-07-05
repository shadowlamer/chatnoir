#include <string.h>

#define SCREEN_PIXEL_WIDTH 256
#define SCREEN_PIXEL_HEIGHT 192
#define PIXELS_PER_LINE 8
#define LINES_PER_CHAR 8
#define SCREEN_CHAR_WIDTH 32
#define SCREEN_CHAR_HEIGHT 24

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
const char map[MAP_HEIGHT][MAP_WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

const char sine[256] = {   0,   3,   6,   9,  12,  16,  19,  22,  25,  28,  31,  34,  37,  40,  43,  46,
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
                         -49, -46, -43, -40, -37, -34, -31, -28, -25, -22, -19, -16, -12,  -9,  -6,  -3 };

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
void fillScreenAttrs(char pattern);
void drawColumnOfAttrs(unsigned char left, unsigned char top, unsigned char bottom);
void renderWalls();
void calculateWalls();
unsigned int traceRay(unsigned int myX, unsigned int myY, unsigned char angle);
char getMapAt(unsigned int x, unsigned int y);
void putSprite(unsigned char x, unsigned char y, char *sprite);

void printNumAt(unsigned char x, unsigned char num);

void main()
{
    unsigned char i, j;

    screen = (char *)SCREEN_BUFFER_START;
    screenAttrs = (char *)ATTRS_BUFFER_START;
    font = (char *)0x3c00;

//    fillScreen((char)0xaa);

    playerX = 0x0480;
    playerY = 0x0480;
    playerAngle = 0x00;

    fastFillScreenWithSprite(bushSprite, SCREEN_CHAR_HEIGHT);

    while (1) {

         if ((joystickKeysPort & 0b00001111)) {
             if (joystickKeysPort & 0b00000100) {
                 playerX += sine[(playerAngle + 64) & 0xff];
                 playerY += sine[playerAngle];
             }
             if (joystickKeysPort & 0b00001000) {
                 playerX -= sine[(playerAngle + 64) & 0xff];
                 playerY -= sine[playerAngle];
             }
             if (joystickKeysPort & 0b00000010) {
                 playerAngle += 5;
                 playerAngle &= 0xff;
             }
             if (joystickKeysPort & 0b00000001) {
                 playerAngle -= 5;
                 playerAngle &= 0xff;
             }
             calculateWalls();
             renderWalls();
         }
    }
}

void printNumAt(unsigned char x, unsigned char num) {
    putSprite(x, 2, font + (('0' + (num % 10)) * 8));
    num = num / 10;
    putSprite(x, 1, font + (('0' + (num % 10)) * 8));
    num = num / 10;
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
    while (getMapAt(x, y) == 0 && ray < 0x10) {
        x += cos;
        y += sin;
        ray++;
    }
    return ray;
}

char getMapAt(unsigned int x, unsigned int y){
    unsigned char mapX = ( x >> 8 ) & 0xff;
    unsigned char mapY = ( y >> 8 ) & 0xff;
    return map[mapY][mapX];
}


void renderWalls() {
    int i;
    for (i=0; i<SCREEN_CHAR_WIDTH; i++) {
        drawColumnOfAttrs(i, wallRenderBuffer[i], SCREEN_CHAR_HEIGHT - wallRenderBuffer[i] - 1);
    }
}


void calculateWalls() {
    int i;
    for (i=0; i<SCREEN_CHAR_WIDTH; i++) {
        wallRenderBuffer[i] = traceRay(playerX, playerY, i);
    }
}

void drawColumnOfAttrs(unsigned char left, unsigned char top, unsigned char bottom) {
    unsigned char y;
    unsigned char attr;

    for (y = 0; y < SCREEN_CHAR_HEIGHT; y++ ){
        attr = ((y > top) && (y < bottom)) ? (char)(0b00000100) : (char)0b00000000;
        if (top < 8) attr |= 0b01000000;
        screenAttrs[left + (SCREEN_CHAR_WIDTH * y)] = attr;
    }
}

void fillScreen(char pattern) {
    memset(screen, pattern, SCREEN_BUFFER_SIZE);
}

void fillScreenAttrs(char pattern) {
    int attrOffset;

    for ( attrOffset = 0; attrOffset < ATTRS_BUFFER_SIZE; attrOffset++ )
    {
        screenAttrs[attrOffset] = pattern;
    }
}
