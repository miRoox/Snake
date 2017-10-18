#include "maps.h"
#include "utils.h"
#include <string.h>

extern inline bool equalPos(Pos one, Pos other);
extern inline bool proposalPos(Pos pos);

//internal
//valid area include border and space
static inline bool validPos(Pos pos)
{
    return pos.x<=MapWidth+1 && pos.y<=MapHeight+1;
}

//draw map to buffer
void drawMap(char buffer[BufferSize])
{
    static bool inited = false;
    static char _buffer[BufferSize];
    if(!inited) //lazy initialize
    {
        size_t offset = 0;
        _buffer[offset++] = '#';
        for(size_t i=0;i<MapWidth;++i)
        {
            _buffer[offset++] = '#';
        }
        _buffer[offset++] = '#';
        _buffer[offset++] = '\n';
        for(size_t i=0;i<MapHeight;++i)
        {
            _buffer[offset++] = '#';
            for(size_t j=0;j<MapWidth;++j)
            {
                _buffer[offset++] = ' ';
            }
            _buffer[offset++] = '#';
            _buffer[offset++] = '\n';
        }
        _buffer[offset++] = '#';
        for(size_t i=0;i<MapWidth;++i)
        {
            _buffer[offset++] = '#';
        }
        _buffer[offset++] = '#';
        _buffer[offset++] = '\n';
        _buffer[offset] = '\0';

        inited = true;
    }

    strncpy(buffer,_buffer,BufferSize);
}

//map position to buffer offset
unsigned int mapPosToOffset(Pos pos)
{
    assert(validPos(pos));
    return (pos.x)+(2*sizeof(char)+MapWidth+sizeof(char))*pos.y;
}

//map buffer offset to position
Pos mapOffsetToPos(unsigned int offset)
{
    assert(offset<BufferSize);
    Pos pos = {0,0};
    pos.x = offset%(2*sizeof(char)+MapWidth+sizeof(char));
    pos.y = offset/(2*sizeof(char)+MapWidth+sizeof(char));
    assert(validPos(pos));
    return pos;
}

/* map model */
static MapModel _model;

void setMapModel(MapModel model)
{
    _model = model;
}

MapModel mapModel(void)
{
    return _model;
}
