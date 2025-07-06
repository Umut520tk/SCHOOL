#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
#include <stdbool.h>
#include <math.h>

#define COl 57
#define ROW 21
#define DELAY 1
#define BASE_POSITION 2

#define BUS_LINE_COUNT 6
#define BUS_LINE_SIZE 9
#define BUS_STOP_SIZE 16

#define MAX_PASSENGER 8
#define MAX_LUGGAGE 8

const char* colorsText[] = {
    "\033[31m", // Red
    "\033[32m", // Green
    "\033[33m", // Yellow
    "\033[34m", // Blue
    "\033[35m", // Magenta
    "\033[36m", // Cyan
    "\033[37m", // White
};

const char* colorsBac[] = {
    "\033[41m", // Red
    "\033[42m", // Green
    "\033[43m", // Yellow
    "\033[44m", // Blue
    "\033[45m", // Magenta
    "\033[46m", // Cyan
    "\033[47m", // White
};


int timeStep = 0;
int prev_timeStep = 0;

bool Running = true;

char map[ROW][COl+1] = {
    "#########################################################",
    "#A      #####B            #####C                 D#######",
    "# ########### ########### ##### ##### ########### #######",
    "# ########### ########### ##### ##### ########### #######",
    "# ########### ########### ##### ##### ########### #######",
    "# ########### ########### ##### ##### ########### #######",
    "# ########### ########### ##### ##### ########### #######",
    "#E           F                 G#####            H      #",
    "# ########### ##### ########### ##### ##### ########### #",
    "# ########### ##### ########### ##### ##### ########### #",
    "# ########### ##### ########### ##### ##### ########### #",
    "# ########### ##### ########### ##### ##### ########### #",
    "# ########### ##### ########### ##### ##### ########### #",
    "#I           J                 K           L#####       #",
    "####### ##### ##### ########### ##### ##### ##### #######",
    "####### ##### ##### ########### ##### ##### ##### #######",
    "####### ##### ##### ########### ##### ##### ##### #######",
    "####### ##### ##### ########### ##### ##### ##### #######",
    "####### ##### ##### ########### ##### ##### ##### #######",
    "#      M     N      #####      O           P            #",
    "##########################################################",
};

