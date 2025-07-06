#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;

    struct node *next;
};

void push(struct node **Top,int data);
int pop(struct node **Top);
void peek(struct node *Top);
void display(struct node *Top);

int main(){

    struct node *Top = NULL;

    for (size_t i = 0; i < 100; i++)
    {
        push(&Top,i);
    }
    display(Top);
    
    for (size_t i = 0; i < 50; i++)
    {
        printf("\nPopped data: %d\n",pop(&Top));
    }

    display(Top);

    return 0;
}

void push(struct node **Top,int data){
    
    if (*Top == NULL)
    {
        *Top = (struct node *)malloc(sizeof(struct node));
        (*Top)->data = data;
        (*Top)->next = NULL;
        return;
    }
    
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = *Top;
    *Top = temp;

}
int pop(struct node **Top){

    if (*Top == NULL)
    {
        printf("\n Stack is Empty!\n");
    }
    else{
        int data = (*Top)->data;

        struct node *temp = (*Top);
        (*Top) = (*Top)->next;

        //free(temp);
        return data;
    }
}
void display(struct node *Top){

    struct node *curr = Top;

    printf("\n\tSTACK:\n     Top -> ");
    while (curr->next != NULL)
    {
        printf("%d -> ",curr->data);
        curr = curr->next;
    }
    printf("%d",curr->data);
}