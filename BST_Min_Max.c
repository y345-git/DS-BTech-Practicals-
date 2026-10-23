// Write a C program to implement BST (addNode, search, findMin, and findMax)
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

struct Node *addNode(struct Node *root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = addNode(root->left, data);
    else if (data > root->data)
        root->right = addNode(root->right, data);

    return root;
}

void search(struct Node *root, int target) {
    if (root == NULL) {
        printf("Target not found\n");
        return;
    }
    if (root->data == target) {
        printf("Target found\n");
        return;
    }
    if (target < root->data)
        search(root->left, target);
    else
        search(root->right, target);
}

int findMin(struct Node *root) {
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

int findMax(struct Node *root) {
    while (root->right != NULL)
        root = root->right;
    return root->data;
}

int main() {
    struct Node *root = NULL;
    int n, data, target, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &data);
        root = addNode(root, data);
    }

    printf("\nEnter target to search: ");
    scanf("%d", &target);
    search(root, target);

    if (root != NULL) {
        printf("Minimum value = %d\n", findMin(root));
        printf("Maximum value = %d\n", findMax(root));
    }

    return 0;
}
