#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PWD "pwd123"
#define KEY "markdown-00-key_"

char* get_md_key(char *pwd) {
    if (!strcmp(pwd, PWD))
        return KEY;
    else
	    return 0;
}
