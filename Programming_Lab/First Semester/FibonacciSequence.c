#include<stdio.h>

int main(){
    int lenght = 0;
    printf("Please write the lenght of Fibonacci : ");
    scanf("%d",&lenght);


    int array[lenght];

    array[0] = 0;
    array[1] = 1;
    printf("%d ",array[0]);
    printf("%d ",array[1]);
    for (int i = 2; i < lenght; i++)
    {
        array[i] = array[i-1] + array[i-2];
        printf("%d ",array[i]);
    }
    

    return 0;
}