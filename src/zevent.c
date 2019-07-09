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
                    pushSentence("� ������ ������");
                    break;
                case EVT_STUCK_FORWARD:
                    pushSentence("� ������� ����� � �����");
                    break;
                case EVT_MOVE_BACKWARD:
                    pushSentence("� ������ �����");
                    break;
                case EVT_STUCK_BACKWARD:
                    pushSentence("� ������ ������ � �����");
                    break;
                case EVT_TURN_LEFT:
                    pushSentence("� ���������� ������");
                    break;
                case EVT_TURN_RIGHT:
                    pushSentence("� ���������� �������");
                    break;
                case EVT_LOOK_NORTH:
                    pushSentence("� ���������� �� �����");
                    break;
                case EVT_LOOK_SOUTH:
                    pushSentence("� ���������� �� ��");
                    break;
                case EVT_LOOK_EAST:
                    pushSentence("� ���������� �� ������");
                    break;
                case EVT_LOOK_WEST:
                    pushSentence("� ���������� �� �����");
                    break;
            }
            break;
        case EVT_SECOND_TIME:
            pushSentence("� ��� ���");
            break;
        case EVT_THIRD_TIME:
            pushSentence("� ���");
            break;
        case EVT_MANY_TIMES:
            switch (event) {
                case EVT_MOVE_FORWARD:
                    pushSentence("� ������ ����� � ����� ������");
                    break;
                case EVT_STUCK_FORWARD:
                    pushSentence("� ������� ������� ����� �����");
                    break;
                case EVT_MOVE_BACKWARD:
                    pushSentence("� ������� � �������");
                    break;
                case EVT_STUCK_BACKWARD:
                    pushSentence("� �������� � �����");
                    break;
                case EVT_TURN_LEFT:
                case EVT_TURN_RIGHT:
                    pushSentence("� �������� �� �����");
                    break;
            }
            break;
    }
}

char *describeEvent() {
    return popSentence();
}