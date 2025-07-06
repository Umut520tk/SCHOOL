#include<stdio.h>

struct myStruct
{
    int x;
};


void incrementStruct(struct myStruct,struct myStruct* );

int main(){
    struct myStruct A = {10};
    struct myStruct B = {10};

    incrementStruct(A,&B);

    printf("A: %d",A.x);
    printf("\nB: %d",B.x);
    return 0;   
}
void incrementStruct(struct myStruct A,struct myStruct* B){
    A.x++;
    B->x++;
}