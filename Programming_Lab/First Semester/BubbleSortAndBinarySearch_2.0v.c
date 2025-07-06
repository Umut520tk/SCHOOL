#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define SIZE 10

int binarySearch(int [],size_t size,int Key);
int bubbleSort(int [],size_t size);

int main()
{
    int array[SIZE];
    int Key = 0;
    int randNumber;
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++)
    {
        randNumber = rand() % SIZE;
        for (int j = 0; j < i; j++)
        {
            if (randNumber == array[j])
            {
                randNumber = rand() % SIZE;
                j = -1;
            }
        }
        array[i] = randNumber;
    }
    
    bubbleSort(array,SIZE);
    for (size_t i = 0; i < SIZE; i++)
    {
        printf("array[%zu] = %d ",i,array[i]);
    }
    
    
    puts("");
    while (Key!=-1)
    {
        printf("Enter a number to search (-1 to exit) : ");
        scanf("%d",&Key);
        binarySearch(array,SIZE,Key);
    }
    

    return 0;
}

int bubbleSort(int array[],size_t size){

    int control;

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (array[j] > array[j+1])
            {
                control = array[j+1];
                array[j+1] = array[j];
                array[j] = control; 
            }
        }
    }
}

int binarySearch(int array[],size_t size, int Key)
{
    int upperBond = size - 1;
    int lowerBond = 0;

    int middle = (upperBond + lowerBond) / 2;

    while (upperBond >= lowerBond)
    {
        if (array[middle] == Key) 
        {
            printf("Key found at index %d\n",middle);
            return middle;    
        }
        else if (array[middle] > Key) upperBond = middle - 1;
        else lowerBond = middle + 1;

        middle = (upperBond + lowerBond) / 2;

    }
    
    printf("Key not found\n");
    return -1;
    
}


