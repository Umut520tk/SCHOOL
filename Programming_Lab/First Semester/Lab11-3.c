#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int array[5][5];
    int diognal;

    srand(time(NULL));

    printf("The content of array is:\n");
    for (size_t i = 0; i < 5; i++)
    {
        printf("\t");
        for (size_t j = 0; j < 5; j++)
        {
            array[i][j] = rand() % 10;   
            printf("%4d", array[i][j]); 
        }
        printf("\n");
    }
 
    for (size_t i = 0; i < 5; i++)
    {
        diognal += array[i][i];
    }

    printf("\nThe sum of diognal is: %d\n", diognal);
    

 return 0;   
}