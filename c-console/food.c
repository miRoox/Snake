#include "food.h"
#include "snake.h"
#include <stdlib.h>

static Pos _food;

static inline void randomFood(void);

Pos foodPos(void)
{
    return _food;
}

bool initFood(const Pos* food)
{
    bool ok = false;
    if(food==NULL)
    {
        randomFood();
        ok = true;
    }
    else if(proposalPos(*food))
    {
        _food.x = food->x;
        _food.y = food->y;
        ok = true;
    }
    return ok;
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
