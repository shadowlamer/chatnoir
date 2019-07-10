//
// Created by sl on 11.07.19.
//

#ifndef YRGB2019_TRIG_H
#define YRGB2019_TRIG_H

#define SIN(x) sine[x]
#define COS(x) sine[(x + 64) & 0xff]

extern const char sine[256];

#endif //YRGB2019_TRIG_H
