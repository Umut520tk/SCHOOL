#include<stdio.h>

#define SIZE 10

void Enqueue(int data);   
int Dequeue();
void printQueue();
int isFull();
int isEmpty();

int rear = -1, front = -1;
int queque[SIZE];

int main(){
    int out;

    while (1)
    {
        printQueue();
        printf("1: For Enqueue \t 2: For Dequeue \n Which operation do you want to do : ");
        scanf("%d",&out);

        switch (out)
        {
        case 1:
            printf("Please enter your Value:");
            scanf("%d",&out);
            Enqueue(out);
            break;
        case 2:
            printf("Value Dequeued: %d\n",Dequeue());
            break;
        default:
            printf("Please enter valid input!!\n");
            break;
        }
    }
    

    return 0;
}
void Enqueue(int data){
    if(isFull() == 1) printf("\n Queue is full!\n");
    else{
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        queque[rear] = data;
    }
}

int Dequeue(){

    if (isEmpty() == 1){ printf("\n Queue is Empty! \n");}
    else
    {
        int data = queque[front];
        
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else{
            front = (front + 1) % SIZE;
        }
        return data;
    }
    return -1;
}
void printQueue(){
    if (isEmpty()!= 1)
    {
        printf("\nFront -->");
        int i;
        for(i=front;i != rear; i = (i+1) % SIZE)
        {
            printf("%d - ",queque[i]);   
        }
        printf("%d",queque[i]);   
        printf("<-- Rear\n");
    }
}
int isFull(){
    if(front == rear + 1 || (front == 0 && rear == SIZE - 1)){
        return 1;
    }
    return 0;
}
int isEmpty(){
    if(front == -1){
        return 1;
    }
    return 0;
}