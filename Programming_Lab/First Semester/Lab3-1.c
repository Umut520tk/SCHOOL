#include<stdio.h>
int main()
{
    int a,b,c;
    printf("Please write your number to find multiplaciton of a ,b and c is odd or even :\n");
    printf("(a) :");
    scanf("%d",&a);
    printf("\n");
    printf("(b) :");
    scanf("%d",&b);
    printf("\n");
    printf("(c) :");
    scanf("%d",&c);
    printf("\n");


    if((a * b * c)%2 == 0){
        printf("Your multiplication is Even");
    }
    else
    {
        printf("Your multiplication is Odd");
    }
    

    return 0;
}