#include<stdio.h>

int main(){
    int length_myArray;
    int count = 0;
    int myint;


    printf("Input the number of elements to be stored in the array : ");
    scanf("%d",&length_myArray);
    
    int MyArray[length_myArray];

    printf("\n Please write elements: \n");
    for (int i = 0; i < length_myArray; i++)
    {
        printf("element - %d :",i);
        scanf("%d" ,&MyArray[i]);
    }

    for (int i = 0; i < length_myArray - 1; i++)
    {
        myint = MyArray[i];
        for (int j = i + 1; j < length_myArray; j++)
        {
            if (myint == MyArray[j])
            {
                count++;
            }
        }
    }
    
    printf("Total number of duplicate elements found in the array is :%d",count);
    return 1;
}