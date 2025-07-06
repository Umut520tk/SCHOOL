#include <stdio.h>

int main(){

    FILE *fptr = fopen("data.txt","w");

    char str[100];

    printf("Please enter your text: ");
    scanf("%[^\n]",str);

    fprintf(fptr,"%s",str);

    fclose(fptr);

    FILE *fptr_in = fopen("data.txt","r");

    char str_in[100];
    
    fscanf(fptr_in,"%[^\n]",str_in);

    printf("Your text: %s",str_in);

    fclose(fptr_in);
}