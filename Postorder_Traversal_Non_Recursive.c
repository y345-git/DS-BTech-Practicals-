// Write a C program to implement non-recursive Postorder traversal
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

void postorder(struct Node *root) {
    if (root == NULL)
        return;

    struct Node *stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 != -1) {
        struct Node *temp = stack1[top1--];
        stack2[++top2] = temp;

        if (temp->left != NULL)
            stack1[++top1] = temp->left;

        if (temp->right != NULL)
            stack1[++top1] = temp->right;
    }

    while (top2 != -1) {
        struct Node *temp = stack2[top2--];
        printf("%d ", temp->data);
    }
}

int main() {
    struct Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    return 0;
}
