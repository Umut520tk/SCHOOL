#include<stdio.h>
#include <string.h>

int main(){
    FILE *file = fopen("Mytxt.txt","r");
    char str[100];

    while (fscanf(file,"%[^\n]\n",str) == 1)
    {
        printf("%s\n",str);
    }
    fseek(file,0,SEEK_SET);
    fprintf(file,"Hello World");
    fclose(file);
    return 0;
}