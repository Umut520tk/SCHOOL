#include <stdio.h>

#define SIZE 5

// Stack
int stack[SIZE];
int top = -1;

int push(int );
int pop(int *);
int isStackFull();
int isStackEmpty();
void stackDisplay();

// Queque
int queque[SIZE];
int front = -1, rear = -1;

int enQueque(int );
int deQueque(int *);
int isQuequeFull();
int isQuequeEmpty();
void quequeDisplay();

int main(){

    int data;

    printf("\t\nCREATION OF QUEQUE\n");
    for (size_t i = 0; i < SIZE; i++)
    {
        enQueque(2*i + 1);
    }
    quequeDisplay();

    printf("\t\nINSERTION TO THE STACK\n");
    for (size_t i = 0; i < SIZE; i++)
    {
        deQueque(&data);
        push(data);
    }
    stackDisplay();

    printf("\t\nREINSERTION TO THE QUEQUE\n");
    for (size_t i = 0; i < SIZE; i++)
    {
        pop(&data);
        enQueque(data);
    }
    quequeDisplay();

    return 0;
}
// --------------------------------------------------------------------
// Stack
int push(int data){

    if (isStackFull()){
        printf("\nStack is Full !\n");
        return 0;
    }
    else {

        top++;
        stack[top] = data;

        printf("\n Pushed to the Stack -> %d\n",data);
        return 1;
    }
}
int pop(int *data){

    if (isStackEmpty())
    {
        printf("\n Stack is Empty !\n");
        return 0;
    }
    else {
        *data = stack[top];
        top--;
        
        printf("\n Popped from Stack -> %d\n",*data);
        return 1;
    }
}
int isStackFull(){
    if (top == SIZE - 1)return 1;
    return 0;
}
int isStackEmpty(){
    if (top == -1)return 1;
    return  0;
}
void stackDisplay(){
    if (!isStackEmpty())
    {
        printf("\n\tSTACK:\n");
        for (int i = top; i > -1; i--)
        {
            printf("\t        %d\n",stack[i]);
        }
    }
}
// --------------------------------------------------------------------
// Queque
int enQueque(int data){
    if (isQuequeFull())
    {
        printf("\nQueque is Full !\n");
        return 0;
    }
    
    if (front == -1)front = 0;

    rear = (rear + 1) % SIZE;
    queque[rear] = data;
    printf("\n Enquequed -> %d\n",data);
    return 1;
}
int deQueque(int *data){
    if (isQuequeEmpty())
    {
        printf("\nQueque is Empty !\n");
        return 0;
    }
    
    *data = queque[front];
    front++;

    if (front == rear + 1)
    {
        front = -1;
        rear = -1;
    }
    printf("\n Dequequed -> %d\n",*data);
    return 1;
}
int isQuequeFull(){
    if(rear == SIZE -1) return 1;
    return 0;
}
int isQuequeEmpty(){

    if (front == -1) return 1;
    return 0;
}
void quequeDisplay(){
    if (!isQuequeEmpty())
    {
        int i;
        printf("\n\tQUEQUE:\n\t       Front-> ");
        for (i = front; i != rear; i++)
        {
            printf("%d -> ",queque[i]);
        }
        printf("%d <- Rear\n",queque[i]);
    }
    
}