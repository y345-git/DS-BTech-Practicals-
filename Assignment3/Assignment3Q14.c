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
    struct Node *newNode;
    int value;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    printf("Enter value: ");
    scanf("%d", &value);

    newNode->data = value;
    newNode->next = NULL;

    if (front == NULL) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue() {
    struct Node *temp;

    if (front == NULL) {
        printf("Queue is empty.\n");
    }
    else {
        temp = front;
        printf("Deleted: %d\n", front->data);

        front = front->next;
        free(temp);

        if (front == NULL) {
            rear = NULL;
        }
    }
}

void display() {
    struct Node *temp;

    if (front == NULL) {
        printf("Queue is empty.\n");
    }
    else {
        temp = front;

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
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Display");
        printf("\n4. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            enqueue();
        }
        else if (choice == 2) {
            dequeue();
        }
        else if (choice == 3) {
            display();
        }
        else if (choice == 4) {
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}