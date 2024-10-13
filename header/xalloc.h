/* xalloc header */

#include <stdlib.h>
#include <stddef.h>
#ifndef _YVALS.H
#include "yvals.h"
#endif

#define _SIZE_BLOCK 512
#define _SIZE_CELL  ((sizeof(_cell) + _MEMBND & ~_MEMBND) - _CELL_OFF)
#define _CELL_OFF   (sizeof(size_t) + _MEMBND & ~_MEMBND)

typedef struct _cell {
    size_t _size;
    struct _cell *_next;
} _cell;

typedef struct {
    _cell **_tail_ptr;
    _cell *_head;
} _alloc_table;

void *_getmem(size_t);
extern _alloc_table _alloc_data;
