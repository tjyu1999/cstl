/* memchr function: locate character in block of memory */

#include <string.h>

void *memchr(const void *s, int c, size_t n) {
    const unsigned char uc = c;
    const unsigned char *su = (const unsigned char *) s;
    
    for (;  0 < n; ++su, --n) {
        if (*su == uc)
            return (void *) su;
    }
    
    return NULL;    
}
