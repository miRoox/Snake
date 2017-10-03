#ifndef ID_H
#define ID_H

#include <stddef.h>
#include <stdbool.h>

struct _Id;
typedef struct _Id Id;

#undef typeId
#undef _typeId
#define typeId(type) _typeId(type)
#define _typeId(type) (makeIdFromName(#type, sizeof(#type)/sizeof(char)))

extern Id* makeIdFromName(const char name[], size_t size);
extern Id* copyId(const Id* other);
extern void deleteId(Id* id);
extern size_t sizeofId(const Id* id);
extern bool sameId(const Id* x, const Id* y);

#endif //ID_H