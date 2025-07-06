#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}node;


void addTask(node **HEAD,int data);
void deleteTask(node **HEAD,int data);
void printTask(node **HEAD);
int countTask(node **HEAD);


int main(){

    node *Head = NULL;

    addTask(&Head,1);
    addTask(&Head,2);
    addTask(&Head,3);

    printTask(&Head);

    printf("\n Count: %d",countTask(&Head));

    deleteTask(&Head,1);

    printTask(&Head);

    printf("\n Count: %d",countTask(&Head));

    deleteTask(&Head,3);

    printTask(&Head);

    printf("\n Count: %d",countTask(&Head));

    deleteTask(&Head,2);

    printTask(&Head);

    printf("\n Count: %d",countTask(&Head));

    deleteTask(&Head,5);

    printTask(&Head);

    printf("\n Count: %d",countTask(&Head));

    return 0;
}

void addTask(node **HEAD,int data) 
{
    node *temp = *HEAD;

    if (*HEAD == NULL)
    {
        *HEAD = (node *)malloc(sizeof(node));
        (*HEAD)->data = data;
        (*HEAD)->next = NULL;
        return;
    }
    
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    node *curr = (node *)malloc(sizeof(node));

    curr->data = data;
    curr->next = NULL;

    temp->next = curr;
}
void deleteTask(node **HEAD,int data){

    if (*HEAD == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    node *curr = *HEAD;
    node *prev = NULL;

    while (curr != NULL && curr->data != data )
    {
        prev = curr;
        curr = curr->next;
    }
    
    if (curr != NULL && prev == NULL)
    {
        *HEAD = curr->next;
        printf("\nRemoved: %d\n",data);
    }
    else if(curr != NULL && prev != NULL){
        prev->next = curr->next;
        printf("\nRemoved: %d\n",data); 
    }
    else{
        printf("\nCouldn't find the : %d\n",data);
    }
}
void printTask(node **HEAD){

    node *curr = *HEAD;

    while (curr != NULL)
    {
        printf("%d -> ",curr->data);
        curr = curr->next;
    }

}
int countTask(node **HEAD){

    node *curr = *HEAD;

    int count = 0;

    while(curr != NULL){
        count++;
        curr = curr->next;
    }

    return count;
}