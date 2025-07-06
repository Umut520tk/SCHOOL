#include<stdio.h>
#include<stdlib.h>

int main(){
    int size;
    printf("How many Values do you want to assign ?");
    scanf("%d",&size);
    
    int *arr = (int *)malloc(size * sizeof(int));
    printf("Please enter your values: \n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d: ",i);
        scanf("%d",arr + i);
    }
    printf("Your array: ");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ",*(arr + i));
    }
    
    return 0;
}