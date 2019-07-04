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

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

char *screen;
char *screenAttrs;
char wallRenderBuffer[WALL_BUFFER_SIZE];
const char map[MAP_HEIGHT][MAP_WIDTH] = {
  {0,0,1,1,1,1,0,0},
  {0,0,1,0,0,1,0,0},
  {1,1,1,0,0,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,1,1,0,0,1,1,1},
  {0,0,1,0,0,1,0,0},
  {0,0,1,1,1,1,0,0}
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
                         -90, -92, -94, -96, -98,-100,-102,-104,-106,-107,-109, -11,   0,-112,-113,-115,
                        -116,-117,-118,-120,-121,-122,-122,-123,-124,-125,-125,-126,-126,-126,-127,-127,
                        -127,-127,-127,-127,-127,-126,-126,-126,-125,-125,-124,-123,-122,-122,-121,-120,
                        -118,-117,-116,-115,-113,-112,-111,-109,-107,-106,-104,-102,-100, -98, -96, -94,
                         -92, -90, -88, -85, -83, -81, -78, -76, -73, -71, -68, -65, -63, -60, -57, -54,
                         -51, -49, -46, -43, -40, -37, -34, -31, -28, -25, -22, -19, -16, -12,  -9,  -6 };

__sfr __banked __at 0xf7fe joystickKeysPort;

long int playerX;
long int playerY;

void fillScreen(char pattern);
void fillScreenAttrs(char pattern);
void drawColumnOfAttrs(unsigned char left, unsigned char top, unsigned char bottom);
void renderWalls();
void calculateWalls();
long int traceRay(long int myX, long int myY, unsigned char angle);
char getMapAt(long int x, long int y);

void main()
{
    screen = (char *)SCREEN_BUFFER_START;
    screenAttrs = (char *)ATTRS_BUFFER_START;

    fillScreen((char)0xaa);

    playerX = (4 << 8);
    playerY = (4 << 8);


    while (1) {

        if (joystickKeysPort & 0b00001000) {
            playerX += 100;
        }
        if (joystickKeysPort & 0b00000100) {
            playerX -= 100;
        }
        if (joystickKeysPort & 0b00000010) {
            playerY += 100;
        }
        if (joystickKeysPort & 0b00000001) {
            playerY -= 100;
        }

        calculateWalls();
        fillScreenAttrs(0b00111000);
        renderWalls();
    }
}

long int traceRay(long int myX, long int myY, unsigned char angle) {
    long int x = myX;
    long int y = myY;
    long int ray = 0;
    while (getMapAt(x, y) == 0 && ray < 10000) {
        x += sine[angle + 64];
        y += sine[angle];
        ray += 256;
    }
    return ray;
}

char getMapAt(long int x, long int y){
    unsigned char mapX = ( x >> 8 ) & 0xff;
    unsigned char mapY = ( y >> 8 ) & 0xff;
    return map[mapY][mapX];
}


void renderWalls() {
    int i;
    for (i=0; i<SCREEN_CHAR_WIDTH; i++) {
        drawColumnOfAttrs(i, wallRenderBuffer[i], wallRenderBuffer[i]);
    }
}

void calculateWalls() {
    int i;
    for (i=0; i<SCREEN_CHAR_WIDTH; i++) {
        wallRenderBuffer[i] = (traceRay(playerX, playerY, i) >> 8) & 0xff;
    }
}

void drawColumnOfAttrs(unsigned char left, unsigned char top, unsigned char bottom) {
    int position;
    char height = SCREEN_CHAR_HEIGHT - top - bottom;

    position = (top * SCREEN_CHAR_WIDTH) + left;

    for (height; height > 0; height-- ){
        screenAttrs[position] = (char)0b11111111;
        position+=SCREEN_CHAR_WIDTH;
    }
}

void fillScreen(char pattern) {
    int screenOffset;

    for ( screenOffset = 0; screenOffset < SCREEN_BUFFER_SIZE; screenOffset++ )
    {
        screen[screenOffset] = pattern;
    }
}

void fillScreenAttrs(char pattern) {
    int attrOffset;

    for ( attrOffset = 0; attrOffset < ATTRS_BUFFER_SIZE; attrOffset++ )
    {
        screenAttrs[attrOffset] = pattern;
    }
}
