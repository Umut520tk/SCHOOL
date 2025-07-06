#include <stdio.h>
#include <math.h>

int isPalindrome(int);

void main(){
    int number;

    printf("Please write some numbers : ");
    scanf("%d",&number);


    printf("\n%d",isPalindrome(number));


}

int isPalindrome(int num)
{
    int remainder = 0, original = num, reversed;


    while (num != 0)
    {
        remainder = num % 10;
        reversed = reversed * 10 + remainder;
        num /= 10;
    }
    
    return reversed == original;


}