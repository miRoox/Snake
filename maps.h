#ifndef MAPS_H
#define MAPS_H

#include <stdbool.h>

typedef struct
{
    unsigned int x;
    unsigned int y;
} Pos;

enum //map size
{
    MapWidth = 16,
    MapHeight = 16,
    BufferSize = (2*sizeof('|')+MapWidth+sizeof('\n'))*(2*sizeof('-')+MapHeight)+1
};

//proposal area doesnot include border
inline bool proposalPos(Pos pos)
{
    return pos.x>0 && pos.x<=MapWidth
           && pos.y>0 && pos.y<=MapHeight;
}

extern void drawMap(char buffer[BufferSize]);
extern unsigned int mapPosToOffset(Pos pos);
extern Pos mapOffsetToPos(unsigned int offset);

#endif //MAPS_H