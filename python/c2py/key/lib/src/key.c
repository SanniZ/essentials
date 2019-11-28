#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PWD "passwd123"
#define KEY "TxT-00-^&^-_-key"

char* get_key(char *pwd) {
    if (!strcmp(pwd, PWD))
        return KEY;
    else
	    return NULL;
}
