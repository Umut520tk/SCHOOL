#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>


bool dene = true;
struct employee{
    int id;
    char name[100];
    struct employee* next;
};

typedef struct employee employee;

employee* HEAD;

void insert(int,char []);
int loadEmployees(char file[]);
void print();

int main(){
    HEAD = NULL;

    int count = loadEmployees("employees.txt");
    printf("%d\n",count);
    print();

    return 0;
}
int loadEmployees(char file[]){
    int count = 0;
    FILE *f_ptr = fopen(file,"r");

    int id;
    char name[100];

    while (fscanf(f_ptr,"%d#%[^\n]\n",&id,name) == 2)
    {
        count++;
        insert(id,name);
    }
    
    fclose(f_ptr);
    return count;
}
void print(){

    employee* current = HEAD;

    while (current->next != NULL)
    {
        printf("Id:%d Name:%s\n",current->id,current->name);
        current = current->next;
    }
    printf("Id:%d Name:%s\n",current->id,current->name);
}
void insert(int id,char name[]){


    if (HEAD == NULL)
    {
        HEAD = (employee *)malloc(sizeof(employee));
        HEAD->id = id;
        strcpy(HEAD->name,name);
        HEAD->next = NULL;
        return;
    }

    employee* current = HEAD;
    
    while (current->next != NULL)
    {
        current = current->next;
    }

    employee* temp = (employee *)malloc(sizeof(employee));
    temp->id = id;
    strcpy(temp->name,name);
    temp->next = NULL;

    current->next = temp;
}