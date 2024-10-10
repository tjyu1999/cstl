/* memcpy function: copy block of memory */

#include <string.h>

void *memcpy(void *s1, const void *s2, size_t n) {
    char *su1 = char *s1;
    const char *su2 = const char *s2;
    
    for(; 0 < n; ++su1, ++su2, --n)
        *su1 = *su2;
    
    return s1;
}
