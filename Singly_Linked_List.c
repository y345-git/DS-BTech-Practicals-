// Write a program to implement a Singly Linked List (insert, delete, search, and display functions)
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void insert() {
    struct Node *newNode = malloc(sizeof(struct Node));
    printf("Enter value: ");
    scanf("%d", &newNode->data);
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void delete() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    int value;
    printf("Enter value to delete: ");
    scanf("%d", &value);

    struct Node *temp = head, *prev = NULL;
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value not found.\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Deleted successfully.\n");
}

void search() {
    if (head == NULL) {
        printf("Value not found.\n");
        return;
    }

    int value;
    printf("Enter value to search: ");
    scanf("%d", &value);

    for (struct Node *temp = head; temp != NULL; temp = temp->next) {
        if (temp->data == value) {
            printf("Value found.\n");
            return;
        }
    }
    printf("Value not found.\n");
}

void display() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("List: ");
    for (struct Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d -> ", temp->data);
    }
    printf("NULL\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nSingly Linked List Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insert(); break;
            case 2: delete(); break;
            case 3: search(); break;
            case 4: display(); break;
            case 5: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
