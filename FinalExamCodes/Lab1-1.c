#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("Please Enter 5 number: \n");

    int *a = (int *)malloc(5 * sizeof(int));
    int *b = (int *)malloc(4 * sizeof(int));

    for (size_t i = 0; i < 5; i++)
    {
        printf("%d = ",i + 1);
        scanf("%d",&a[i]);
    }
    
    for (size_t i = 0; i < 4; i++)
    {
        b[i] = a[i + 1] - a[i];
    }

    printf("Original Array: \n");

    for (size_t i = 0; i < 5; i++)
    {
        printf("a[%d] = %d\n",i,a[i]);
    }
    
    printf("Difference Array: \n");

    for (size_t i = 0; i < 4; i++)
    {
        printf("b[%d] = %d\n",i,b[i]);
    }

    return 0;
}