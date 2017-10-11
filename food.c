#include "food.h"
#include "snake.h"
#include <stdlib.h>

static Pos _food;

static inline void randomFood(void);

Pos foodPos(void)
{
    return _food;
}

void initFood(const Pos* food)
{
    if(food==NULL)
    {
        randomFood();
    }
    else
    {
        _food.x = food->x;
        _food.y = food->y;
    }
}

void updateFood(void)
{
    if(equalPos(_food,snakeHead()))
    {
        randomFood();
    }
}

void drawFood(char buffer[BufferSize])
{
    buffer[mapPosToOffset(_food)] = 'O';
}

/* internal */

void randomFood(void)
{
    do {
        _food.x = rand()%MapWidth + 1;
        _food.y = rand()%MapHeight + 1;
    }
    while(onSnake(_food));
}