int busStopLocation[16][2] = {
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


// Passenger System
typedef struct Luggage
{
    int id;
    struct Passenger *owner;
}Luggage;

typedef struct Passenger{
    int id;
    char line[BUS_LINE_SIZE + 1];
    char Start;
    char End;

    struct Luggage luggages[2];
    struct Passenger *next;

    int direction;
    int LuaggageCount;

}Passenger;

typedef struct Queue{
    Passenger *front;
    Passenger *rear;

}Queue;

// Passenger.c
Queue* createQueue();
Passenger* createPassenger();
void SelectBusStops(Passenger *);
void enqueue(Queue* q,Passenger* p);
Passenger* dequeue(Queue* q);
void printQueue(Queue* q);

// Bus stops Structure
typedef struct BusStop
{
    char Name;
    int passengerCount;
    int location[2];

    Passenger *passengers;
}BusStop;

char busStops[BUS_STOP_SIZE] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
char lines[BUS_LINE_COUNT][BUS_LINE_SIZE + 1] = {
                
                    "AEIJKL",
                    "BFEIJNM",
                    "CGKJFEA",
                    "DCGKJNM",
                    "LPOKGCDH",
                    "MNJFGKOP"
                };

// 

void delay(int number_of_seconds);
void printScreen();

// Stops.c
Passenger* getPassenger(BusStop *stop,char line[BUS_LINE_SIZE],int dir);
void printPassenger(BusStop *stop);
void createBusStops(BusStop arr[BUS_LINE_COUNT]);
void connectPassengerToStop(BusStop arr[BUS_STOP_SIZE],Passenger *passenger);
void printPassengerCounts(BusStop arr[BUS_STOP_SIZE]);


// Busses 
typedef struct Bus{
    char Name[2];

    int location_X;
    int location_Y;

    char line[BUS_LINE_SIZE];
    
    int fromPos;
    int toPos;

    int passengerCount;

    int positionInLine;

    int direction;

    Passenger *passengers;

    Luggage luggages[MAX_LUGGAGE];
    int luggagesTop;

    bool luaggesLoadOperations;
    bool luaggesUnloadOperations;

    bool chosen;

    Luggage luggageToBeLoaded[MAX_LUGGAGE];
    int luggagesToBeLoadedIndex;
    int luggageToBeLoadedCount;

    Luggage waitingLuggages[MAX_LUGGAGE];
    int waitinLuggagesIndex; 

    Luggage luggageToBeUnloaded[MAX_LUGGAGE];
    bool isUnloadingDone;
    int luggagesToBeReloadedIndex;
    int luggageToBeUnloadedCount;

}Bus;

void CreateBusses(Bus b[BUS_LINE_COUNT]);
void moveBusses(Bus b[BUS_LINE_COUNT],BusStop stops[BUS_STOP_SIZE]);
void GetInTheBus(BusStop *stop,Bus *bus);
void GetOutTheBus(BusStop *stop, Bus *bus);


// Selecting via mouse
int *getMousePosition();

// Add this after the bus structure definition
Bus *selectedBusForDisplay = NULL;
HANDLE displayThread;
HANDLE selectThread;
HANDLE hConsole;

unsigned __stdcall DisplayBusInfo(void* arg);
unsigned __stdcall SelectViaMouse(void *arg);

void printStatistic(Bus b[BUS_LINE_COUNT * 2],BusStop s[BUS_STOP_SIZE]);

// Stoppin \\ Starting Simulation
HANDLE checkGameRunningThread;
unsigned __stdcall CheckForKeyboard(void *arg);
int countDigits(int num);

// Luagges Systems
void loadLuggages(Bus *bus);
void UnloadLuggages(Bus *bus);


int loadLuggages_time = 0;
int unloadLuggages_time = 0;
int luggages_delay = 1;

int main()
{
    // Set console title
    SetConsoleTitle("Bus Simulation");

    #if defined(_WIN32)
    system("cls");
    #else
    printf("\033[2J\033[H");
    #endif

    srand(time(NULL));




    Queue *queue = createQueue();
    
    BusStop Stops[BUS_STOP_SIZE];
    createBusStops(Stops);

    Bus busses[BUS_LINE_COUNT * 2];
    CreateBusses(busses);

    for (size_t i = 0; i < 15; i++)
    {
        enqueue(queue,createPassenger());
    }

    int passengerDelay = rand() % 2 + 1;


    displayThread = (HANDLE)_beginthreadex(NULL, 0, DisplayBusInfo, (void*)busses, 0, NULL);
    selectThread = (HANDLE)_beginthreadex(NULL, 0, SelectViaMouse, (void*)busses, 0, NULL);
    checkGameRunningThread = (HANDLE)_beginthreadex(NULL, 0, CheckForKeyboard, NULL, 0, NULL);

    printScreen();
    printQueue(queue);
    while (1)
    {
        printf("\033[2;65H");
        printf("Time =%4d",timeStep);
        
        moveBusses(busses,Stops);
        if (timeStep-prev_timeStep == passengerDelay)
        {

            Passenger *newPassenger = dequeue(queue);

            connectPassengerToStop(Stops,newPassenger);

            printQueue(queue);

            for (size_t i = 0; i < BUS_STOP_SIZE; i++)
            {
                if (Stops[i].Name == newPassenger->Start)
                {
                    printPassenger(&Stops[i]);
                }
            }

            printPassengerCounts(Stops);
            printStatistic(busses,Stops);

            passengerDelay = rand() % 2 + 1;

            prev_timeStep = timeStep;
        }
        if (selectedBusForDisplay != NULL)
        {
            printf("%s\033[%d;%dH%d\033[0m",colorsBac[1],selectedBusForDisplay->location_X + BASE_POSITION, selectedBusForDisplay->location_Y + BASE_POSITION,selectedBusForDisplay->passengerCount);
        }
        
        delay(DELAY);
        while (!Running)
        {}        
    }

    CloseHandle(displayThread);
    CloseHandle(selectThread);
    return 0;
}

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds);

    timeStep++;
}

