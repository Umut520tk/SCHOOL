#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};
typedef struct Node Node;

Node* top = NULL;

void push(int data);
void pop();
void peek();

int main(){
    top = NULL;

    char input;
    int int_input;

    while (1)
    {
    printf("To-Do List Manager\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Peek\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%c",&input);

    switch (input)
    {
    case '1':
        printf("\nEnter number: ");
        scanf("%d",&int_input);
        push(int_input);
        break;
    case '2':
        printf("Pop: ");
        pop();
        break;
    case '3':
        peek();
        break;
    case '4':
        return 0;
        break;
    default:
        printf("!You entered non-exist!\n");
        break;
    }
    getchar();
    }
    return 0;
}

void push(int data){
    if (top == NULL) {
        top = (Node *)malloc(sizeof(Node));
        top->data = data;
        top->next = NULL;
        return;
    }
    
    Node *temp = (Node *)malloc(sizeof(Node));
    
    temp->data = data;
    temp->next = top;
    top = temp;
}
void pop(){
    if (top == NULL)
    {
        printf("Stack Underflow!\n");
        return;
    }

    printf("%d\n",top->data);
    Node* temp = top;
    top = top->next;
    free(temp);
}
void peek(){
    if (top == NULL) { 
        printf("Stack is empty\n"); 
    } else { 
        printf("Top element is %d\n", top->data); 
    } 
}