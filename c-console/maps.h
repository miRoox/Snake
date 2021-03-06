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
    BufferSize = (2*sizeof(char)+MapWidth+sizeof(char))*(2*sizeof(char)+MapHeight)+1
};

typedef enum
{
    Boundless,
    Limitary
} MapModel;

inline bool equalPos(Pos one, Pos other)
{
    return one.x==other.x && one.y==other.y;
}

//proposal area doesnot include border
inline bool proposalPos(Pos pos)
{
    return pos.x>0 && pos.x<=MapWidth
           && pos.y>0 && pos.y<=MapHeight;
}

extern void drawMap(char buffer[BufferSize]);
extern unsigned int mapPosToOffset(Pos pos);
extern Pos mapOffsetToPos(unsigned int offset);
extern void setMapModel(MapModel model);
extern MapModel mapModel(void);

#endif //MAPS_H