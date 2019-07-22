//
// Created by sl on 12.07.2019.
//

#include <sound.h>
#include <tools.h>

#define OUT_BIT_PATTERN 0b00011001
#define CHANNELS_NUM 1

__sfr __at 0xfe soundPort;

SoundChannel channels[CHANNELS_NUM];

void initChannel(unsigned char c) {
    channels[c].freqCounter = 0;
    channels[c].timeCounter = 0;
    channels[c].tone = 0xff;
    channels[c].melody = null;
}

void initSound() {
    unsigned char c;
    for (c = 0; c < CHANNELS_NUM; c++) {
        initChannel(c);
    }
}

void processSound() {
    unsigned char out = 0;
    for (;;) {
        out ^= 0b00011001;
        soundPort = out;
    }
}

void play(unsigned char channel, Note *melody) {
    channels[channel].melody = melody;
}

unsigned char isPlaying(unsigned char channel){
    return channels[channel].melody != null;
}