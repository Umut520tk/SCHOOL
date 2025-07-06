#include<stdio.h>

int main()
{
    int lenght;
    printf("Input the number of elements to store in the array: ");
    scanf("%d",&lenght);

    int MyArray[lenght];

    printf("Please write element: \n");
    for (int i = 0; i < lenght; i++)
    {
        printf("element - %d :",i);
        scanf("%d" ,&MyArray[i]);
    }

    printf("\n The values store into the array are: ");
    for (int i = 0; i < lenght; i++)
    {
        printf("%d ",MyArray[i]);
    }
    
    printf("\n The values store into the array in reverse are : ");

    for (int i = lenght - 1; i >= 0; i--)
    {
        printf("%d ",MyArray[i]);
    }
    return 1;
}