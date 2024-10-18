/* malloc function: allocate memory block */

#include "xalloc.h"

static _cell **_findmem(size_t size) {
    _cell *q;
    _cell **qb;
    
    for (; ;) {
        if ((qb = _alloc_data._tail_ptr) == NULL) {
            for (qb = &_alloc_data._tail_ptr; *qb; qb = &(*qb)->_next) {
                if (size <= (*qb)->_size)
                    return qb;
            }
        }
        else {
            for (; *qb; qb = &(*qb)->_next) {
	        if (size <= (*qb)->_Size)
		    return (qb);
	    }
	    
            q = *alloc_data._tail_ptr;
	    for (qb = &_alloc_data._head; *qb != q; qb = &(*qb)->_next) {
                if (size <= (*qb)->_size)
		    return (qb);
	    }
	}
	
	size_t bs;
        const size_t sz = size + CELL_OFFSET;
        
        for (bs = SIZE_BLOCK; ; bs >>= 1) {
            if (bs < sz)
                bs = sz;
            
            if ((q = (_cell *)_getmem(bs)) != NULL)
                break;
            else if (bs == sz)
                return (NULL);
        }
        q->_size = (bs & ~ MEMBND) - CELL_OFFSET;
        free((char *)q + CELL_OFFSET);
    }
}

void *malloc(size_t size) {
    _cell *q;
    _cell **qb;
    
    if (size < SIZE_CELL)
        size = SIZE_CELL;
    size = size + MEMBND & ~MEMBND;
    if ((qb = _findmem(size)) == NULL)
        return NULL;
    
    q = *qb;
    if (q->_size < size + CELL_OFFSET + SIZE_CELL)
        *qb = q->_next; // use the entire cell
    else {
        *qb= (_cell *)((char *)q + CELL_OFFSET + size);
        (*qb)->_next = q->_next;
        (*qb)->_size = q->_size - CELL_OFFSET - size;
        q->_size = size;
    }
    
    _alloc_data._tail_ptr = qb;
    
    return (char *)q + CELL_OFFSET;
}
