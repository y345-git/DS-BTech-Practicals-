// Write a program to implement Dqueue(double ended queue) 
#include <stdio.h>

#define MAX 100

int deque[MAX];
int front = -1, rear = -1;

void insertFront() {
    int value;

    if (front == 0) {
        printf("Deque is full at front.\n");
    }
    else {
        printf("Enter value: ");
        scanf("%d", &value);

        if (front == -1) {
            front = rear = 0;
        }
        else {
            front--;
        }

        deque[front] = value;
    }
}

void insertRear() {
    int value;

    if (rear == MAX - 1) {
        printf("Deque is full at rear.\n");
    }
    else {
        printf("Enter value: ");
        scanf("%d", &value);

        if (rear == -1) {
            front = rear = 0;
        }
        else {
            rear++;
        }

        deque[rear] = value;
    }
}

void deleteFront() {
    if (front == -1 || front > rear) {
        printf("Deque is empty.\n");
    }
    else {
        printf("Deleted: %d\n", deque[front]);
        front++;

        if (front > rear) {
            front = rear = -1;
        }
    }
}

void deleteRear() {
    if (rear == -1 || front > rear) {
        printf("Deque is empty.\n");
    }
    else {
        printf("Deleted: %d\n", deque[rear]);
        rear--;

        if (front > rear) {
            front = rear = -1;
        }
    }
}

void display() {
    int i;

    if (front == -1) {
        printf("Deque is empty.\n");
    }
    else {
        printf("Deque: ");

        for (i = front; i <= rear; i++) {
            printf("%d ", deque[i]);
        }

        printf("\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("Double Ended Queue Operations:\n");
        printf("\n1. Insert Front");
        printf("\n2. Insert Rear");
        printf("\n3. Delete Front");
        printf("\n4. Delete Rear");
        printf("\n5. Display");
        printf("\n6. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            insertFront();
        }
        else if (choice == 2) {
            insertRear();
        }
        else if (choice == 3) {
            deleteFront();
        }
        else if (choice == 4) {
            deleteRear();
        }
        else if (choice == 5) {
            display();
        }
        else if (choice == 6) {
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}