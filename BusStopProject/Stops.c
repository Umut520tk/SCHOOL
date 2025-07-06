#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUS_LINE_SIZE 6
#define MAX_BUS_STOP 8
#define BUSSTOPSIZE 16

int busStopLocation[BUSSTOPSIZE][2] = {
    {2,2}, // A
    {2, 14}, // B
    {2,32}, // C
    {2,50}, // D
    {8,2}, // E
    {8,14}, // F
    {8,32}, // G
    {8,50}, // H
    {14,2}, // I
    {14,14}, // J
    {14,32}, // K
    {14,44}, // L
    {20,8}, // M
    {20,14}, // N
    {20,32}, // O
    {20,44}, // P
};

char busStops[BUSSTOPSIZE] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
char lines[BUS_LINE_SIZE][MAX_BUS_STOP + 1] = {
                
    "AEIJKL",
    "BFEIJNM",
    "CGKJFEA",
    "DCGKJNM",
    "LPOKGCDH",
    "MNJFGKOP"
};
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

// Bus stops Structure
typedef struct BusStop
{
    char Name;
    int passengerCount;
    int location[2];

    Passenger *passengers;
}BusStop;

Passenger* createPassenger();
void SelectBusStops(Passenger *passenger);

// Newly Created
Passenger* getPassenger(BusStop *stop);
void printPassenger(BusStop *stop);
void createBusStops();
void connectPassengerToStop(BusStop arr[BUSSTOPSIZE],Passenger *passenger);

int main (){
    srand(time(NULL));
    BusStop Stops[BUSSTOPSIZE];

    createBusStops(Stops);
    
    for (size_t i = 0; i < 15; i++)
    {
        connectPassengerToStop(Stops,createPassenger());
    }
    

    for (size_t i = 0; i < BUSSTOPSIZE; i++)
    {
        printf("Name: %c Location: [%d,%d] Passenger Count: %d\n",Stops[i].Name,Stops[i].location[0],Stops[i].location[1],Stops[i].passengerCount);
        printPassenger(&Stops[i]);
    }
    Passenger* temp1 = getPassenger(&Stops[0]);
    Passenger* temp2 = getPassenger(&Stops[0]);
    Passenger* temp3 = getPassenger(&Stops[1]);


    if (temp1 != NULL)
    {
        printf("\nPassenger Deleted\tStart:%c Id:%d\n",temp1->Start,temp1->id);
    }
    if (temp2 != NULL){
        printf("\nPassenger Deleted\tStart:%c Id:%d\n",temp2->Start,temp2->id);
    }
    if (temp3 != NULL)
    {
        printf("\nPassenger Deleted\tStart:%c Id:%d\n",temp3->Start,temp3->id);

    }
    temp1 = createPassenger();
    connectPassengerToStop(Stops,temp1);
    
    printf("\nCreated\t Id:%d Start:%c\n\n",temp1->id,temp1->Start);

    

    for (size_t i = 0; i < BUSSTOPSIZE; i++)
    {
        printf("Name: %c Location: [%d,%d] Passenger Count: %d\n",Stops[i].Name,Stops[i].location[0],Stops[i].location[1],Stops[i].passengerCount);
        printPassenger(&Stops[i]);
    }

    return 0;
}

void createBusStops(BusStop arr[BUSSTOPSIZE]){
    for (size_t i = 0; i < BUSSTOPSIZE; i++)
    {
        arr[i].Name = busStops[i];
        for (size_t j = 0; j < 2; j++)
        {
            arr[i].location[j] = busStopLocation[i][j];
        }
        
        arr[i].passengerCount = 0;

        arr[i].passengers = NULL;
    }
}
void connectPassengerToStop(BusStop arr[BUSSTOPSIZE],Passenger *passenger)
{
    int i = 0;
    for (i = 0; i < BUSSTOPSIZE; i++)
    {
        if (arr[i].Name == passenger->Start)
        {
            break;
        }
    }
    
    if (arr[i].passengers == NULL)
    {
        arr[i].passengers = passenger;
        return;
    }
     
    Passenger* current = arr[i].passengers;
    while (current->next != NULL)
    {
        current = current->next;
    }
    
    current->next = passenger;
}

void printPassenger(BusStop *stop){

    Passenger* current = stop->passengers;
    while (current != NULL)
    {
        printf("\tStart:%c Id:%d\n",current->Start,current->id);
        current = current->next;
    }
    
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
Passenger* getPassenger(BusStop *stop){

    if (stop->passengers == NULL)
    {
        return NULL;
    }

    Passenger* temp = stop->passengers;

    stop->passengers = temp->next;

    return temp;
}