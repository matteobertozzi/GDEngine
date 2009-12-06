#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "strings.h"

char *gdStringTrim (char *s) {
    char *p;

    if (s == NULL)
        return(NULL);

    for (p = s; *p != '\0' && strchr(" \n\r\t", *p) != NULL; ++p);

    if (*p != '\0') {
        memmove(s, p, strlen(p) + 1);
        for (p = s + strlen(s) - 1; strchr(" \n\r\t", *p) != NULL; --p);
        p[1] = '\0';
        return(s);
    }

    s[0] = '\0';
    return(NULL);
}

