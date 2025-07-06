#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;

};

void inorderTraversel(struct node *root);

void preorderTraversel(struct node *root);

void postorderTraversel(struct node *root);

struct node* createNode(int data);

int main(){

    struct node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);
    
    printf("INORDER TRAVERSAL\n\t");
    inorderTraversel(root);

    printf("\nPREORDER TRAVERSAL\n\t");
    preorderTraversel(root);


    printf("\nPOSTORDER TRAVERSAL\n\t");
    postorderTraversel(root);

    return 0;
}

struct node* createNode(int data)
{
    struct node *root = (struct node *)malloc(sizeof(struct node));
    root->data = data;
    root->left = NULL;
    root->right = NULL;

    return root;
}

void inorderTraversel(struct node *root){
    if(root != NULL)
    {
        inorderTraversel(root->left);
        printf("%d ",root->data);
        inorderTraversel(root->right);
    }
}

void preorderTraversel(struct node *root){
    if (root != NULL)
    {
        printf("%d ",root->data);
        preorderTraversel(root->left);
        preorderTraversel(root->right);
    }
}

void postorderTraversel(struct node *root){
    if (root != NULL)
    {
        postorderTraversel(root->left);
        postorderTraversel(root->right);
        printf("%d ",root->data);
    }
    
}