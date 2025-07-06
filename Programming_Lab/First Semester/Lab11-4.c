#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int main(){

    int array[5][5];
    int sum[5] = {0};

    srand(time(NULL));


    printf("The content of the array is: \n");
    for (size_t i = 0; i <= 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            array[i][j] = rand() % 10;
            sum[i] += array[i][j];
            printf("%4d",array[i][j]);
        }
        printf("\n");
    }

    printf("The sum of row is : \n");

    for (size_t i = 0; i <= 5; i++)
    {
        printf("%4d",i == 5 ? 0 : sum[i]);
    }
    
    return 1;
}


