/* free function: deallocate memory block */

#include "xalloc.h"

void free(void *ptr) {
    if (ptr == NULL)
        return;
    
    _cell *q;
    q = (_cell*)((char*)ptr - _CELL_OFF);
    if (q->_size < _SIZE_CELL || (q->_size & _MEMBND) != 0)
        return;

    if (_alloc_data._head == NULL || q < _alloc_data._head) { // insert at the head of the list
        q->_next = _alloc_data._head;
        _alloc_data._head = q;
    }
    else { // scan the insertion point
        _cell *qp;
        char *qpp;
        
        for (qp = _alloc_data._head; qp->_next != NULL && qp->_next < q;)
            qp = qp->_next;
        qpp = (char *)qp + _CELL_OFF + qp->_size;
        
        if ((char *)q < qpp)
            return;
        else if ((char *)q == qpp) {
            qp->_size += _CELL_OFF + q->_size;
            q = qp;
        }
        else { // splice q after qp and resume scan with q
            q->_next = qp->_next;
            qp->_next = q;
            _alloc_data._tail_ptr = &qp->_next;
        }
    }
    
    if (q->_next && (char *)q + _CELL_OFF + q->_size == (char *)q->_next) { // merge q and q->_next
        q->_size += _CELL_OFF + q->_next->_size;
	q->_next = q->_next->_next;
    }
}
