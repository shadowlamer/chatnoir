//
// Created by sl on 11.07.2019.
//

#ifndef YRGB2019_QUOTES_H
#define YRGB2019_QUOTES_H

const Quote quotes[] = {
        {
                .mask = EVT_MASK_TROUBLE,
                .prob=30,
                .quote="ќпределенно, этот мир совсем\n"
                       "обезумел."
        },
        {
                .mask = EVT_MASK_TROUBLE,
                .prob=30,
                .quote="я чувствовал себ€ неважно, но не\n"
                       "был так болен, как следовало бы\n"
                       "после всего пережитого."
        },
        {
                .mask = EVT_MASK_TROUBLE,
                .prob=30,
                .quote="Ќеудачный день. » недел€.\n"
                       "» мес€ц. » год. » жизнь."
        },
        {
                .mask = EVT_MASK_MOVEMENT,
                .prob=30,
                .quote="Ќоги дл€ мен€ - первое дело.\n"
                       "Ёто первое, что € увидел, когда\n"
                       "родилс€."
        },
        {
                .mask = EVT_MASK_REPEAT,
                .prob=100,
                .quote="» еще раз."
        },
        {
                .mask = EVT_MASK_REPEAT,
                .prob=100,
                .quote="ѕовторение - мать учени€."
        },
        {
                .mask = EVT_MOVE_FORWARD,
                .prob=150,
                .quote="я шагнул вперед"
        },
        {
                .mask = EVT_MOVE_BACKWARD,
                .prob=150,
                .quote="я шагнул назад"
        },
        {
                .mask = EVT_TURN_RIGHT,
                .prob=150,
                .quote="я повернулс€ направо"
        },
        {
                .mask = EVT_TURN_LEFT,
                .prob=150,
                .quote="я повернулс€ налево"
        },
        {
                .mask = EVT_STUCK_FORWARD,
                .prob=150,
                .quote="я ткнулс€ лицом в стену"
        },
        {
                .mask = EVT_STUCK_BACKWARD,
                .prob=150,
                .quote="я уперс€ спиной в стену"
        },
};

#define EVT_NUM_QUOTES 12

#endif //YRGB2019_QUOTES_H
