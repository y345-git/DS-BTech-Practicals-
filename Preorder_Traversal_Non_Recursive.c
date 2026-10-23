// Write a C program to implement non-recursive Preorder traversal
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void preorder(struct Node *root) {
    if (root == NULL)
        return;

    struct Node *stack[100];
    int top = -1;

    stack[++top] = root;

    while (top != -1) {
        struct Node *temp = stack[top--];
        printf("%d ", temp->data);

        if (temp->right != NULL)
            stack[++top] = temp->right;

        if (temp->left != NULL)
            stack[++top] = temp->left;
    }
}

int main() {
    struct Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    return 0;
}
