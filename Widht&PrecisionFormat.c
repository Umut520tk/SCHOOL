#include<stdio.h>
#include<stdlib.h>

int main(){
    char *str = (char *)calloc(100,sizeof(char));
    char str2[100];
    double num = 123.34565;
    double num2=0;
    sprintf(str,"Hello World This is my Number: %3.3lf",num);
    
    FILE *file_ptr = fopen("Mytxt.txt","r");

    while(fgets(str,100,file_ptr) != NULL){
        sscanf(str,"%[^:]: %lf",str2,&num2);
        printf("%s: %.3lf\n",str2,num2);
    }

    fseek(file_ptr,0,SEEK_SET);

    while (fscanf(file_ptr,"%[^:]: %lf",str2,&num2) == 2)
    {
        printf("%s: %.3lf",str2,num2);
    }

    fclose(file_ptr);
    free(str);
    return 0;
}