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

const char

void fillScreen(char pattern);
void fillScreenAttrs(char pattern);
void drawColumnOfAttrs(unsigned char left, unsigned char top, unsigned char bottom);
void renderWalls();
void calculateWalls();

void main()
{
    screen = (char *)SCREEN_BUFFER_START;
    screenAttrs = (char *)ATTRS_BUFFER_START;

    fillScreen((char)0xaa);
    calculateWalls();
    renderWalls();
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
        wallRenderBuffer[i] = map[0][i];
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
