#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* nextNode;
}Node;

Node* HEAD = NULL;

int insert(char data);
int delete(char data);
void display(); 
int count();


int main(){

    HEAD = (Node *)malloc(sizeof(Node));
    HEAD->data = -1;
    HEAD->nextNode = NULL;
    char input;
    int int_input;
    while (1)
        {
        printf("To-Do List Manager\n");
        printf("1. Add Task\n");
        printf("2. Delete Task\n");
        printf("3. Print Task\n");
        printf("4. Count Task\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%c",&input);

        switch (input)
        {
        case '1':
            printf("\nEnter task number: ");
            scanf("%d",&int_input);
            insert(int_input);
            break;
        case '2':
            printf("\nEnter task number to delete: ");
            scanf("%d",&int_input);
            if (delete(int_input) == -1)printf("Could'nt find that task!\b");
            break;
        case '3':
            printf("Tasks: ");
            display();
            break;
        case '4':
            printf("Total tasks: %d\n",count());
            break;
        case '5':
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
int insert(char data){
    if (HEAD->data == -1)
    {
        HEAD->data = data;
        return data;
    }
    Node* currentNode = HEAD;
    Node* prevNode = NULL;

    while (currentNode->nextNode != NULL)
    {
        prevNode = currentNode; 
        currentNode = currentNode->nextNode;
    }
    Node* tempNode = (Node*)malloc(sizeof(Node));
    tempNode->data = data;
    tempNode->nextNode = NULL;
    currentNode->nextNode = tempNode;
    return data;
}
int delete(char data){
    if (HEAD->data == data)
    {
        Node* tempNode = HEAD;
        HEAD = HEAD->nextNode;
        free(tempNode);
        return data;
    }      

    Node* currentNode = HEAD;
    Node* prevNode = NULL;

    while (currentNode->nextNode != NULL)
    {
        prevNode = currentNode; 
        currentNode = currentNode->nextNode;
        if (currentNode->data == data)
        {
            prevNode->nextNode = currentNode->nextNode;
            free(currentNode);
            return data;
        }
    }
    return -1;
}
void display(){
    Node* currentNode = HEAD;
    Node* prevNode = NULL;

    while (currentNode->nextNode != NULL)
    {
        printf("%d -> ",currentNode->data);
        prevNode = currentNode; 
        currentNode = currentNode->nextNode;
    }
    printf("%d -> NULL\n",currentNode->data);
}
int count(){
    Node* currentNode = HEAD;
    Node* prevNode = NULL;
    int i = 1;
    while (currentNode->nextNode != NULL)
    {
        i++;
        prevNode = currentNode; 
        currentNode = currentNode->nextNode;
    }
    return i;
}