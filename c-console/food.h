#ifndef FOOD_H
#define FOOD_H

#include "maps.h"
#include <stdbool.h>

extern Pos foodPos(void);
extern bool initFood(const Pos* food);
extern void updateFood(void);
extern void drawFood(char buffer[BufferSize]);

#endif //FOOD_H