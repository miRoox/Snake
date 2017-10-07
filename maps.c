#include "maps.h"
#include "utils.h"
#include <string.h>

//internal
//valid area include border and space
static bool validPos(Pos pos)
{
    return pos.x<=MapWidth+1 && pos.y<=MapHeight+1;
}

//draw map to buffer
void drawMap(char buffer[BufferSize])
{
    static bool inited = false;
    static char _buffer[BufferSize];
    if(inited)
    {
        strncpy(buffer,_buffer,BufferSize);
    }
    else //lazy initialize
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
            _buffer[offset++] = '-';
        }
        _buffer[offset++] = '#';
        _buffer[offset++] = '\n';
        _buffer[offset] = '\0';

        inited = true;
    }
}

//map position to buffer offset
unsigned int mapPosToOffset(Pos pos)
{
    assert(pos.x<=MapWidth+1);
    assert(pos.y<=MapHeight+1);
    return (pos.x)+(2*sizeof('#')+MapWidth+sizeof('\n'))*pos.y;
}

//map buffer offset to position
Pos mapOffsetToPos(unsigned int offset)
{
    assert(offset<BufferSize);
    Pos pos = {0,0};
    pos.x = offset%(2*sizeof('#')+MapWidth+sizeof('\n'));
    pos.y = offset/(2*sizeof('#')+MapWidth+sizeof('\n'));
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
