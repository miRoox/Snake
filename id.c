#include "id.h"
#include "errormsg.h"
#include <stdlib.h>
#include <string.h>

struct _Id
{
    size_t sz;
    char name[];
};

Id* makeIdFromName(const char name[], size_t size)
{
    Id* id = malloc(sizeof(size) + size * sizeof(char));
    if(id==NULL)
    {
        fatal("malloc failed: %s",strerror(errno));
        return NULL;
    }
    id->sz = size;
    strncpy(id->name,name,size);
    return id;
}

Id* copyId(const Id* other)
{
    Id* id = malloc(sizeof(other->sz) + other->sz * sizeof(char));
    if(id==NULL)
    {
        fatal("malloc failed: %s",strerror(errno));
        return NULL;
    }
    if(other==NULL)
    {
        free(id);
        return NULL;
    }
    id->sz = other->sz;
    strncpy(id->name,other->name,other->sz);
    return id;
}

void deleteId(Id* id)
{
    free(id);
}

size_t sizeofId(const Id* id)
{
    if(id==NULL)
        return 0;
    return sizeof(id->sz) + id->sz * sizeof(char);
}

bool sameId(const Id* x, const Id* y)
{
    if(x==NULL || y==NULL)
        return false;
    else if(x->sz != y->sz)
        return false;
    else
        return strncmp(x->name,y->name,x->sz)==0;
}
