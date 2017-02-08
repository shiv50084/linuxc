#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef POINT_TO_STRING
#define PATH_MAX 1024
void * mymalloc(size_t nbytes)
{
    void *dummy = malloc(nbytes);
    if (!dummy) {
        exit(1);
    }

    return dummy;
}

char *mystrdup(const char *from)
{
    char *tmp;
    int stringlength;

    if (from == NULL || !strlen(from)) {
        tmp = NULL;
    } else {
        stringlength = strlen(from);
        stringlength = (stringlength < PATH_MAX ? stringlength : PATH_MAX);
        tmp = (char *)mymalloc(stringlength + 1);
        strncpy(tmp, from, stringlength);

        /* We must ensure the string always has a NULL terminator.
         * This necessary because strncpy will not append a NULL terminator
         * if the original string is greater than stringlength.
         */
        tmp += stringlength;
        *tmp = '\0';
        tmp -= stringlength;
    }
    return tmp;
}
#endif

int main(int argc, char *argv[])
{
	char *string = "abcdef";
#ifdef POINT_TO_STRING
	char **tmp;
	tmp = &string;
	*tmp = mystrdup(*tmp);
#endif
	printf("string = %s\n", string);
	strcpy(string, "12345");
	printf("string = %s\n", string);

	free(string);
	return 0;
}
