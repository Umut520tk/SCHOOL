#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int array1[5][5];
    int array2[5][5];

    srand(time(NULL));

    printf("The content of array 1 is:\n");
    for (size_t i = 0; i < 5; i++)
    {
        printf("\t");
        for (size_t j = 0; j < 5; j++)
        {
            array1[i][j] = rand() % 10;   
            printf("%4d", array1[i][j]); 
        }
        printf("\n");
    }
    printf("\nThe content of array 1 is:\n");
    for (size_t i = 0; i < 5; i++)
    {
        printf("\t");
        for (size_t j = 0; j < 5; j++)
        {
            array2[i][j] = rand() % 10;   
            printf("%4d", array2[i][j]); 
        }
        printf("\n");
    }


    printf("\nThe sum of array1 and array2 is:\n");
    for (size_t i = 0; i < 5; i++)
    {
        printf("\t");
        for (size_t j = 0; j < 5; j++)
        {   
            printf("%4d", array2[i][j] + array1[i][j]); 
        }
        printf("\n");
    }





 return 0;   
}