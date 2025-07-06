#include<stdio.h>

#define SIZE 5

int front = -1;
int Rear = -1;

void enqueue(int arr[SIZE],int data);
int dequeue(int arr[SIZE]);
void show(int arr[SIZE]);


int main(){

    int arr[SIZE];

    enqueue(arr,1);
    enqueue(arr,2);
    enqueue(arr,3);
    enqueue(arr,4);
    enqueue(arr,5);
    
    show(arr);

    dequeue(arr);
    show(arr);
    dequeue(arr);
    show(arr);
    dequeue(arr);
    show(arr);

    return 0;
}

void enqueue(int arr[SIZE],int data){

    if (Rear >= SIZE)
    {
        printf("Queque is full!");

    }
    else{

        if (front == -1)
        {
            front++;
        }
        
        Rear++;

        arr[Rear] = data;
    }
} 

int dequeue(int arr[SIZE]){
    if (front > Rear)
    {
        printf("Queque is empty !");
    }else{
        int a = arr[front];
        front++;
        return a;
    }
}
void show(int arr[SIZE])
{
    if(front < Rear){

        printf("Front -> ");
        int i;
        for (i = front; i < Rear; i++)
        {
            printf("%d <-",arr[i]);
        }
        printf("%d",arr[i]);
        printf("\n");
    }
}
 
