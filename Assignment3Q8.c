// Write a program to implement linked list as sack
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;

void push() {
    struct Node *newNode;
    int value;

    newNode = malloc(sizeof(struct Node));

    printf("Enter value: ");
    scanf("%d", &value);

    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

void pop() {
    struct Node *temp;

    if (top == NULL) {
        printf("Stack is empty.\n");
    }
    else {
        temp = top;
        printf("Popped value: %d\n", top->data);
        top = top->next;
        free(temp);
    }
}

void display() {
    struct Node *temp = top;

    if (top == NULL) {
        printf("Stack is empty.\n");
    }
    else {
        printf("Stack: ");

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
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push();
                break;

            case 2:
                pop();
                break;

            case 3:
                display();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}