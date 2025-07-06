#include<stdio.h>

int main(){
    int length_myArray;
    int count = 0;
    int myint;

    // Determine length of myArray
    printf("Input the number of elements to be stored in the array : ");
    scanf("%d",&length_myArray);

    int myArray[length_myArray];

    // get elelement form user
    printf("\n Please write elements (only positive integers): \n");
    for (int i = 0; i < length_myArray; i++)
    {
        printf("element - %d :",i);
        scanf("%d" ,&myArray[i]);
    }

    // Find how many duplicate numbers exist and replace the second number of each duplicate with -1.
    for (int i = 0; i < length_myArray - 1; i++)
    {
        myint = myArray[i];
        for (int j = i + 1; j < length_myArray; j++)
        {
            if (myint == myArray[j])
            {
                myArray[j] = -1;
                count++;
            }
        }
        
    }
    
    // Copy data to MyFinalArray, excluding any -1 values.
    int myFinalArray[length_myArray - count];
    int j = 0;
    for (int i = 0; i < length_myArray; i++)
    {
        if (myArray[i] != -1)
        {
            myFinalArray[j] = myArray[i];
            j++;
        }
    }

    printf("Array with duplicates removed :");
    for (int i = 0; i < length_myArray - count; i++)
    {
        printf("%d ",myFinalArray[i]);
    }

    return 1;
}