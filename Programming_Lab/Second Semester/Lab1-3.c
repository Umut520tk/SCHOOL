#include <stdio.h>
#include <stdlib.h>


int main(){
    int index = 0;
    int shifting = 0;
    printf("Plese enter the index number : ");
    scanf("%d", &index);


    while (index > 9 || index < 1)
    {
        printf("Please enter the index number between 1 and 9 : ");
        scanf("%d", &index);
    }

    printf("How mant time do you want shift : ");
    scanf("%d", &shifting);

    int* arr = (int *) malloc(index * sizeof(int)); 
    int* arr_reversed = (int *) malloc(index * sizeof(int)); 


    printf("Original array : ");
    for (size_t i = 0; i < index; i++)
    {
        //arr[i] = i + 1;
        arr[i] = rand() % 9 + 1;
        printf("%i \t",arr[i]);
    }

    printf("\nReversed Array : ");
    for (size_t i = 0; i < index + shifting; i++)
    {
        arr_reversed[i] = arr[i % index];
        printf("%i \t",arr_reversed[i]);
    }
    
    free(arr);
    free(arr_reversed);
}