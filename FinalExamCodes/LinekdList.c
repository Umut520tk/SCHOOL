#include <stdio.h>
#include <stdlib.h>

struct node 
{

    int data;
    struct node *next;
};


typedef struct node node;

node *HEAD = NULL;

void insert(int data);
void display();

int main(){


    insert(1);
    insert(2);
    insert(3);
    insert(4);
    insert(5);

    display();

    return 0;
}

void insert(int data){

    if (HEAD == NULL)
    {
        HEAD = (node *)malloc(sizeof(node));
        HEAD->data = data;
        HEAD->next = NULL;
    }
    else{
        node *curr = HEAD;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
     
        node *temp = (node *)malloc(sizeof(node));
        temp->data = data;
        temp->next = NULL;

        curr->next = temp;
    }
}
void display(){

    if (HEAD != NULL)
    {
        node *curr = HEAD;


        while (curr != NULL){
            printf("%d -> " ,curr->data);
            curr = curr->next;
        }
    }
    

}