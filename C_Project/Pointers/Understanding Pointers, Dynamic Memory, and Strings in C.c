#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const int size = 100;

    char *str_ptr = (char *)calloc(size,sizeof(char));
    
    strcpy(str_ptr,"Hello World");

    printf("%s",str_ptr);

    free(str_ptr);
    return 0;
}