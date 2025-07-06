#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPalindrome(char str[]); 

int main(){
    char str[100];

    while (1)
    {
        printf("Check Palindrome: ");
        scanf("%s",str);

        if (isPalindrome(str) == 1)
        {
            printf("It is A palindrome\n");
        }else printf("It is not palindrome\n");
    }
    
    return 0;
}
int isPalindrome(char str[]){

    int len = strlen(str);
    char stack[len]; 
    int top = -1;

    for (size_t i = 0; i < len; i++)
    {
        stack[++top] = str[i];
    }
    
    for (size_t i = 0; i < len; i++)
    {
        if (str[i] != stack[top--]) return 0;
        
    }
    

    return 1;
}