/* xalloc header */

#include <stdlib.h>
#include <stddef.h>
#ifndef _YVALS
#include <yvals.h>
#endif

#define SIZE_BLOCK  512
#define SIZE_CELL   ((sizeof(_cell) + MEMBND & ~MEMBND) - CELL_OFFSET)
#define CELL_OFFSET (sizeof(size_t) + MEMBND & ~MEMBND)

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
