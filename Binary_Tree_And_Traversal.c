// Write a C program to implement Binary Tree with recursive Preorder, Inorder, and Postorder traversals
#include <stdio.h>

#define MAX 100

int tree[MAX];

void createTree(int index) {
    int data;
    printf("Enter data for node %d (-1 for no node): ", index);
    scanf("%d", &data);

    tree[index] = data;
    if (data == -1)
        return;

    // Create left child
    if (2 * index + 1 < MAX) {
        printf("Enter left child of %d:\n", data);
        createTree(2 * index + 1);
    }

    // Create right child
    if (2 * index + 2 < MAX) {
        printf("Enter right child of %d:\n", data);
        createTree(2 * index + 2);
    }
}

// Preorder: Root -> Left -> Right
void preorder(int index) {
    if (index >= MAX || tree[index] == -1)
        return;

    printf("%d ", tree[index]);
    preorder(2 * index + 1);
    preorder(2 * index + 2);
}

// Inorder: Left -> Root -> Right
void inorder(int index) {
    if (index >= MAX || tree[index] == -1)
        return;

    inorder(2 * index + 1);
    printf("%d ", tree[index]);
    inorder(2 * index + 2);
}

// Postorder: Left -> Right -> Root
void postorder(int index) {
    if (index >= MAX || tree[index] == -1)
        return;

    postorder(2 * index + 1);
    postorder(2 * index + 2);
    printf("%d ", tree[index]);
}

int main() {
    int i;
    for (i = 0; i < MAX; i++)
        tree[i] = -1;

    printf("Create Binary Tree\n");
    createTree(0);

    printf("\nPreorder Traversal: ");
    preorder(0);

    printf("\nInorder Traversal: ");
    inorder(0);

    printf("\nPostorder Traversal: ");
    postorder(0);
    printf("\n");

    return 0;
}
