// Write a program to implement Deque (Double Ended Queue)
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int deque[MAX];
int front = -1, rear = -1;

void insertFront() {
    if (front == 0) {
        printf("Deque is full at front.\n");
        return;
    }
    if (front == -1) {
        front = rear = 0;
    } else {
        front--;
    }
    printf("Enter value: ");
    scanf("%d", &deque[front]);
}

void insertRear() {
    if (rear == MAX - 1) {
        printf("Deque is full at rear.\n");
        return;
    }
    if (rear == -1) {
        front = rear = 0;
    } else {
        rear++;
    }
    printf("Enter value: ");
    scanf("%d", &deque[rear]);
}

void deleteFront() {
    if (front == -1 || front > rear) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deleted: %d\n", deque[front++]);
    if (front > rear) {
        front = rear = -1;
    }
}

void deleteRear() {
    if (rear == -1 || front > rear) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deleted: %d\n", deque[rear--]);
    if (front > rear) {
        front = rear = -1;
    }
}

void display() {
    if (front == -1 || front > rear) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deque: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", deque[i]);
    }
    printf("\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nDouble Ended Queue Operations:\n");
        printf("1. Insert Front\n");
        printf("2. Insert Rear\n");
        printf("3. Delete Front\n");
        printf("4. Delete Rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertFront(); break;
            case 2: insertRear(); break;
            case 3: deleteFront(); break;
            case 4: deleteRear(); break;
            case 5: display(); break;
            case 6: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
