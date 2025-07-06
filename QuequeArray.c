#include<stdio.h>

#define SIZE 10

int Enqueue(int data);   
int Dequeue();
void printQueue();

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
int Enqueue(int data){
    if (rear - front < 0 && rear != -1)
    {
        return -1;
    }
    else if (front == -1){
        front++;
    }

    rear++;

    queque[rear] = data; 
    return 1;
}
int Dequeue(){
    if (rear - front < 0 && front != -1)
    {
        return -1;
    }

    int data = queque[front];
    front++;
    return data;
}
void printQueue(){
    if (front == -1 || front > rear)
    {
        front = -1;
        rear = -1;
        return;
    }
    printf("<");
    int i;
    for(i=0;i < rear - front; i++)
    {
        printf("%d - ",queque[i + front]);   
    }
    printf("%d",queque[i + front]);   
    printf("<\n");
}
