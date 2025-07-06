#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5


int findMinProduct(int arr[SIZE][SIZE],int size);
void fillMatrix(int arr[SIZE][SIZE],int size);

int main(){
    int arr[SIZE][SIZE];
    int rnd;

    srand(time(NULL));

    fillMatrix(arr,SIZE);

    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            printf("%4d",arr[i][j]);
        }
        puts("");
    }
    


    printf("\nSmallest product is : %4d",findMinProduct(arr,SIZE));

    return 0;
}
void fillMatrix(int arr[SIZE][SIZE],int size){

    int rnd = -1;

    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            rnd = rand() % (size * size * 2) ;
            if (j == 0 && i == 0) arr[i][j] = rnd;
            else {
                for (size_t k = 0; k < (5 * i) + j; k++)
                {
                    if (arr[k / 5][k % 5] == rnd)
                    {
                        j -= 1;
                        break; 
                    }
                    else {
                        arr[i][j] = rnd;
                    }
                }
            }   
        }
    }





}


int findMinProduct(int arr[SIZE][SIZE],int size)
{

    int current = arr[0][0] * arr[0][1];

    for (size_t i = 0; i < size * size; i++)
    {
        for (size_t j = 0; j < size * size; j++)
        {
            if (arr[i / 5][i % 5] * arr[j / 5][j % 5] < current && i != j) current = arr[i / 5][i % 5] * arr[j / 5][j % 5];
        }
    }

    return current;
}