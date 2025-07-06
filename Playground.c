#include<stdio.h>
#include<string.h>

int main(){
    char str1[100];
    char str2[100];

while (1)
{
    /* code */


    printf("Please Enter Your first String: ");
    scanf("%[^\n]",str1);
    getchar();
    printf("Please Enter Your second String: ");
    scanf("%[^\n]",str2);
    getchar();

    printf("Str1: %s\n",str1);
    printf("Str2: %s\n",str2);

    printf("Compare: %d\n",strcmp(str1,str2));

    printf("lenStr1: %d, lenStr2: %d\n",strlen(str1),strlen(str2));


    strcat(str1,str2);
    printf("str1 + str2: %s\n",str1);


    char *token = strtok(str1," ");
    while (token != NULL)
    {
        printf("First token: %s\n",token);
        token = strtok(NULL," ");
    }
    
}
    return 0;
}