void printScreen(){

    printf("  ");
    char c;
    for (c = 'A'; c <= 'Z'; ++c)
        printf("%c", c);
    for (c = 'A'; c <= 'Z'; ++c)
        printf("%c", c);
    for (c = 'A'; c <= 'E'; ++c)
        printf("%c", c);
    printf("\n\n");
    for (size_t i = 1; i < ROW + 1; i++)
    {
        for (size_t j = 0; j < COl; j++)
        {
            if (j == 0)
            {
                printf("%d ",i % 10);
            }
            
            if (map[i-1][j] == '#')
            {
                printf("%s%c\033[0m", colorsBac[3],map[i - 1][j]); 
            }
            else{printf("%c",map[i - 1][j]);}
        }        
        printf("\n");
    }
}
// Passenger System

Queue* createQueue(){
    Queue* newQueue = (Queue *)malloc(sizeof(Queue)); 
    newQueue->front = NULL;
    newQueue->rear = NULL;

    return newQueue;
}

Passenger* createPassenger()
{
    Passenger *newPassenger = (Passenger *)malloc(sizeof(Passenger));
    newPassenger->id = 1 + rand() % 999; 
    newPassenger->next = NULL;
    strcpy(newPassenger->line,lines[rand() % BUS_LINE_COUNT]);

    SelectBusStops(newPassenger);

    for (size_t i = 0; i < 2; i++)
    {
        newPassenger->luggages[i].id = -1;
        newPassenger->luggages[i].owner = NULL;
    }
    newPassenger->LuaggageCount = rand() % 3;
    for (size_t j = 0; j < newPassenger->LuaggageCount; j++)
    {
        newPassenger->luggages[j].id = 1 + rand() % 999;
        newPassenger->luggages[j].owner = newPassenger;
    }

    return newPassenger;
}

void SelectBusStops(Passenger *passenger)
{

    /* Only One Direction
    int rnd = rand() % (strlen(passenger->line) - 1);
    char start = passenger->line[rnd];
    char end;
    if (rnd == strlen(passenger->line) - 2)
    {
        end = passenger->line[strlen(passenger->line)-1];
    }
    else{
        int rnd2 = rand() % (strlen(passenger->line) - rnd - 1) + 1;
        end = passenger->line[rnd2 + rnd];
    }*/
    
    int rnd = rand() % strlen(passenger->line);
    int rnd2 =  rand() % strlen(passenger->line);

    while (rnd2 == rnd)
    {
        rnd2 =  rand() % strlen(passenger->line);
    }
    
    char start = passenger->line[rnd]; 
    char end = passenger->line[rnd2];

    passenger->Start = start;
    passenger->End = end;

    passenger->direction = ((rnd2 - rnd) > 0) ? 1 : -1; 
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
    printf("\033[4;65HNew Passenger");
    for (size_t i = 0; i < 23; i++)
    {
        printf("\033[5;%dH-", 67 + 2*i);
    }
    printf("\033[6;65H>");
    for (size_t j = 14; j < -1; j--)
    {
        printf("\033[6;%dH%c",110 - 3 * j ,pass[j]);
    }
    printf("\033[6;113H>");
    for (size_t i = 0; i < 23; i++)
    {
        printf("\033[7;%dH-", 67 + 2*i);
    }
}
Passenger* dequeue(Queue *q){

    if (q->front == NULL)
    {
        printf("Queue is empty!!!");
        return NULL;
    }
    Passenger* temp = q->front;
    q->front = temp->next;
    temp->next = NULL;

    Passenger* newPassenger = createPassenger();

    enqueue(q,newPassenger);

    return temp;
}

