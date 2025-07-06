#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;

}node;

node *top = NULL;


void push();
void pop();
void display();


int main(){ 

    push(1);
    push(2);
    push(3);
    push(4);

    display();

    pop();
    display();

    pop();

    display();

    return 0;
}

void push(int data){

    if (top == NULL)
    {
        top = (node *)malloc(sizeof(node));
        top->data = data;
        top->next = NULL;
    }else{

        node *temp = (node *)malloc(sizeof(node));

        temp->data = data;

        temp->next = top;
        top = temp;
    }
}

void display(){

    node *curr = top;

    printf("top-> ");
    while (curr != NULL){
        printf("%d ->",curr->data);
        
        curr = curr->next;
    }
    puts("");
}

void pop(){

    node* temp = top;

    top = top->next;

    free(temp);

}