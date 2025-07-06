#include <stdio.h>
#include <stdlib.h>

#define SIZE 7

int front = -1, rear = -1;

int enQueque(int arr[],int data);
int deQueque(int arr[],int *data);
int isFull();
int isEmpty();
void display(int arr[]);

int main(){
    int *arr = (int *)calloc(SIZE,sizeof(int));
    int choice = 0;
    
    while (choice != 3)
    {
        puts("(1) -> EnQueque: ");
        puts("(2) -> DeQueque: ");
        puts("(3) -> Exit: ");
        printf("\nPlease Enter your Choice: ");
        scanf("%d",&choice);

        int data;

        switch (choice)
        {
        case 1:
            printf("\nPlease enter your data: ");
            scanf("%d",&data);
            if (enQueque(arr,data))
            {
                printf("\n %d -> Enqued\n",data);
            }
            else{
                printf("\nCircular Quequeq is Full !\n");
            }
        
            break;
        case 2:
            if (deQueque(arr,&data))
            {
                printf("\n%d -> Dequed\n",data);
            }
            else {
                printf("\n Queque is Empty !\n");
            }
        case 3:
            break;
        default:
            printf("Please enter some valid data");
            choice = 0;
            break;
        }
        display(arr);
    }
    

    /*
    for (size_t i = 1; i <= SIZE; i++)
    {
        enQueque(arr,i);
    }
    printf("\nBEFORE OPERATIONS\n");
    display(arr);

    int data = 0;;
    for (size_t i = 1; i <= 4; i++)
    {
        deQueque(arr,&data);
        enQueque(arr,data);
        deQueque(arr,&data);
    }

    printf("\nAFTER OPERATIONS\n");
    display(arr);
    */
    return 0;
}

int isFull(){
    if ((front == rear + 1) || (front == 0  && rear == SIZE - 1)) return 1;
    return 0;
}
int isEmpty(){
    if (front == -1)return 1;
    return 0;
}

int enQueque(int arr[],int data){
    if (isFull()) return 0;
    if (front == -1)front = 0;
    
    rear = (rear + 1) % SIZE;

    arr[rear] = data;

    return 1;
}

int deQueque(int arr[],int *data){

    if(isEmpty()) return 0;

    *data = arr[front];

    if (front == rear)
    {
        front = -1;
        rear = -1;
    }else{
        front = (front + 1) % SIZE;
    }
    return 1;
}

void display(int arr[]){
    if (!isEmpty())
    {
        printf("\nCircular Queque is: \n\n\tFront -> ");
        int i;
        for (i = front; i != rear; i = (i + 1) % SIZE)
        {
            printf("%d -> ",arr[i]);
        }
        printf("%d <- Rear\n",arr[i]);
    }
}