//
// Created by sl on 11.07.2019.
//

#ifndef YRGB2019_QUOTES_H
#define YRGB2019_QUOTES_H

const Quote quotes[] = {
        {
                .mask = EVT_MASK_TROUBLE,
                .prob=30,
                .quote="�����������, ���� ��� ������\n"
                       "��������."
        },
        {
                .mask = EVT_MASK_TROUBLE,
                .prob=30,
                .quote="� ���������� ���� �������, �� ��\n"
                       "��� ��� �����, ��� ��������� ��\n"
                       "����� ����� ����������."
        },
        {
                .mask = EVT_MASK_TROUBLE,
                .prob=30,
                .quote="��������� ����. � ������.\n"
                       "� �����. � ���. � �����."
        },
        {
                .mask = EVT_MASK_MOVEMENT,
                .prob=30,
                .quote="���� ��� ���� - ������ ����.\n"
                       "��� ������, ��� � ������, �����\n"
                       "�������."
        },
        {
                .mask = EVT_MASK_REPEAT,
                .prob=100,
                .quote="� ��� ���."
        },
        {
                .mask = EVT_MASK_REPEAT,
                .prob=100,
                .quote="���������� - ���� ������."
        },
        {
                .mask = EVT_MOVE_FORWARD,
                .prob=150,
                .quote="� ������ ������"
        },
        {
                .mask = EVT_MOVE_BACKWARD,
                .prob=150,
                .quote="� ������ �����"
        },
        {
                .mask = EVT_TURN_RIGHT,
                .prob=150,
                .quote="� ���������� �������"
        },
        {
                .mask = EVT_TURN_LEFT,
                .prob=150,
                .quote="� ���������� ������"
        },
        {
                .mask = EVT_STUCK_FORWARD,
                .prob=150,
                .quote="� ������� ����� � �����"
        },
        {
                .mask = EVT_STUCK_BACKWARD,
                .prob=150,
                .quote="� ������ ������ � �����"
        },
};

#define EVT_NUM_QUOTES 12

#endif //YRGB2019_QUOTES_H
