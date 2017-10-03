#include "variant.h"
#include "errormsg.h"
#include <stdlib.h>
#include <string.h>

typedef char byte;
static const char VariantTag[] = {'V','a','r'};

/* data layout
variant tag ,
type id ,
size ,
data
*/

void* _internVariantCast(Id* type, size_t size, const Variant var)
{
    const byte* ptr = var;
    void* ans = NULL;
    if(var==NULL)
    {
        goto ret;
    }
    if(memcmp((const char*)ptr,VariantTag,sizeof(VariantTag))!=0)
    {
        goto ret;
    }
    ptr += sizeof(VariantTag);
    if(!sameId((const Id*)ptr,type))
    {
        goto ret;
    }
    ptr += sizeofId(type);
    if(*(const size_t*)ptr != size)
    {
        goto ret;
    }
    ptr += sizeof(size);
    ans = malloc(size);
    memcpy(ans,ptr,size);
ret:
    deleteId(type);
    return ans;
}

Variant _internToVariant(Id* type, size_t size, const void* ptr)
{
    Variant ans = malloc(sizeof(VariantTag) + sizeofId(type) 
                         + sizeof(size) + size);
    byte* ansptr = ans;
    if(ans==NULL)
    {
        fatal("malloc failed: %s",strerror(errno));
        goto ret;
    }
    if(ptr==NULL)
    {
        free(ans);
        goto ret;
    }
    memcpy(ansptr,VariantTag,sizeof(VariantTag));
    ansptr += sizeof(VariantTag);
    memcpy(ansptr,type,sizeofId(type));
    ansptr += sizeofId(type);
    memcpy(ansptr,&size,sizeof(size));
    ansptr += sizeof(size);
    memcpy(ansptr,ptr,size);
ret:
    deleteId(type);
    return ans;
}
