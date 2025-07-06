#include<stdio.h>
#include<math.h>
int main()
{
    int number;
    int digit;
    int right = 0;
    int left = 0;
    printf("Please enter a number to find it is palindrome or not: ");
    scanf("%d",&number);

    int numberDigit = (int)(log10(number))+1;
    if (numberDigit % 2 == 0)
    {
        for (int i = 0; i < numberDigit/2; i++)
        {
            digit = (int)(number%(int)pow(10,i + 1))/pow(10,i);
            right += digit * (int)pow(10,i);
        }
        int k = 0;
        for (int i = numberDigit/2; i > 0; i--)
        {
            digit = (int)(number%(int)pow(10,i+numberDigit/2))/pow(10,i+numberDigit/2-1);
            left += digit * (int)pow(10,k);
            k++;
        }
            if (right == left)
        {
        printf("Your number is a palindrome");
        }
        else
        {
        printf("Your number is not a palindrome");
        }
    }
    else{
        for (int i = 0; i < (numberDigit-1)/2; i++)
        {
            digit = (int)(number%(int)pow(10,i + 1))/pow(10,i);
            right += digit * (int)pow(10,i);
        }
        int k = 0;
        for (int i = (numberDigit-1)/2; i > 0; i--)
        {
            digit = (int)(number%(int)pow(10,i+1+(numberDigit-1)/2))/pow(10,i+(numberDigit-1)/2);
            left += digit * (int)pow(10,k);
            k++;
        }
        if (right == left)
        {
        printf("Your number is a palindrome");
        }
        else
        {
        printf("Your number is not a palindrome");
        }
    }

    return 0;

}