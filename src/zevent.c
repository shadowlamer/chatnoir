//
// Created by sl on 09.07.19.
//

#include <zevent.h>
#include <quotes.h>

unsigned int lastEvent;

char *sentences[EVT_MAX_SENTENCES];
unsigned char sentenceCounter;

void pushSentence(char *s) {
    if (s == null) return;
    if (sentenceCounter < EVT_MAX_SENTENCES) {
        sentences[sentenceCounter] = s;
        sentenceCounter++;
    }
}

char *popSentence() {
    if (sentenceCounter > 0) {
        sentenceCounter--;
        return sentences[sentenceCounter];
    }
    return null;
}

void initEvents(){
    sentenceCounter = 0;
}

void castEvent(unsigned int event){

    if (lastEvent == event) { //set repeat flag
        event |= EVT_MASK_REPEAT;
    } else {
        lastEvent = event;
    }

    pushSentence(findQuote(event));

    if (!sentenceCounter) //clear last event if not reported
        lastEvent = EVT_IDLE;

}

char *describeEvent() {
    return popSentence();
}

char *findQuote(unsigned int event) {
    unsigned char i;
    for (i = 0; i < EVT_NUM_QUOTES; i++) {
        if (((quotes[i].mask & event) == quotes[i].mask) && (rand() < quotes[i].prob))
            return quotes[i].quote;
    }
    return null;
}