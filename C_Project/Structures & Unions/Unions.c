#include<stdio.h>
#include<string.h>

union myUnions{
    int myNum;
    char myChar[25];
};
int main() {
    union myUnions un1;
    un1.myNum = 12;
    printf("Mynum : %d, Mychar: %s",un1.myNum,un1.myChar);
    strcpy(un1.myChar,"Hello World");
    printf("Mynum : %d, Mychar: %s",un1.myNum,un1.myChar);
    return 0;
}
