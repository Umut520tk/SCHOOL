#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void matrixCalculations(int [][5],int [][5],int [][5],int  );

void main()
{
    int size = 5;
    int matrix1[size][size];
    int matrix2[size][size];
    int output[size][size];

    srand(time(NULL));

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            matrix1[i][j] = (rand() % 10) + 1;
            matrix2[i][j] = (rand() % 10) + 1;
        }
    }

    printf("Matrix1: \n");

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            printf("%2d ",matrix1[i][j]);
        }
        puts("");
    }
    
    printf("\n\nMatrix1: \n");

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            printf("%2d ",matrix2[i][j]);
        }
        puts("");
    }

    matrixCalculations(matrix1,matrix2,output,size);

    printf("\n\nMatrix1 * Matrix2 Calculation Result: \n");

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            printf("%4d ",output[i][j]);
        }
        puts("");
    }

}
void matrixCalculations(int matrix1[][5],int matrix2[][5],int output[][5],int size )
{
    int calc = 0;
    for (size_t i = 0; i < size; i++)
    {
       for (size_t j = 0; j < size; j++)
       {
            for (size_t k = 0; k < size; k++)
            {
                calc += matrix1[i][k] * matrix2[k][j];
            }
            output[i][j] = calc;
            calc = 0;
       }       
    }
    
}