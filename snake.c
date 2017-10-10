#include "snake.h"
#include "snakedata.h"
#include "maps.h"
#include <string.h>

enum
{
    SnakeMaxLength = MapWidth*MapHeight,
    SnakeMinLength = 2
};

#define snakeTag_literal {'S','n','a','k','e','D','a','t','a'}
static const char snakeTag[] = snakeTag_literal;

typedef struct 
{
    size_t len;
    Pos body[SnakeMaxLength];
} Snake;

typedef struct 
{
    char tag[sizeof(snakeTag)];
    Snake snake;
    Direction sdirect;//apply to snake after update()
    size_t slen;//apply to snake after update()
} SnakeData;

static SnakeData _snakeData = {
    .tag = snakeTag_literal,
    .snake.len = SnakeMinLength,
    .sdirect = Invalid,
    .slen = SnakeMinLength
    };
static Snake* snake = &_snakeData.snake;
static Direction* sdirect = &_snakeData.sdirect;
static size_t* slen = &_snakeData.slen;

//internal forward declaration
static Direction vecDirect(Pos forward, Pos backward);
static bool oppositeDirect(Direction one, Direction other);
static bool validSnakeData(SnakeData* data);

/* snake */

Direction currentDirection(void)
{
    return vecDirect(snake->body[0],snake->body[1]);
}

bool turnTo(Direction direct)
{
    bool turned = false;
    if(!oppositeDirect(direct,currentDirection()))
    {
        *sdirect = direct;
        turned = true;
    }
    return turned;
}

size_t currentLength(void)
{
    return snake->len;
}

bool isVictorious(void)
{
    return snake->len == SnakeMaxLength;
}

void growUp(void)
{
    *slen = snake->len +1;
}

// include head
bool onSnake(Pos pos)
{
    return equalPos(snakeHead(),pos) || onSnakeBody(pos);
}

// except head
bool onSnakeBody(Pos pos)
{
    bool on = false;
    for(int i=1; i < snake->len; ++i)
    {
        if(equalPos(snake->body[i],pos))
        {
            on = true;
            break;
        }
    }
    return on;
}

Pos snakeHead(void)
{
    return snake->body[0];
}


void updateSnake(void)
{
    //update length
    snake->len = *slen;
    //move
    for(size_t ri = snake->len-1;ri;--ri)
    {
        snake->body[ri] = snake->body[ri-1];
    }
    //turn
    if(*sdirect==Invalid)
    {
        *sdirect = currentDirection();
    }
    switch(*sdirect)
    {
    case Up:
        snake->body[0].y--;
    break;
    case Down:
        snake->body[0].y++;
    break;
    case Left:
        snake->body[0].x--;
    break;
    case Right:
        snake->body[0].x++;
    break;
    default:
    break;
    }
    if(mapModel()==Boundless)
    {
        snake->body[0].x = (snake->body[0].x - 1)%MapWidth + 1;
        snake->body[0].y = (snake->body[0].y - 1)%MapHeight + 1;
    }
}

void drawSnake(char buffer[BufferSize])
{
    buffer[mapPosToOffset(snake->body[0])] = '@';
    for(size_t i=1;i < snake->len;++i)
    {
        buffer[mapPosToOffset(snake->body[i])] = '*';
    }
}

bool initSnake(void* data)
{
    bool ok = false;
    if(data==&_snakeData)
    {
        ok = true;
    }
    else if(data==NULL)//default
    {
        snake->len = *slen = SnakeMinLength;
        *sdirect = Up;
        snake->body[0] = (Pos){MapWidth/2,MapHeight/2};
        snake->body[1] = snake->body[0];
        snake->body[1].y++;
        ok = true;
    }
    else
    {
        if(validSnakeData(data))
        {
            memcpy(&_snakeData,data,sizeof(_snakeData));
            ok = true;
        }
    }
    return ok;
}

/* snake data */

size_t sizeofSnakeData(void)
{
    return sizeof(_snakeData);
}

const void* snakeData(void)
{
    return &_snakeData;
}

/* internal */

Direction vecDirect(Pos forward, Pos backward)
{
    Direction direct = Invalid;
    if(forward.x > backward.x && forward.y == backward.y)
    {
        direct = Right;
    }
    else if(forward.x < backward.x && forward.y == backward.y)
    {
        direct = Left;
    }
    else if(forward.y > backward.y && forward.x == backward.x)
    {
        direct = Up;
    }
    else if(forward.y < backward.y && forward.x == backward.x)
    {
        direct = Down;
    }
    return direct;
}

bool oppositeDirect(Direction one, Direction other)
{
    bool isOpposite = false;
    switch(one)
    {
    case Up:
        if(other==Down) isOpposite = true;
    break;
    case Down:
        if(other==Up) isOpposite = true;
    break;
    case Left:
        if(other==Right) isOpposite = true;
    break;
    case Right:
        if(other==Left) isOpposite = true;
    break;
    default: //invalid direction is opposite to all
        isOpposite = true;
    break;
    }
    return isOpposite;
}

bool validSnakeData(SnakeData* data)
{
    bool isValid = false;
    if(memcmp(data->tag,snakeTag,sizeof(snakeTag))
          && !oppositeDirect(data->sdirect,
                            vecDirect(data->snake.body[0],
                                     data->snake.body[1])))
    {
        //TODO: check continuity & no interleave
        isValid = true;
    }
    return isValid;
}
