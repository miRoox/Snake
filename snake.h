#ifndef SNAKE_H
#define SNAKE_H

#include "maps.h"

#include <stdlib.h>
#include <stdbool.h>

struct _Snake;
typedef struct _Snake Snake;

typedef enum
{
    Invalid = 0,
    Up,
    Down,
    Left,
    Right
} Direction;

extern Direction currentDirection(void);
extern bool turnTo(Direction direct);
extern size_t currentLength(void);
extern bool isVictorious(void);
extern void growUp(void);
extern bool onSnake(Pos pos);
extern bool onSnakeBody(Pos pos);
extern Pos snakeHead(void);
extern bool initSnake(void* data);
extern void update(void);
extern void drawSnake(char buffer[BufferSize]);


#endif //SNAKE_H