#include <stdio.h>

#define SIZE 5

void enqueue(int [],int data);
int dequeue(int [],int *);

int isFull();
int isEmpty();

void display(int []);

int front = -1, rear = -1;

int main(){
    int arr[SIZE] = {0};

    int choice = 0;
    while (choice != 4)
    {

        printf("Which Operation Do you Want to Do ?\n");
        printf(" (1): Enqueque\n");
        printf(" (2): Dequeque\n");
        printf(" (3): Display\n");
        printf(" (4): Close\n");

        scanf("%d",&choice);

        int data;
        switch (choice)
        {
        case 1:
            if (!isFull(arr))
            {
                printf("\nPlease Enter Number: ");
                scanf("%d",&data);
                enqueue(arr,data);
            }
            else printf("\nQueque is Full !!\n");

            break;
        case 2:
            if (dequeue(arr,&data)) printf("\n Deleted Element -> %d \n",data);
            break;
        case 3:
            display(arr);
            break;
        case 4:
            break;
        default:
            printf("\nPlease Enter Valid Choice!\n");
            break;
        }
    }

    return 0;
}

void enqueue(int arr[],int data){

    if (!isFull())
    {
        if (front == -1) front = 0;
        
        rear = (rear + 1) % SIZE;
        arr[rear] = data;

        printf("\n Inserted -> %d \n",data);
    }
    else printf("Circular Queque is Full!");
}
int dequeue(int arr[],int *data){
    if (isEmpty())
    {
        printf("\nCircular Queque is Empty!\n");
        return 0;
    }
    else{
        *data = arr[front];
        front = (front + 1) % SIZE;

        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        
        return 1;
    }
}
int isFull(){
    if ((front == rear + 1) || (front == 0 && rear == SIZE -1))return 1;
    else return 0;
}
int isEmpty(){
    if (front == -1) return 1;
    else return 0;
}
void display(int arr[]){
    int i;

    if (isEmpty())printf("\n Circular Queque is Empty ! \n");
    else{
        printf("\nFront -> ");
        for (i = front; i != rear;i = (i + 1) % SIZE)
        {
          printf("%d -> ",arr[i]);           
        }
        printf("%d ",arr[i]);
        printf("<- Rear\n");
    }
}