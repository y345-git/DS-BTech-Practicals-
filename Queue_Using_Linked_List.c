// Write a program to implement linked list as Queue
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL;
struct Node *rear = NULL;

void enqueue() {
    struct Node *newNode = malloc(sizeof(struct Node));
    printf("Enter value: ");
    scanf("%d", &newNode->data);
    newNode->next = NULL;

    if (front == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue() {
    if (front == NULL) {
        printf("Queue is empty.\n");
    } else {
        struct Node *temp = front;
        printf("Deleted: %d\n", front->data);
        front = front->next;
        free(temp);
        if (front == NULL) {
            rear = NULL;
        }
    }
}

void display() {
    if (front == NULL) {
        printf("Queue is empty.\n");
    } else {
        struct Node *temp = front;
        printf("Queue: ");
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: display(); break;
            case 4: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
