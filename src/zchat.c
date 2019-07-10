//
// Created by sl on 11.07.19.
//

#include <zchat.h>
#include <font1.h>

__at (TEXT_BUFFER_START) char textArea[];
__at (DEFAULT_FONT_START) char font[];

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

void printOneLine(unsigned char *s) {
    unsigned char letter;
    scrollText();
    fillScreenAttrs(0b01000101, 16, 8);
    for (letter=0; letter<SCREEN_CHAR_WIDTH; letter++) {
        if (letter < strlen(s)) {
            if (s[letter] < 0xc0)
                putSprite(letter, 23, font + (s[letter] * 8));
            else
                putSprite(letter, 23, font1 + ((s[letter] - 0xc0) * 8));
        } else
            putSprite(letter, 23, font + (' ' * 8));
    }
}

void scrollText() {
    memcpy(textArea, textArea + SCREEN_CHAR_WIDTH, 0x800 - SCREEN_CHAR_WIDTH);
}
