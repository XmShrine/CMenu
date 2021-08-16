#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct _coord_;

typedef struct _coord_ coord;

struct _coord_ {
    void*           self;
    void*           bank;
    void*           ends;
    unsigned long          lent;
};

void* AutoMalloc(coord* crd);

void* DeepCopy(void* beg, unsigned long len);

void* ShallowRemove(void* beg, unsigned long len);

void* ShallowCopy(void* beg, unsigned long len, void* obeg, unsigned long olen);

void* Coord(unsigned long lent);

void* CoordClear(coord* crd);

void* CoordLength(coord* crd);

void* CoordEmpty(coord* crd);

void* CoordPushFront(coord* crd);

void* CoordPushBack(coord* crd);

void* CoordAppend(coord* crd, unsigned long whr);

void* CoordArrget(coord* crd, unsigned long whr);

void* CoordBarget(coord* crd, unsigned long whr);

