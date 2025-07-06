#include<stdio.h>

int main(){
    int num;
    int count = 0;

    printf("please write an integers to find factor count of it : "),
    scanf("%d",&num);

    for (int i = 1; i <= num; i++)
    {
        if (num % i == 0)
        {
            count++;
        }
        
    }
    
    printf("Factorial of %d = %d",num,count);

    return 0;
}