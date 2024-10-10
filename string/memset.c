/* memset function: fill block of memory */

#include <string.h>

void *memset(void *s, int c, size_t n) {
    const unsigned char uc = c;
    unsigned char *su = (unsigned char *)s;
    
    for (; 0 < n; ++su, --n)
        *su = uc;
    
    return s;
}
