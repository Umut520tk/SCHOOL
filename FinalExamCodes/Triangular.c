#include <stdio.h>

int main(){

    for (int i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            printf("*");
        }
        puts("");
    }
    return 0;
}