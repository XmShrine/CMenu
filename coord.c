#include "coord.h"

void* AutoMalloc(coord* crd) {
    if (crd->bank==NULL) {
        return malloc(1);
    }
    return crd->bank;
}

void* DeepCopy(void* beg, unsigned long len) {
    void* poi = malloc(len);
    ShallowCopy(beg, len, poi, len);
    return poi;
}

void* ShallowRemove(void* beg, unsigned long len) {
    for (long i=0; i<len; i++) {
        *(char*)(beg+i) = 0;
    }
    return 0;
}

void* ShallowCopy(void* beg, unsigned long len, void* obeg, unsigned long olen) {
    if (olen==0) {
        olen = len;
    }
    if (olen>len) {
        olen = len;
    }
    for (long i=0; i<olen; i++) {
        *(char*)(obeg+i) = *(char*)(beg+i);
    }
    return 0;
}

void* Coord(unsigned long lent) {
    coord* ins = malloc(sizeof(coord));
    ins->self = ins;
    ins->bank = NULL;
    ins->ends = NULL;
    ins->lent = lent;
    return ins;
}

void* CoordClear(coord* crd) {
    if (crd->bank!=NULL) {
        free(crd->bank);
    }
    crd->bank = crd->ends = NULL;
    return 0;
}

void* CoordLength(coord* crd) {
    return (void*)((crd->ends-crd->bank)/crd->lent);
}

void* CoordEmpty(coord* crd) {
    if (crd->bank == NULL || crd->ends == NULL || crd->lent == 0) {
        return (void*)1;
    }
    return (void*)0;
}

void* CoordPushFront(coord* crd) {
    CoordAppend(crd, 0);
    return 0;
}

void* CoordPushBack(coord* crd) {
    CoordAppend(crd, (unsigned long)CoordLength(crd));
    return 0;
}

void* CoordAppend(coord* crd, unsigned long whr) {
    unsigned long siz = ((unsigned long)CoordLength(crd)+1)*crd->lent;
    void*  poi = NULL;
    void*  poe = NULL;
    crd->bank = realloc(AutoMalloc(crd), siz);
    crd->ends = crd->bank + siz;
    for (void* i=crd->bank+whr*crd->lent; i<=crd->ends-crd->lent; i+=crd->lent) {
        poe = DeepCopy(i, crd->lent);
        if (poi!=NULL) {
            ShallowCopy(poi, crd->lent, i, crd->lent);
            free(poi);
            poi = NULL;
        }
        poi = poe;
    }
    return 0;
}

void* CoordRemove(coord* crd, unsigned long whr) {
    for (void* i=CoordArrget(crd, whr); i<=crd->ends; i+=crd->lent) {
        ShallowCopy(i+crd->lent, crd->lent, i, crd->lent);
    }
    unsigned long siz = ((unsigned long)CoordLength(crd)-1)*crd->lent;
    crd->bank = realloc(AutoMalloc(crd), siz);
    crd->ends = crd->bank + siz;
    return 0;
}

void* CoordArrget(coord* crd, unsigned long whr) {
    return crd->bank+whr*crd->lent;
}

void* CoordBarget(coord* crd, unsigned long whr) {
    return CoordArrget(crd, (unsigned long)CoordLength(crd)-whr-1);
}