// Stops.c
void createBusStops(BusStop arr[BUS_STOP_SIZE]){
    for (size_t i = 0; i < BUS_STOP_SIZE; i++)
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

void connectPassengerToStop(BusStop arr[BUS_STOP_SIZE],Passenger *passenger)
{
    int i = 0;
    for (i = 0; i < BUS_STOP_SIZE; i++)
    {
        if (arr[i].Name == passenger->Start)
        {
            break;
        }
    }
    
    if (arr[i].passengers == NULL)
    {
        arr[i].passengers = passenger;
        arr[i].passengerCount++;
        return;
    }
     
    Passenger* current = arr[i].passengers;
    while (current->next != NULL)
    {
        current = current->next;
    }
    
    current->next = passenger;
    arr[i].passengerCount++;
}

void printPassenger(BusStop *stop){

    Passenger* current = stop->passengers;
    while (current != NULL)
    {
        printf("\033[9;65H\033[K");
        printf("\033[9;65HStart:%c Id:%d",current->Start,current->id);
        current = current->next;
    }
    
}
Passenger* getPassenger(BusStop *stop,char line[BUS_LINE_SIZE],int dir){

    if (stop->passengers == NULL)
    {
        return NULL;
    }

    Passenger* prev = NULL;
    Passenger* curr = stop->passengers;

    while (curr != NULL)
    {
        if (strcmp(curr->line,line) == 0 && curr->direction == dir)
        {
            if (curr->next == NULL)
            {
                stop->passengers = NULL;
            }
            else if(prev == NULL){
                stop->passengers = stop->passengers->next;
                curr->next = NULL;
            }
            else{
                prev->next = curr->next;
                curr->next = NULL;
            }
            stop->passengerCount--;
            break;   
        }
        prev = curr;
        curr = curr->next;
    }
    return curr;
}
void printPassengerCounts(BusStop arr[BUS_STOP_SIZE]){

    for (size_t i = 0; i < BUS_STOP_SIZE; i++)
    {
        printf("\033[%d;%dH%s%d\033[0m",arr[i].location[0] + BASE_POSITION + 1, arr[i].location[1] + BASE_POSITION + 1,colorsBac[3],arr[i].passengerCount);
    }
}

// Busses

void CreateBusses(Bus b[BUS_LINE_COUNT * 2]){

    int bus_counts[BUS_LINE_COUNT] = {0};
    for (size_t i = 0; i < BUS_LINE_COUNT * 2; i++)
    {        
        strcpy(b[i].line,lines[i % BUS_LINE_COUNT]);
        int k = 0;

        b[i].direction = (i < BUS_LINE_COUNT) ? 1 : -1;

        while (busStops[k] != b[i].line[(b[i].direction == 1) ? 0 : (strlen(b[i].line) - 1)])
        {
            k++;
        }
        
        b[i].location_X = busStopLocation[k][0];
        b[i].location_Y = busStopLocation[k][1];

        b[i].passengerCount = 0;

        b[i].fromPos = k;

        k = 0;
        while (b[i].line[(b[i].direction == 1) ? 1 : (strlen(b[i].line) - 2)] != busStops[k])
        {
            k++;
        }
        b[i].toPos = k;

        b[i].positionInLine = (b[i].direction == 1) ? 1 : strlen(b[i].line) - 2;

        
        sprintf(b[i].Name,"%c%d",b[i].line[0],++bus_counts[i % BUS_LINE_COUNT]);

        b[i].passengers = NULL;

        for (size_t j = 0; j < MAX_LUGGAGE; j++)
        {
            b[i].luggages[j].id = -1;
            b[i].luggages[j].owner = NULL;
        }

        b[i].chosen = false;

        b[i].luggagesTop = -1;
        
        b[i].luggagesToBeLoadedIndex = -1;
        b[i].luggageToBeLoadedCount = 0;
        b[i].luaggesLoadOperations = false;

        b[i].luggagesToBeReloadedIndex = -1;
        b[i].luggageToBeUnloadedCount = 0;
        b[i].luaggesUnloadOperations = false;
        
        b[i].waitinLuggagesIndex = -1;
        b[i].isUnloadingDone = false;
        
    }
}
void moveBusses(Bus b[BUS_LINE_COUNT],BusStop stops[BUS_STOP_SIZE])
{
    for (size_t i = 0; i < BUS_LINE_COUNT * 2; i++)
    {


        if(b[i].luaggesUnloadOperations){
            /*
            if (timeStep - unloadLuggages_time == luggages_delay){
                unloadLuggages_time = timeStep;
                UnloadLuggages(&b[i]);
            }*/
           UnloadLuggages(&b[i]);
        }
        else if (b[i].luaggesLoadOperations)
        {
            /*
            if (timeStep - loadLuggages_time == luggages_delay){
                loadLuggages_time = timeStep;
                loadLuggages(&b[i]);
            }*/
           loadLuggages(&b[i]);
        }
        else{
            int x = busStopLocation[b[i].toPos][0] - b[i].location_X;
            int y = busStopLocation[b[i].toPos][1] - b[i].location_Y;
            int sign = 0;
            if (x == 0 && y != 0)
            {
                sign = (y < 0) ? -1 : 1;
                b[i].location_Y += sign;
                        
                printf("\033[%d;%dH%c",b[i].location_X + BASE_POSITION,b[i].location_Y - sign + BASE_POSITION,map[b[i].location_X - 1][b[i].location_Y - sign - 1]);
            }
            else if(y == 0 && x != 0){
                sign = (x < 0) ? -1 : 1;
                b[i].location_X += sign;

                printf("\033[%d;%dH%c",b[i].location_X - sign + BASE_POSITION,b[i].location_Y + BASE_POSITION,map[b[i].location_X - sign - 1][b[i].location_Y - 1]);
                
            }
            else{
                b[i].fromPos = b[i].toPos;
                int k = 0;
                b[i].positionInLine += b[i].direction;
                if (b[i].positionInLine == strlen(b[i].line))
                {
                    b[i].direction *= -1;
                    b[i].positionInLine-=2;
                    while (b[i].line[b[i].positionInLine] != busStops[k])
                    {
                        k++;
                    }
                    b[i].toPos = k;
                }
                if (b[i].positionInLine == -1)
                {
                    b[i].direction *= -1;
                    b[i].positionInLine+=2;
                    while (b[i].line[b[i].positionInLine] != busStops[k])
                    {
                        k++;
                    }
                    b[i].toPos = k;
                }
                else{
                    while (b[i].line[b[i].positionInLine] != busStops[k])
                    {
                        k++;
                    }
                    b[i].toPos = k;
                }
                GetInTheBus(&stops[b[i].fromPos],&b[i]);
                GetOutTheBus(&stops[b[i].fromPos],&b[i]);
                if (b[i].luggageToBeLoadedCount != 0)
                {
                    b[i].luaggesLoadOperations = true;
                    loadLuggages_time = timeStep;
                }
                if (b[i].luggageToBeUnloadedCount != 0)
                {
                    b[i].luaggesUnloadOperations = true;
                    unloadLuggages_time = timeStep;
                }
                
            }
            if (x == 0 && y == 0)
            {
                printf("\033[%d;%dH%c",b[i].location_X + BASE_POSITION, b[i].location_Y + BASE_POSITION,map[b[i].location_X - 1][b[i].location_Y - 1]);   
            }
            else{
                if (b[i].chosen)
                {
                    printf("%s\033[%d;%dH%d\033[0m",colorsBac[1],b[i].location_X + BASE_POSITION, b[i].location_Y + BASE_POSITION,b[i].passengerCount); 
                }
                else{
                printf("\033[%d;%dH%d",b[i].location_X + BASE_POSITION, b[i].location_Y + BASE_POSITION,b[i].passengerCount);}
            }
        }
    }
}

// Carrying Passenger
void GetInTheBus(BusStop *stop,Bus *bus){
    int indx = 0;

    for (size_t i = 0; i < MAX_LUGGAGE; i++)
    {
        bus->luggageToBeLoaded[i].id = -1;
        bus->luggageToBeLoaded[i].owner = NULL;
    }

    if (bus->passengerCount < MAX_PASSENGER)
    {
        for (size_t i = 0; i < stop->passengerCount; i++)
        {
            if (bus->passengerCount == MAX_PASSENGER)
            {
                break;
            }
            Passenger *pass = getPassenger(stop,bus->line,bus->direction);
            if (pass != NULL && pass->LuaggageCount + bus->luggagesTop < MAX_LUGGAGE)
            {
                if (pass->luggages[0].id != -1 && pass->luggages[1].id != -1)
                {
                    bus->luggageToBeLoaded[indx].id = pass->luggages[0].id;
                    bus->luggageToBeLoaded[indx].owner = pass->luggages[0].owner;

                    bus->luggageToBeLoaded[indx+1].id = pass->luggages[1].id;
                    bus->luggageToBeLoaded[indx+1].owner = pass->luggages[1].owner;

                    bus->luggageToBeLoadedCount += 2;
                    indx += 2;
                }
                else if (pass->luggages[0].id != -1)
                {
                    bus->luggageToBeLoaded[indx].id = pass->luggages[0].id;
                    bus->luggageToBeLoaded[indx].owner = pass->luggages[0].owner;
                    bus->luggageToBeLoadedCount++;
                    indx++;
                }
                else if (pass->luggages[1].id != -1)
                {
                    bus->luggageToBeLoaded[indx].id = pass->luggages[1].id;
                    bus->luggageToBeLoaded[indx].owner = pass->luggages[1].owner;
                    bus->luggageToBeLoadedCount++;
                    indx++;
                }
                if (bus->passengers == NULL)
                {
                    bus->passengers = pass;    
                }
                else {
                    Passenger *curr = bus->passengers;
                    while (curr->next != NULL)
                    {
                        curr = curr->next;
                    }
                    curr->next = pass;
                }
                bus->passengerCount++;
            }
        }
    }

}

void GetOutTheBus(BusStop *stop,Bus *bus)
{
    for (size_t i = 0; i < MAX_LUGGAGE; i++)
    {
        bus->luggageToBeUnloaded[i].id = -1;
        bus->luggageToBeUnloaded[i].owner = NULL;

        bus->waitingLuggages[i].id = -1;
        bus->waitingLuggages[i].owner = NULL; 
    }
    

    int indx = 0;
    for (size_t i = 0; i < bus->passengerCount; i++)
    {
        Passenger *prev = NULL;
        Passenger *curr = bus->passengers;
     
        while (curr != NULL)
        {
            if (curr->End == stop->Name)
            {
                bus->passengerCount--;
                i = -1;
                break;
            }
            
            prev = curr;
            curr = curr->next;
        }
        
        if(curr != NULL)
        {
            if (curr->luggages[0].id != -1 && curr->luggages[1].id != -1)
            {
                bus->luggageToBeUnloaded[indx].id = curr->luggages[0].id;
                bus->luggageToBeUnloaded[indx].owner = curr->luggages[0].owner;
                bus->luggageToBeUnloaded[indx+1].id = curr->luggages[1].id;
                bus->luggageToBeUnloaded[indx+1].owner = curr->luggages[1].owner;
                bus->luggageToBeUnloadedCount += 2;
                indx += 2;
            }
            else if (curr->luggages[0].id != -1)
            {
                bus->luggageToBeUnloaded[indx].id = curr->luggages[0].id;
                bus->luggageToBeUnloaded[indx].owner = curr->luggages[0].owner;
                bus->luggageToBeUnloadedCount++;
                indx++;
            }
            else if (curr->luggages[1].id != -1)
            {
                bus->luggageToBeUnloaded[indx].id = curr->luggages[1].id;
                bus->luggageToBeUnloaded[indx].owner = curr->luggages[1].owner;
                bus->luggageToBeUnloadedCount++;
                indx++;
            }
        }

        if (curr != NULL && prev == NULL)
        {
            bus->passengers = curr->next;
            free(curr);
        }
        else if(curr != NULL)
        {
            prev->next = curr->next;
            free(curr);
        }
        else{
            break;
        }
    }
}
// Luagges Systems
void loadLuggages(Bus *bus)
{
    bus->luggagesToBeLoadedIndex++;
    if (bus->luggagesTop < MAX_LUGGAGE - 1 && bus->luggageToBeLoadedCount > 0 && bus->luggagesToBeLoadedIndex < MAX_LUGGAGE  && bus->luggageToBeLoaded[bus->luggagesToBeLoadedIndex].id != -1)
    {

        bus->luggagesTop++;
        bus->luggages[bus->luggagesTop].id = bus->luggageToBeLoaded[bus->luggagesToBeLoadedIndex].id;
        bus->luggages[bus->luggagesTop].owner = bus->luggageToBeLoaded[bus->luggagesToBeLoadedIndex].owner;
        bus->luggageToBeLoadedCount--;
        if (bus->luggageToBeLoadedCount == 0)
        {
            bus->luggagesToBeLoadedIndex = -1;
            bus->luggageToBeLoadedCount = 0;
            bus->luaggesLoadOperations = false;
        }
        
    }
    else{
        bus->luggagesToBeLoadedIndex = -1;
        bus->luggageToBeLoadedCount = 0;
        bus->luaggesLoadOperations = false;
    }
}

void UnloadLuggages(Bus *bus){

    if (bus->isUnloadingDone)
    {
        if (bus->waitinLuggagesIndex == -1)
        {
            bus->isUnloadingDone = false;
            bus->luaggesUnloadOperations = false;
            return;
        }
        
        bus->luggagesToBeReloadedIndex++;
        if (bus->waitingLuggages[bus->luggagesToBeReloadedIndex].id != -1)
        {
            bus->luggagesTop++;
            bus->luggages[bus->luggagesTop].id = bus->waitingLuggages[bus->luggagesToBeReloadedIndex].id;
            bus->luggages[bus->luggagesTop].owner = bus->waitingLuggages[bus->luggagesToBeReloadedIndex].owner;

            bus->waitingLuggages[bus->luggagesToBeReloadedIndex].id = -1;
            bus->waitingLuggages[bus->luggagesToBeReloadedIndex].owner = NULL;
        }
        else{
            bus->luggagesToBeReloadedIndex = -1;
            bus->waitinLuggagesIndex = -1;
            bus->luaggesUnloadOperations = false;
            bus->isUnloadingDone = false;
            return;
        }
        if (bus->luggagesToBeReloadedIndex == bus->waitinLuggagesIndex)
        {
            bus->luggagesToBeReloadedIndex = -1;
            bus->waitinLuggagesIndex = -1;
            bus->luaggesUnloadOperations = false;
            bus->isUnloadingDone = false;
        }
    }
    else {
        if (bus->luggagesTop > -1)
        {
            for (size_t i = 0; i < MAX_LUGGAGE; i++)
            {
                if (bus->luggageToBeUnloaded[i].id != -1 && bus->luggages[bus->luggagesTop].id == bus->luggageToBeUnloaded[i].id)
                {
                    bus->luggages[bus->luggagesTop].id = -1;
                    bus->luggages[bus->luggagesTop].owner = NULL;

                    bus->luggageToBeUnloaded[i].id = -1;;
                    bus->luggageToBeUnloaded[i].owner = NULL;
                    
                    bus->luggageToBeUnloadedCount--;

                    break;
                }
            }
            if(bus->luggages[bus->luggagesTop].id != -1 && bus->waitinLuggagesIndex+1 < MAX_LUGGAGE){
                bus->waitinLuggagesIndex++;
                bus->waitingLuggages[bus->waitinLuggagesIndex].id = bus->luggages[bus->luggagesTop].id;
                bus->waitingLuggages[bus->waitinLuggagesIndex].owner = bus->luggages[bus->luggagesTop].owner;
                
                bus->luggages[bus->luggagesTop].id = -1;
                bus->luggages[bus->luggagesTop].owner = NULL;
            }
            bus->luggagesTop--;
            if (bus->luggageToBeUnloadedCount <= 0)
            {
                bus->luggageToBeUnloadedCount = 0;
                bus->isUnloadingDone = true; 
            }
        }
        else{
            bus->luggageToBeUnloadedCount = 0;
            bus->luggagesTop = -1;
            bus->isUnloadingDone = true;
        }
    }
}
// selecting via mouse
int *getMousePosition(){
    int *mousePosition = (int *)malloc(sizeof(int) * 2);
    DWORD prev_mode;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;

    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    while(1) {
        ReadConsoleInput(hInput, irInBuf, 128, &cNumRead);
        for(DWORD i = 0; i < cNumRead; i++) {
            if(irInBuf[i].EventType == MOUSE_EVENT) {
                // Debug print to see what events we're getting
                fflush(stdout);
                
                // Check for any mouse button press
                if(irInBuf[i].Event.MouseEvent.dwButtonState != 0) {
                    
                    mousePosition[0] = irInBuf[i].Event.MouseEvent.dwMousePosition.Y + 1;
                    mousePosition[1] = irInBuf[i].Event.MouseEvent.dwMousePosition.X + 1;

                    return mousePosition;
                }
            }
        }
    }
}
unsigned __stdcall SelectViaMouse(void *arg){
    Bus *b = (Bus*) arg ;
    Bus *selectedBus = NULL;
    bool find = false;

    while (selectedBus == NULL)
    {
        int *mousePosition = getMousePosition();
        for (size_t i = 0; i < BUS_LINE_COUNT * 2; i++)
        {
            b[i].chosen = false;
            if (selectedBus == NULL && mousePosition[0] - BASE_POSITION == b[i].location_X && mousePosition[1] - BASE_POSITION == b[i].location_Y)
            {
                b[i].chosen = true;
                selectedBus = &b[i];
                selectedBusForDisplay = selectedBus;
                find = true;
            }
        }
        if (!find && selectedBusForDisplay != NULL)
        {
            for (size_t i = 0; i < BUS_LINE_COUNT*2; i++)
            {
                if (strcmp(selectedBusForDisplay->Name,b[i].Name) == 0)
                {
                    b[i].chosen = true;
                }    
            } 
        }
        else{
            selectedBus = NULL;
            find = false;
        }
    }
}
unsigned __stdcall DisplayBusInfo(void* arg) {
    Bus* busses = (Bus*)arg;
    while(1) {
        if(selectedBusForDisplay != NULL) {
            // Clear previous display area

            Passenger *temp = selectedBusForDisplay->passengers;

            printf("\033[15;70H\033[K");
            printf("\033[15;70HBus [%s] Passengers", selectedBusForDisplay->Name);
            for (size_t i = 0; i < MAX_PASSENGER; i++)
            {
                printf("\033[%d;70H\033[K",i + 16);
            }
            
            for (size_t i = 0; i < selectedBusForDisplay->passengerCount; i++)
            {
                printf("\033[%d;70H%3d:\t%c-%c (L:",i+16,temp->id,temp->Start,temp->End);

                if (temp->luggages[0].owner != NULL)
                {
                    printf("%d",temp->luggages[0].id);
                    if (temp->luggages[1].owner != NULL)
                    {
                        printf(",%d",temp->luggages[1].id);
                    }
                    
                }
                else{printf("-");}
                printf(")");
                temp = temp->next;
            } 

            printf("\033[23;82H\033[K");
            printf("\033[23;82HBus [%s] Luggages", selectedBusForDisplay->Name);

            for (size_t i = 0; i < 8; i++)
            {
                printf("\033[%d;100H\033[K",23 - i);
                printf("\033[%d;100H|",23 - i);
                printf("\033[%d;104H\033[K",23 - i);
                printf("\033[%d;104H|",23-i);
            }
            printf("\033[24;100H-----");
            
            for (size_t i = 0; i < selectedBusForDisplay->luggagesTop+1; i++)
            {
                if (selectedBusForDisplay->luggages[i].owner != NULL)
                {
                    printf("\033[%d;101H%d",23 - i,selectedBusForDisplay->luggages[i].id);
                }
            }
        }
        Sleep(1000);
    }
    return 0;
}
void printStatistic(Bus b[BUS_LINE_COUNT * 2],BusStop s[BUS_STOP_SIZE]){
    int Waiting = 0;
    int Travelling = 0;
    int busFulness = 0;

    for (size_t i = 0; i < BUS_STOP_SIZE; i++)
    {
        Waiting += s[i].passengerCount;
    }

    for (size_t i = 0; i < BUS_LINE_COUNT * 2; i++)
    {
        Travelling += b[i].passengerCount;
    }
    
    if (Travelling != 0) {
        busFulness = (Travelling * 100) / (BUS_LINE_COUNT * 16);
    } else {
        busFulness = 0.0; // Set to 0% if no passengers are travelling
    }

    printf("\033[11;70H\033[K");
    printf("\033[11;70HWaiting     :%d", Waiting);

    printf("\033[12;70H\033[K");
    printf("\033[12;70HTravelling  :%d", Travelling);

    printf("\033[13;70H\033[K");
    printf("\033[13;70HBus fullness:%d%%", busFulness);

}



// Check for Game is Running
int countDigits(int num) {
    if (num == 0) return 1; // Special case for 0
    return (int)log10(abs(num)) + 1; // Use abs() to handle negative numbers
}

unsigned __stdcall CheckForKeyboard(void *arg){
    while (1)
    {
        if (GetAsyncKeyState('R') & 0x8000)
        {
            printf("\033[2;77H\033[K");
            Running = true;
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            printf("\033[2;77H\033[K");
            printf("\033[2;77H(paused)");
            Running = false;
        }

        Sleep(50);
    }

    return 0;
}
