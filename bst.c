#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int valor;
    struct Node *left;
    struct Node *right;
}node;

node* newNode(int key){
    node* t = malloc(sizeof(node));
    t->valor = key;
    t->right = t->left = NULL;
    return t;
}

node* insertNode(node* root, int key){
    if(root == NULL) return newNode(key);
    if(key < root->valor)
        root->left = insertNode(root->left,key);
    else if (key > root->valor)
        root->right = insertNode(root->right,key);
    return root;
}

node* tree_search(node* root,int key){
    if(root == NULL || root->valor == key)
        return root;
    if(key < root->valor)
        return tree_search(root->left,key);
    else return tree_search(root->right,key);
}

void printTree(node* root){
    if(root != NULL){
        printTree(root->left);
        printf("%d \n", root->valor);
        printTree(root->right);
    }
}

int main(){
    
    node* root = NULL;
    root = insertNode(root,10);
    insertNode(root, 30);
    insertNode(root, 20);

    printTree(root);
}