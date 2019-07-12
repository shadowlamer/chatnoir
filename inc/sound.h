//
// Created by sl on 12.07.2019.
//

#ifndef YRGB2019_SOUND_H
#define YRGB2019_SOUND_H

typedef struct {
    unsigned int time;
    unsigned char tone;
} Note;

typedef struct {
    unsigned char freqCounter;
    unsigned int timeCounter;
    unsigned char tone;
    Note *melody;
} SoundChannel;

void processSound();
void initSound();
void play(unsigned char channel, Note *melody);
unsigned char isPlaying(unsigned char channel);

#endif //YRGB2019_SOUND_H
