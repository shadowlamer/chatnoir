//
// Created by sl on 10.07.19.
//

#include <zgraph.h>

__at (SCREEN_BUFFER_START) char screen[];
__at (ATTRS_BUFFER_START)  char screenAttrs[];

void fillScreen(char pattern) {
    memset(screen, pattern, SCREEN_BUFFER_SIZE);
}

void fillScreenAttrs(char pattern, unsigned char startLine, unsigned char lines) {
    memset(screenAttrs + startLine * SCREEN_CHAR_WIDTH, pattern, lines * SCREEN_CHAR_WIDTH);
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
