#include<stdio.h>

#define COLUMN_COUNT 3
#define ROW_COUNT 3


int main(){
    int Matrix[ROW_COUNT][COLUMN_COUNT];
    int count = 1;



    printf("Enter elements in the matrix : \n");

    // Displaying all data
    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            printf("element - [%d],[%d] : ",i,j);
            scanf("%d",&Matrix[i][j]);
            puts("");
        }
        
    }

    printf("Columns 1 , 2 , 3\n");
    // Displaying the matrix as a table
    for (int i = 0; i < ROW_COUNT; i++)
    {
        printf("Row ");
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            printf(" %3d ",Matrix[i][j]);
        }
        puts("");
    }

    return 1;
}