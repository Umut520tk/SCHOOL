#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

void inOrder(Node *root,int arr[],int *i);
void preOrder(Node *root,int arr[],int *i);
void postOrder(Node *root,int arr[],int *i);
void sizeOfNode(Node *,int *size);

Node *createNode(int data);

int main(){

    Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);

    
    int size = 0;
    sizeOfNode(root,&size);

    int arrIn[size] = {}; 
    int arrPre[size] = {}; 
    int arrPost[size] = {}; 
    int i = 0;
    printf("Size of the Binary Tree is: %d",size);

    inOrder(root,arrIn,&i);

    printf("\nIn-Order Traversel Of Binary Tree:\n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ",arrIn[i]);
    }
    i = 0;

    preOrder(root,arrPre,&i);
    printf("\nPre-Order Traversel Of Binary Tree:\n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ",arrPre[i]);
    }
    i = 0;

    postOrder(root,arrPost,&i);
    printf("\nPost-Order Traversel Of Binary Tree:\n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ",arrPost[i]);
    }
    return 0;
}

Node *createNode(int data){

    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}
void sizeOfNode(Node *root,int *size){
    (*size)++;
    if(root->left == NULL && root->right == NULL)
    {
        return;
    }
    else
    {
        if (root->left != NULL)
        {
            sizeOfNode(root->left,size);        
        }
        if(root->right != NULL){
            sizeOfNode(root->right,size);
        }    
    }
}
void inOrder(Node *root,int arr[],int *i){

    if (root != NULL)
    {
        inOrder(root->left,arr,i);
        arr[(*i)] = root->data;
        (*i)++;
        inOrder(root->right,arr,i);
    }
}
void preOrder(Node *root,int arr[],int *i){
    if (root != NULL)
    {
        arr[*i] = root->data;
        (*i)++;
        preOrder(root->left,arr,i);
        preOrder(root->right,arr,i);

    }
}
void postOrder(Node *root,int arr[],int *i){
    if (root != NULL)
    {
        postOrder(root->left,arr,i);
        postOrder(root->right,arr,i);
        arr[*i] = root->data;
        (*i)++;
    }
}

