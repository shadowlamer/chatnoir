//
// Created by sl on 09.07.19.
//

#include <zevent.h>

unsigned char lastEvent;
unsigned char repetitionCounter;

char *sentences[EVT_MAX_SENTENCES];
unsigned char sentenceCounter;

void pushSentence(char *s) {
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
      repetitionCounter = 0;
}

void castEvent(unsigned char event){

    if (lastEvent == event) {
        if (repetitionCounter < EVT_NUM_REPETITIONS)
            repetitionCounter++;
    } else {
        lastEvent = event;
        repetitionCounter = 0;
    }

    switch (repetitionCounter) {
        case EVT_FIRST_TIME:
            switch (event) {
                case EVT_IDLE:
                    pushSentence("");
                    break;
                case EVT_MOVE_FORWARD:
                    pushSentence("Я шагнул вперед");
                    break;
                case EVT_STUCK_FORWARD:
                    pushSentence("Я ткнулся лицом в стену");
                    break;
                case EVT_MOVE_BACKWARD:
                    pushSentence("Я шагнул назад");
                    break;
                case EVT_STUCK_BACKWARD:
                    pushSentence("Я уперся спиной в стену");
                    break;
                case EVT_TURN_LEFT:
                    pushSentence("Я повернулся налево");
                    break;
                case EVT_TURN_RIGHT:
                    pushSentence("Я повернулся направо");
                    break;
                case EVT_LOOK_NORTH:
                    pushSentence("Я повернулся на север");
                    break;
                case EVT_LOOK_SOUTH:
                    pushSentence("Я повернулся на юг");
                    break;
                case EVT_LOOK_EAST:
                    pushSentence("Я повернулся на восток");
                    break;
                case EVT_LOOK_WEST:
                    pushSentence("Я повернулся на запад");
                    break;
            }
            break;
        case EVT_SECOND_TIME:
            pushSentence("И еще раз");
            break;
        case EVT_THIRD_TIME:
            pushSentence("И еще");
            break;
        case EVT_MANY_TIMES:
            switch (event) {
                case EVT_MOVE_FORWARD:
                    pushSentence("Я упрямо шагал и шагал вперед");
                    break;
                case EVT_STUCK_FORWARD:
                    pushSentence("Я пытался пробить телом стену");
                    break;
                case EVT_MOVE_BACKWARD:
                    pushSentence("Я пятился и пятился");
                    break;
                case EVT_STUCK_BACKWARD:
                    pushSentence("Я вжимался в стену");
                    break;
                case EVT_TURN_LEFT:
                case EVT_TURN_RIGHT:
                    pushSentence("Я вертелся на месте");
                    break;
            }
            break;
    }
}

char *describeEvent() {
    return popSentence();
}