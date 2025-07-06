#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    char data;
    struct Node *nextNode;
}Node;
Node *HEAD = NULL;
void insert(char);
void display();
char delete(char data);
void freeNode();

int main(){
    HEAD = (Node *)malloc(sizeof(Node));
    char str[100];
    printf("Please enter: ");
    scanf("%[^\n]",str);
    getchar();

    HEAD->data = str[0];
    HEAD->nextNode = NULL;

    int n = strlen(str);
    for (size_t i = 1; i < strlen(str); i++)
    {
        insert(str[i]);
    }
    printf("Created With linked List: ");
    display();

    printf("\n Which do you want to delete: ");
    scanf("%c",&str[0]);

    delete(str[0]);
    printf("Deleted: ");
    display();

    return 0;
}
void display(){
    Node* currentNode = HEAD;
    Node* prevNode = NULL;
    while(currentNode->nextNode != NULL){
        prevNode = currentNode;
        printf("%c",prevNode->data);
        currentNode = prevNode->nextNode;
    }
    printf("%c",currentNode->data);
}
void insert(char data){
    Node* currentNode = HEAD;
    Node* prevNode = NULL;

    while (currentNode->nextNode != NULL )
    {
        currentNode = currentNode->nextNode; 
    }

    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->nextNode = NULL;

    currentNode->nextNode = newNode;
}
char delete(char data)
{
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
        if (currentNode->data == data)
        {
            prevNode->nextNode = currentNode->nextNode;
            free(currentNode);
            return data;
        }
        prevNode = currentNode;
        currentNode = currentNode->nextNode;
    }
    return '\0';

}
void freeNode(){
    Node* currentNode = HEAD;
    Node* prevNode = NULL;
    while(currentNode->nextNode != NULL){
        prevNode=currentNode;
        currentNode = currentNode->nextNode;
        free(prevNode);
    }
    free(currentNode);
}