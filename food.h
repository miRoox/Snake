#ifndef FOOD_H
#define FOOD_H

#include "maps.h"

extern Pos foodPos(void);
extern void initFood(const Pos* food);
extern void updateFood(void);
extern void drawFood(char buffer[BufferSize]);

#endif //FOOD_H