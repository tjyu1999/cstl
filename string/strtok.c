/* strtok function: split string into tokens */

#include <string.h>

char *strtok(char *s1, const char *s2) {
    char *s_begin;
    char *s_end;
    static char *s_save = ""; // for safety
    
    s_begin = s1 ? s1 : s_save;
    s_begin += strspn(s_begin, s2);
    if (*s_begin == '\0') {
        s_save = ""; // for safety
        return NULL;
    }
    
    s_end = s_begin + strcspn(s_begin, s2);
    if (*s_end != '\0')
        *s_end++ = '\0';
    s_save = s_end;
    
    return s_begin;
}
