/* strrchr function: locate last occurrence of character in string */

#include <string.h>

char *strrchr(const char *s, int c) {
    // find last occurrence of c in char s[]
	const char ch = c;
	const char *sc;
    
    // check another char
	for (sc = NULL; ; ++s) {
		if (*s == ch)
			sc = s;
		if (*s == '\0')
			return (char *) sc;
	}
}
