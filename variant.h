#ifndef VARIANT_H
#define VARIANT_H

#include "id.h"

typedef void* Variant;

#define variantCast(type, var) variantCastWithSize(type, sizeof(type), var)
#define variantCastWithSize(type, size, var) ((type*)_internVariantCast(typeId(type), size, var))

#define toVariant(type, ptr) toVariantWithSize(type, sizeof(type), ptr)
#define toVariantWithSize(type, size, ptr) _internToVariant(typeId(type), size, ptr)

extern void* _internVariantCast(Id* type, size_t size, const Variant var);
extern Variant _internToVariant(Id* type, size_t size, const void* ptr);

#endif //VARIANT_H