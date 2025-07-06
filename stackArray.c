#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

#define MAX 10

char stack[MAX];
int top = -1;

void push(int value);
bool isEmpty();
char pop();

int main() {
    char str[] = "REVERSED";

    for (size_t i = 0; i < strlen(str); i++)
    {
        push(str[i]);
    }
    while (!isEmpty())
    {
        printf("%c",pop());
    }
    return 0;
}
void push(int value){
    if (top == MAX - 1)
    {
        printf("Error: Stack overflow!\n");
        return;
    }
    
    stack[++top] = value;
}
char pop(){
    if (top == -1)
    {
        printf("Error: Stack underflow!\n");
        return -1;
    }
    return stack[top--];
}
bool isEmpty(){
    if (top == -1)
    {
        return true;
    }
    else return false;    
}