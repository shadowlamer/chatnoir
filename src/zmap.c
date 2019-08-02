//
// Created by sl on 11.07.19.
//

#include <zmap.h>

#include <sprites/bush0.h>
#include <sprites/ground0.h>

char wallRenderBuffer[WALL_BUFFER_SIZE];

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

const unsigned char wallSizes[8] = {4, 3, 2, 2, 1, 1, 1, 1};
const unsigned int  wallSpriteOffsets[8] = {0, 512, 848, 1040, 1200, 1264, 1312, 1344};

unsigned int playerX;
unsigned int playerY;
unsigned char playerAngle;

unsigned int traceRay(unsigned int myX, unsigned int myY, unsigned char angle) {
    unsigned int x = myX;
    unsigned int y = myY;
    unsigned char effAngle = angle + playerAngle - (SCREEN_CHAR_WIDTH / 2);
    unsigned int ray = 0;
    unsigned int sin = SIN(effAngle);
    unsigned int cos = COS(effAngle);
    unsigned char screenCoef = SIN((angle * 2) + 32);
    while (getMapAt(x, y) == 0 && ray < 0x0a) {
        x += cos;
        y += sin;
        ray++;
    }
    ray = (ray * screenCoef) >> 7;
    if (ray > 7) ray = 7;
    return ray;
}

char getMapAt(unsigned int x, unsigned int y){
    unsigned char mapX = ( x >> 8 ) & 0xff;
    unsigned char mapY = ( y >> 8 ) & 0xff;
    return map[mapY][mapX];
}


void renderWalls() {
    unsigned char i;
    unsigned char wallDistance;
    unsigned char wallSize;
    for (i=0; i<SCREEN_CHAR_WIDTH; ) {
        wallDistance = wallRenderBuffer[i];
        wallSize = wallSizes[wallDistance];
        drawSpriteColumn(i, wallDistance, wallSize, bush0 + wallSpriteOffsets[wallDistance]);
        i+=wallSize;
    }
}


void calculateWalls() {
    int i;
    for (i=0; i<SCREEN_CHAR_WIDTH; i++) {
        wallRenderBuffer[i] = traceRay(playerX, playerY, i);
    }
}

void drawSpriteColumn(unsigned char left, unsigned char distance, unsigned char width, unsigned char *spite) {
    __asm
    ld      ix,     #0x0002
    add     ix,     sp              ;Set IX to first param

    ld      bc,     #0x0000
    push    bc                      ;Allocate 2 bytes in stack (ix-3 and ix-4)

    ld      hl,     #_ground0
    ld      a,      0 (ix)
    and     a,      #0x07
    add     a,      l
    ld      l,      a
    push    hl                      ;Save ground sprite addr in stack (ix-5 and ix-6)

    ld      a,      2 (ix)
    add     a,      0 (ix)
    sub     a,      #SCREEN_CHAR_WIDTH
    jr      c,      width_ok
    ld      -3 (ix),a               ;Save sprite overflow for last column
    neg
    add     a,      2 (ix)
    ld      2 (ix), a               ;Fix last column width
    width_ok:

    ld      de,     #_screen
    ld      h,      #0x00
    ld      l,      0 (ix)
    add     hl,     de
    ex      de,     hl              ;Set DE to the top of the column

    ld      l,      3 (ix)
    ld      h,      4 (ix)

;************************* Draw top part ********************
    ld      a,      #0x40
    cycle_top:
    push af
    push de

    ld      a,      e
    rrca
    rrca
    rrca
    rrca
    rrca
    and     a,      #0x07
    sub     a,      1 (ix)
    jr      c,      draw_bg_top

    ld      c,      2 (ix)
    ldir
    ld      a,      -3 (ix)         ;Load sprite overflow
    or      a                       ;Compare with zero
    jr      z,      end_draw_top
    add     a,      l               ;Shift sprite pointer when necessary
    ld      l,      a
    jr      end_draw_top

    draw_bg_top:

    push    hl
    ld      hl, #RANDOM_BUFFER_START - #SCREEN_BUFFER_START
    ld      a,  (_playerAngle)
    add     a,  0 (ix)
    ld      c,  a
    add     hl, bc
    add     hl, de
    xor     a
    cp      (hl)
    ld      a,  #0x01
    jr      nc,  sky_star
    xor     a
    sky_star:
    ld      c,      2 (ix)
    pop     hl

    draw_top_bg_loop:
    ld      (de),   a
    inc     de
    dec     c
    jr      nz,     draw_top_bg_loop

    end_draw_top:

    pop     de
    ld      a,      #SCREEN_CHAR_WIDTH
    add     a,      e
    ld      e,      a
    ld      a,      d
    adc     a,      #0x00
    ld      d,      a               ;Move to next screen position

    pop      af
    dec     a
    jr      nz,     cycle_top

    ld      a,      #0x08
    sub     a,      1 (ix)
    ld      1 (ix), a

    ;************************* Draw bottom part ********************
    ld      a,      #0x40
    cycle_bottom:
    push af
    push de

    ld      a,      e
    rrca
    rrca
    rrca
    rrca
    rrca
    and     a,      #0x07
    sub     a,      1 (ix)
    jr      nc,      draw_bg_bottom

    ld      c,      2 (ix)
    ldir
    ld      a,      -3 (ix)         ;Load sprite overflow
    or      a                       ;Compare with zero
    jr      z,      end_draw_bottom
    add     a,      l               ;Shift sprite pointer when necessary
    ld      l,      a
    jr      end_draw_bottom

    draw_bg_bottom:

    push    hl
    ld      h,      -5 (ix)
    ld      l,      -6 (ix)
    ld      c,      2 (ix)
    ldir
    pop     hl

    end_draw_bottom:

    push    hl
    ld      h,      -5 (ix)
    ld      l,      -6 (ix)
    ld      c,      #0x08
    add     hl,     bc
    ld      -5 (ix),h
    ld      -6 (ix),l
    pop     hl


    pop     de
    ld      a,      #SCREEN_CHAR_WIDTH
    add     a,      e
    ld      e,      a
    ld      a,      d
    adc     a,      #0x00
    ld      d,      a               ;Move to next screen position

    pop      af
    dec     a
    jr      nz,     cycle_bottom

    pop     de
    pop     de                      ;Deallocate space
    __endasm;
}

//void drawSpriteColumn(unsigned char left, unsigned char distance){
//    unsigned char i;
//    unsigned int pos = left;
//    unsigned char width = wallSizes[distance];
//    unsigned char _width = width;
//    unsigned int spritePos = wallSpriteOffsets[distance];
//    unsigned int groundPos;
//    if (( left + width ) > SCREEN_CHAR_WIDTH)
//        _width = SCREEN_CHAR_WIDTH - left;
//    for (i = 0; i < 64; i++) {
//        if (((pos >> 5) & 0x07) >= distance) {
//            memcpy(screen + pos, bush0 + spritePos, _width);
//            spritePos += width;
//        } else {
//            if (RANDOM(pos + playerAngle) > 125)
//                screen[pos] = 0x01;
//            else
//                memset(screen + pos, 0x00, _width);
//        }
//        pos += SCREEN_CHAR_WIDTH;
//    }
//    groundPos = left & 0x07;
//    for (i = 0; i < 64; i++) {
//        if (((pos >> 5) & 0x07) <= (7 - distance)) {
//            memcpy(screen + pos, bush0 + spritePos, _width);
//            spritePos += width;
//        } else {
//            memcpy(screen + pos, ground0 + groundPos, _width);
//        }
//        pos += SCREEN_CHAR_WIDTH;
//        groundPos += 8;
//    }
//}
