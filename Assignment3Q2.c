// Write a program to implement Stack ADT 
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push() {
    int value;

    if (top == MAX - 1) {
        printf("Stack Overflow\n");
    }
    else {
        printf("Enter value: ");
        scanf("%d", &value);

        top++;
        stack[top] = value;

        printf("Value pushed successfully.\n");
    }
}

void pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
    }
    else {
        printf("Popped value: %d\n", stack[top]);
        top--;
    }
}

void display() {
    int i;

    if (top == -1) {
        printf("Stack is empty.\n");
    }
    else {
        printf("Stack: ");

        for (i = top; i >= 0; i--) {
            printf("%d ", stack[i]);
        }

        printf("\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nStack ADT Operations:\n");
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