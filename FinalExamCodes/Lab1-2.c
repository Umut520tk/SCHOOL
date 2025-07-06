#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50

int main(){

    srand(time(NULL));

    int *a = (int *)calloc(SIZE,sizeof(int));
    int *b = (int *)calloc(SIZE,sizeof(int));

    printf("Array A:\n");
    for (size_t i = 0; i < SIZE; i++)
    {
        a[i] = rand() % 10; 
        printf("a[%d] = %d\n",i,a[i]);   
    }
    
    printf("\nArray B:\n");
    for (size_t i = 0; i < SIZE; i++)
    {
        b[i] = a[49 - i]; 
        printf("b[%d] = %d\n",i,b[i]);   
    }


    return 0;
}