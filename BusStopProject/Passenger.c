#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUS_LINE_SIZE 6
#define MAX_BUS_STOP 8

typedef struct Luggage
{
    int id;
    struct Passenger *owner;
}Luggage;

typedef struct Passenger{
    int id;
    char line[MAX_BUS_STOP + 1];
    char Start;
    char End;

    struct Luggage luggages[2];
    struct Passenger *next;
}Passenger;

typedef struct Queue{
    Passenger *front;
    Passenger *rear;

}Queue;

Queue* createQueue();
Passenger* createPassenger();
void SelectBusStops(Passenger *);
void enqueue(Queue* q,Passenger* p);
Passenger* dequeue(Queue* q);
void printQueue(Queue* q);

char busStops[16] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
char lines[BUS_LINE_SIZE][MAX_BUS_STOP + 1] = {
                
                    "AEIJKL",
                    "BFEIJNM",
                    "CGKJFEA",
                    "DCGKJNM",
                    "LPOKGCDH",
                    "MNJFGKOP"
                };


                
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

int main(){
    srand(time(NULL));
    Queue *queue = createQueue();

    for (size_t i = 0; i < 15; i++)
    {
        enqueue(queue,createPassenger());
    }

    while (1)
    {    
        printQueue(queue);

        delay(1);    
    
        Passenger* temp = dequeue(queue);
        printf("%c is deleted\n",temp->Start);
        free(temp);
    }
    

    return 0;
}

Queue* createQueue(){
    Queue* newQueue = (Queue *)malloc(sizeof(Queue)); 
    newQueue->front = NULL;
    newQueue->rear = NULL;

    return newQueue;
}

Passenger* createPassenger()
{
    Passenger *newPassenger = (Passenger *)malloc(sizeof(Passenger));
    newPassenger->id = 1 + rand() % 200; 
    newPassenger->next = NULL;
    strcpy(newPassenger->line,lines[rand() % BUS_LINE_SIZE]);

    SelectBusStops(newPassenger);


    return newPassenger;
}

void SelectBusStops(Passenger *passenger)
{
    int rnd = rand() % (strlen(passenger->line) - 1);
    char start = passenger->line[rnd];
    char end;
    if (rnd == strlen(passenger->line) - 2)
    {
        end = passenger->line[strlen(passenger->line)-1];
    }
    else{
        rnd;
        int rnd2 = rand() % (strlen(passenger->line) - rnd - 1) + 1;
        end = passenger->line[rnd2 + rnd];
    }
    
    passenger->Start = start;
    passenger->End = end;
}

void enqueue(Queue* q,Passenger* p)
{

    if (q->rear == NULL)
    {
        q->rear = p;
        q->front = p;
        return;
    }

    q->rear->next = p;
    q->rear = p;

}
void printQueue(Queue* q)
{
    char pass[15];
    int i = 0;
    // Traverse the queue and print each element
    Passenger* temp = q->front;
    while (temp != NULL) {
        pass[i++] = temp->Start;
        temp = temp->next;
    }
    printf("\033[1;1H>");
    for (size_t j = 14; j < -1; j--)
    {
        printf(" %c ",pass[j]);
    }
    
    printf(">\n");
}
Passenger* dequeue(Queue *q){

    if (q->front == NULL)
    {
        printf("Queue is empty!!!");
        return NULL;
    }
    Passenger* temp = q->front;
    q->front = temp->next;

    Passenger* newPassenger = createPassenger();

    enqueue(q,newPassenger);

    return temp;
}