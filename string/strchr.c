/* strchr function: locate first occurrence of character in string */

#include <string.h>

const char *strchr(const char *s, int c) {
    const char ch = c;
    
    for (; *s != ch; ++s) {
        if (*s == '\0')
            return NULL;
    }
    
    return (char *) s;
}
